cmake_minimum_required(VERSION 3.8)
project(node)

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(tutorial_interfaces REQUIRED)

add_executable(run_node src/node.cpp)
ament_target_dependencies(run_node rclcpp std_msgs tutorial_interfaces)

install(TARGETS
  run_node
  DESTINATION lib/${PROJECT_NAME})

ament_package()
