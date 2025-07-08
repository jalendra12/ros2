cmake_minimum_required(VERSION 3.8)
project(integer_interface)

find_package(ament_cmake REQUIRED)
find_package(rosidl_default_generators REQUIRED)
find_package(rclcpp REQUIRED)
rosidl_generate_interfaces(${PROJECT_NAME}
  "srv/AddThreeInts.srv"
)
ament_package()
