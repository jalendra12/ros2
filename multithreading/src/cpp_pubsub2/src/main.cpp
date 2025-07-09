#include "rclcpp/rclcpp.hpp"
#include "../include/cpp_pubsub2/publisher1_member_function.hpp"
#include "../include/cpp_pubsub2/publisher2_member_function.hpp"
#include "../include/cpp_pubsub2/subscriber1_member_function.hpp"
#include "../include/cpp_pubsub2/subscriber2_member_function.hpp"
#include <thread>

void run_publisher_node_1()
{
    rclcpp::spin(std::make_shared<MinimalPublisher1>());
}

void run_publisher_node_2()
{
    rclcpp::spin(std::make_shared<MinimalPublisher2>());
}

void run_subscriber_node_1()
{
    rclcpp::spin(std::make_shared<MinimalSubscriber1>());
}

void run_subscriber_node_2()
{
    rclcpp::spin(std::make_shared<MinimalSubscriber2>());
}

int main(int argc, char **argv)
{
    // Initialize ROS 2
    rclcpp::init(argc, argv);

    std::thread t_1(run_publisher_node_1);
    std::thread t_2(run_publisher_node_2);
    std::thread t_3(run_subscriber_node_1);
    // std::thread t_4(run_subscriber_node_2);

    // Wait for all threads to finish (join)
    t_1.join();
    t_2.join();
    t_3.join();
    // t_4.join();
    return 0;
}
