cmake_minimum_required(VERSION 3.8)
project(pubsub)

find_package(ament_cmake REQUIRED)
find_package(message REQUIRED)
find_package(rclcpp REQUIRED)
include_directories(include)

add_executable(publisher src/publisher.cpp)
ament_target_dependencies(publisher rclcpp message)

add_executable(subscriber src/main.cpp)
ament_target_dependencies(subscriber rclcpp message)

install(TARGETS
  publisher
  subscriber
  DESTINATION lib/${PROJECT_NAME})

ament_package()
