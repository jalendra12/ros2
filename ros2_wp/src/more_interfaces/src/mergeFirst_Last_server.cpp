#include "rclcpp/rclcpp.hpp"
#include "more_interfaces/srv/address_book.hpp"

#include <memory>

void add(const std::shared_ptr<more_interfaces::srv::AddressBook::Request> request,
         std::shared_ptr<more_interfaces::srv::AddressBook::Response> response)
{
  response->full_name = request->first_name + " - " + request->last_name;

  RCLCPP_INFO(rclcpp::get_logger("rclcpp"),
              "Incoming request\nfirst_name: '%s' last_name: '%s'",
              request->first_name.c_str(), request->last_name.c_str());

  RCLCPP_INFO(rclcpp::get_logger("rclcpp"),
              "Sending back response: '%s'",
              response->full_name.c_str());
}


int main(int argc, char **argv)
{
  rclcpp::init(argc, argv);

  std::shared_ptr<rclcpp::Node> node = rclcpp::Node::make_shared("address_book_server");

  rclcpp::Service<more_interfaces::srv::AddressBook>::SharedPtr service =
    node->create_service<more_interfaces::srv::AddressBook>("merge_name", &add);

  RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Ready to Merge first and Last Name");

  rclcpp::spin(node);
  rclcpp::shutdown();
}