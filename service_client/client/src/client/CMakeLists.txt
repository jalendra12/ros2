cmake_minimum_required(VERSION 3.8)
project(client)

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(integer_interface REQUIRED)

add_executable(add_three_ints_client src/add_three_ints_client.cpp)
ament_target_dependencies(add_three_ints_client rclcpp integer_interface)

install(TARGETS
    add_three_ints_client
  DESTINATION lib/${PROJECT_NAME})

ament_package()