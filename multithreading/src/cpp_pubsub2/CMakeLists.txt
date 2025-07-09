cmake_minimum_required(VERSION 3.8)
project(cpp_pubsub2)

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(message REQUIRED)
include_directories(include)

add_executable(thread_message src/main.cpp)
ament_target_dependencies(thread_message rclcpp message)

install(TARGETS
  thread_message
  DESTINATION lib/${PROJECT_NAME})

ament_package()
