#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/string.hpp>

#include <boost/beast/core.hpp>
#include <boost/beast/websocket.hpp>
#include <boost/asio.hpp>
#include <thread>
#include <set>
#include <mutex>
#include <memory>
#include <queue>

namespace beast = boost::beast;
namespace websocket = beast::websocket;
namespace asio = boost::asio;
using tcp = boost::asio::ip::tcp;

class ROS2WebSocketBridge;

std::set<std::shared_ptr<websocket::stream<tcp::socket>>> clients;
std::mutex clients_mutex;

class ClientHandler {
public:
  ClientHandler(std::shared_ptr<websocket::stream<tcp::socket>> ws,
                std::shared_ptr<ROS2WebSocketBridge> ros_node)
      : ws_(ws), ros_node_(ros_node) {
    thread_ = std::thread(&ClientHandler::run, this);
  }

  ~ClientHandler() {
    if (thread_.joinable())
      thread_.join();
  }

private:
  std::shared_ptr<websocket::stream<tcp::socket>> ws_;
  std::shared_ptr<ROS2WebSocketBridge> ros_node_;
  std::thread thread_;

  void run();
};

class ROS2WebSocketBridge : public rclcpp::Node {
  public:
    ROS2WebSocketBridge()
        : Node("ros2_websocket_bridge"), counter_(0) {
  
      subscription_ = this->create_subscription<std_msgs::msg::String>(
          "/chatter", 10,
          std::bind(&ROS2WebSocketBridge::topic_callback, this, std::placeholders::_1));
  
      // 🕒 Create timer: fires every 1 second
      timer_ = this->create_wall_timer(
          std::chrono::seconds(1),
          std::bind(&ROS2WebSocketBridge::timer_callback, this));
    }
  
    void print_from_client(const std::string& msg) {
      RCLCPP_INFO(this->get_logger(), "Message from WebSocket client: '%s'", msg.c_str());
    }
  
  private:
    rclcpp::Subscription<std_msgs::msg::String>::SharedPtr subscription_;
    rclcpp::TimerBase::SharedPtr timer_;
    int counter_;
  
    void topic_callback(const std_msgs::msg::String::SharedPtr msg) {
      std::lock_guard<std::mutex> lock(clients_mutex);
      for (auto& ws : clients) {
        try {
          ws->text(true);
          ws->write(asio::buffer(msg->data));
        } catch (...) {
          // ignore broken clients
        }
      }
    }
  
    void timer_callback() {
      std::string message = "Timer message #" + std::to_string(++counter_);
      RCLCPP_INFO(this->get_logger(), "Sending: '%s'", message.c_str());
  
      std::lock_guard<std::mutex> lock(clients_mutex);
      for (auto& ws : clients) {
        try {
          ws->text(true);
          ws->write(asio::buffer(message));
        } catch (...) {
          // ignore broken clients
        }
      }
    }
  
    friend class ClientHandler;
  };
  

// ---------------- Client Handler Implementation ----------------
void ClientHandler::run() {
  beast::flat_buffer buffer;
  try {
    while (true) {
      ws_->read(buffer);
      std::string received = beast::buffers_to_string(buffer.data());
      buffer.consume(buffer.size());

      if (!received.empty() && ros_node_) {
        ros_node_->print_from_client(received);
      }
    }
  } catch (...) {
    std::lock_guard<std::mutex> lock(clients_mutex);
    clients.erase(ws_);
  }
}

// ---------------- WebSocket Server ----------------
class WebSocketServer {
public:
  WebSocketServer(asio::io_context& ioc, unsigned short port,
                  std::shared_ptr<ROS2WebSocketBridge> ros_node)
      : acceptor_(ioc, tcp::endpoint(tcp::v4(), port)),
        ros_node_(ros_node) {
    accept();
  }

private:
  tcp::acceptor acceptor_;
  std::shared_ptr<ROS2WebSocketBridge> ros_node_;

  void accept() {
    acceptor_.async_accept([this](boost::system::error_code ec, tcp::socket socket) {
      if (!ec) {
        auto ws = std::make_shared<websocket::stream<tcp::socket>>(std::move(socket));
        ws->accept();

        {
          std::lock_guard<std::mutex> lock(clients_mutex);
          clients.insert(ws);
        }

        // Start client handler
        new ClientHandler(ws, ros_node_);  // Memory managed by thread
      }

      accept();  // Continue accepting
    });
  }
};

// ---------------- Main ----------------
int main(int argc, char* argv[]) {
  rclcpp::init(argc, argv);

  asio::io_context ioc;
  auto ros_node = std::make_shared<ROS2WebSocketBridge>();
  WebSocketServer server(ioc, 8765, ros_node);

  std::thread io_thread([&ioc]() { ioc.run(); });

  rclcpp::spin(ros_node);
  ioc.stop();
  io_thread.join();
  rclcpp::shutdown();
  return 0;
}
