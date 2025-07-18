#include <chrono>
#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "message/msg/instruct_robot.hpp"

using namespace std::chrono_literals;

class MinimalPublisher : public rclcpp::Node
{
public:
  MinimalPublisher(int status)
  : Node("minimal_publisher"),status(status)
  {
    publisher_ = this->create_publisher<message::msg::InstructRobot>("topic", 10);
    // timer_ = this->create_wall_timer(
    //   1000ms, std::bind(&MinimalPublisher::timer_callback, this));
    timer_callback();
  }

private:
  void timer_callback()
  {
    auto message = message::msg::InstructRobot();                           
    message.status = status;                                    
    RCLCPP_INFO(this->get_logger(), "Publishing %d",status);
    publisher_->publish(message);
  }
  rclcpp::TimerBase::SharedPtr timer_;
  rclcpp::Publisher<message::msg::InstructRobot>::SharedPtr publisher_;     
  int status;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  int status = atoll(argv[1]);
  rclcpp::spin(std::make_shared<MinimalPublisher>(status));
  rclcpp::shutdown();
  return 0;
}