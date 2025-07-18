#include<iostream>
#include "subscriber.cpp"
int main(int argc, char*argv[]){
  rclcpp::init(argc, argv);
  std::cout<<"The Subscriber is Active...\n";

  auto node = std::make_shared<MinimalSubscriber>();
  rclcpp::executors::MultiThreadedExecutor executor;
  executor.add_node(node);
  executor.spin();
  
  rclcpp::shutdown();
  return 0;
}