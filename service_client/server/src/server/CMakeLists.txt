cmake_minimum_required(VERSION 3.8)
project(server)

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(integer_interface)

add_executable(add_three_ints_server src/add_three_ints_server.cpp)
ament_target_dependencies(add_three_ints_server rclcpp integer_interface)

install(TARGETS
    add_three_ints_server
  DESTINATION lib/${PROJECT_NAME})

ament_package()