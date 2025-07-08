#include "rclcpp/rclcpp.hpp"
#include "integer_interface/srv/add_three_ints.hpp"

#include <memory>

void add(const std::shared_ptr<integer_interface::srv::AddThreeInts::Request> request,
          std::shared_ptr<integer_interface::srv::AddThreeInts::Response>       response)
{
  response->sum = request->a + request->b + request->c;
  RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Incoming request\na: %ld" " b: %ld" " c: %ld",
                request->a, request->b, request->c);
  RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "sending back response: [%ld]", (long int)response->sum);
}

int main(int argc, char **argv)
{
  rclcpp::init(argc, argv);

  std::shared_ptr<rclcpp::Node> node = rclcpp::Node::make_shared("add_three_ints_server");

  rclcpp::Service<integer_interface::srv::AddThreeInts>::SharedPtr service =
    node->create_service<integer_interface::srv::AddThreeInts>("/add_three_ints",  &add);

  RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Ready to add three ints.");

  rclcpp::spin(node);
  rclcpp::shutdown();
}