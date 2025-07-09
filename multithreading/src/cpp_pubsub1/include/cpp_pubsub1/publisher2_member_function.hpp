#include <chrono>
#include <functional>
#include <memory>
#include <string>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

using namespace std::chrono_literals;

class MinimalPublisher2 : public rclcpp::Node
{
  public:
    MinimalPublisher2()
    : Node("minimal_publisher2"), count_(0)
    {
      publisher_ = this->create_publisher<std_msgs::msg::String>("topic2", 10);
      timer_ = this->create_wall_timer(
      1000ms, std::bind(&MinimalPublisher2::timer_callback, this));
    }

  private:
    void timer_callback()
    {
        auto now = std::chrono::system_clock::now();
        auto now_time_t = std::chrono::system_clock::to_time_t(now);
        auto duration = now.time_since_epoch();
        auto microseconds = std::chrono::duration_cast<std::chrono::microseconds>(duration).count();

        std::tm* local_time = std::localtime(&now_time_t);

        // Format minutes, seconds, and microseconds
        std::stringstream time_stream;
        time_stream << std::put_time(local_time, "%M:%S") << ":" << (microseconds % 1000000);

        auto message = std_msgs::msg::String();
        message.data = "Hello, world! " + std::to_string(count_++);
        RCLCPP_INFO(this->get_logger(), "[%s] Publishing using 2: '%s'",time_stream.str().c_str(), message.data.c_str());
        publisher_->publish(message);
    }
    rclcpp::TimerBase::SharedPtr timer_;
    rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher_;
    size_t count_;
};

// int main(int argc, char * argv[])
// {
//   rclcpp::init(argc, argv);
//   rclcpp::spin(std::make_shared<MinimalPublisher2>());
//   rclcpp::shutdown();
//   return 0;
// }