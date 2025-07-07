#include <chrono>
#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "more_interfaces/msg/address_book.hpp"

using namespace std::chrono_literals;

class AddressBookPublisher : public rclcpp::Node
{
public:
  AddressBookPublisher(const std::string &first, const std::string &last, const std::string &phone)
  : Node("address_book_publisher"), first_name_(first), last_name_(last), phone_number_(phone)
  {
    address_book_publisher_ =
      this->create_publisher<more_interfaces::msg::AddressBook>("address_book", 10);

    auto publish_msg = [this]() -> void {
        auto message = more_interfaces::msg::AddressBook();

        message.first_name = first_name_;
        message.last_name = last_name_;
        message.phone_number = phone_number_;
        message.phone_type = message.PHONE_TYPE_MOBILE;

        std::cout << "Publishing Contact\nFirst:" << message.first_name <<
          "  Last:" << message.last_name << std::endl;

        this->address_book_publisher_->publish(message);
      };
    timer_ = this->create_wall_timer(1s, publish_msg);
  }

private:
  rclcpp::Publisher<more_interfaces::msg::AddressBook>::SharedPtr address_book_publisher_;
  rclcpp::TimerBase::SharedPtr timer_;
  std::string first_name_;
  std::string last_name_;
  std::string phone_number_;
};


int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  if( argc < 4){
    std::cout<<"Required Full Name and Phone Number"<<std::endl;
    return 1;
  }
  std::string name = argv[1];
  std::string lname = argv[2];
  std::string pNumber = argv[3];

  rclcpp::spin(std::make_shared<AddressBookPublisher>(name,lname,pNumber));
  rclcpp::shutdown();

  return 0;
}