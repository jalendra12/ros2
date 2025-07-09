#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include "../include/cpp_pubsub1/publisher1_member_function.hpp"
#include "../include/cpp_pubsub1/publisher2_member_function.hpp"
#include "../include/cpp_pubsub1/subscriber1_member_function.hpp"
#include "../include/cpp_pubsub1/subscriber2_member_function.hpp"
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

    // Create threads for each node to run concurrently
    // std::thread publisher_thread_1(run_publisher_node_1);
    // std::thread publisher_thread_2(run_publisher_node_2);
    // std::thread subscriber_thread_1(run_subscriber_node_1);
    // std::thread subscriber_thread_2(run_subscriber_node_2);

    // Wait for all threads to finish (join)
    // publisher_thread_1.join();
    // publisher_thread_2.join();
    // subscriber_thread_1.join();
    // subscriber_thread_2.join();

    // // all nodes will spin in single thread
    // rclcpp::executors::SingleThreadedExecutor executor;
    // rclcpp::executors::StaticSingleThreadedExecutor executor; // this is used when we are initializing subscription, topic, etc. first
    rclcpp::executors::MultiThreadedExecutor executor;
    rclcpp::Node::SharedPtr node2 = std::make_shared<MinimalPublisher1>();
    rclcpp::Node::SharedPtr node4 = std::make_shared<MinimalPublisher2>();
    executor.add_node(node2);
    executor.add_node(node4);
    rclcpp::Node::SharedPtr node1 = std::make_shared<MinimalSubscriber1>();
    executor.add_node(node1);
    rclcpp::Node::SharedPtr node3 = std::make_shared<MinimalSubscriber2>();
    executor.add_node(node3);
    executor.spin();

    rclcpp::shutdown();
    return 0;
}
