#include <chrono>
#include <functional>
#include <memory>
#include <string>

#include "rclcpp/rclcpp.hpp"
#include "message/msg/thread_message.hpp"

using namespace std::chrono_literals;

class MinimalPublisher1 : public rclcpp::Node
{
  public:
    MinimalPublisher1()
    : Node("minimal_publisher1"), count_(0)
    {
      publisher_ = this->create_publisher<message::msg::ThreadMessage>("topic", 10);
      timer_ = this->create_wall_timer(
      500ms, std::bind(&MinimalPublisher1::timer_callback, this));
    }

  private:
    void timer_callback()
    {
      auto message = message::msg::ThreadMessage();
      message.s2 = "Hello, world1! " + std::to_string(count_);
      // message.s1 = "Hello, world1! " + std::to_string(count_);
      count_++;
      RCLCPP_INFO(this->get_logger(), "Publishing using 1: '%s' & '%s'",message.s1.c_str(), message.s2.c_str());
      publisher_->publish(message);
    }
    rclcpp::TimerBase::SharedPtr timer_;
    rclcpp::Publisher<message::msg::ThreadMessage>::SharedPtr publisher_;
    size_t count_;
};

// int main(int argc, char * argv[])
// {
//   rclcpp::init(argc, argv);
//   rclcpp::spin(std::make_shared<MinimalPublisher1>());
//   rclcpp::shutdown();
//   return 0;
// }