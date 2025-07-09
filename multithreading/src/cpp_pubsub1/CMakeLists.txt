cmake_minimum_required(VERSION 3.8)
project(cpp_pubsub1)

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
include_directories(include)

add_executable(parallelism src/main.cpp)
ament_target_dependencies(parallelism rclcpp std_msgs)

install(TARGETS
  parallelism
  DESTINATION lib/${PROJECT_NAME})

ament_package()
