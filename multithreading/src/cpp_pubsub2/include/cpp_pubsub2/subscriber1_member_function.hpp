#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "message/msg/thread_message.hpp"
using std::placeholders::_1;

class MinimalSubscriber1 : public rclcpp::Node
{
  public:
    MinimalSubscriber1()
    : Node("minimal_subscriber1")
    {
      subscription_ = this->create_subscription<message::msg::ThreadMessage>(
      "topic", 10, std::bind(&MinimalSubscriber1::topic_callback, this, _1));
    }

  private:
    void topic_callback(const message::msg::ThreadMessage & msg) const
    {
      RCLCPP_INFO(this->get_logger(), "Subscriber 1: '%s' & '%s'",msg.s1.c_str(), msg.s2.c_str());
    }
    rclcpp::Subscription<message::msg::ThreadMessage>::SharedPtr subscription_;
};

// int main(int argc, char * argv[])
// {
//   rclcpp::init(argc, argv);
//   rclcpp::spin(std::make_shared<MinimalSubscriber1>());
//   rclcpp::shutdown();
//   return 0;
// }