#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "message/msg/thread_message.hpp"
using std::placeholders::_1;

class MinimalSubscriber2 : public rclcpp::Node
{
  public:
    MinimalSubscriber2()
    : Node("minimal_subscriber2")
    {
      subscription_ = this->create_subscription<message::msg::ThreadMessage>(
      "topic", 10, std::bind(&MinimalSubscriber2::topic_callback, this, _1));
    }

  private:
    void topic_callback(const message::msg::ThreadMessage & msg) const
    {
      RCLCPP_INFO(this->get_logger(), "Subscriber 2: '%s' & '%s'",msg.s1.c_str(), msg.s2.c_str());
    }
    rclcpp::Subscription<message::msg::ThreadMessage>::SharedPtr subscription_;
};

// int main(int argc, char * argv[])
// {
//   rclcpp::init(argc, argv);
//   rclcpp::spin(std::make_shared<MinimalSubscriber2>());
//   rclcpp::shutdown();
//   return 0;
// }