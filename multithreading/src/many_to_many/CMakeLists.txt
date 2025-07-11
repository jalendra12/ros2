cmake_minimum_required(VERSION 3.8)
project(many_to_many)

find_package(ament_cmake REQUIRED)
find_package(message REQUIRED)
find_package(rclcpp REQUIRED)
include_directories(include)

add_executable(many1 src/main1.cpp)
ament_target_dependencies(many1 rclcpp message)

add_executable(many2 src/main2.cpp)
ament_target_dependencies(many2 rclcpp message)

install(TARGETS
  many1
  many2
  DESTINATION lib/${PROJECT_NAME})

ament_package()
