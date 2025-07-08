cmake_minimum_required(VERSION 3.8)
project(server)

find_package(ament_cmake REQUIRED)
find_package(rosidl_default_generators REQUIRED)
find_package(rclcpp REQUIRED)

set(msg_files
  "srv/AddThreeInts.srv"
)
rosidl_generate_interfaces(${PROJECT_NAME}
  ${msg_files}
)
ament_export_dependencies(rosidl_default_runtime)

add_executable(add_three_ints_server src/add_three_ints_server.cpp)
ament_target_dependencies(add_three_ints_server rclcpp)


install(TARGETS
    add_three_ints_server
  DESTINATION lib/${PROJECT_NAME})

rosidl_get_typesupport_target(cpp_typesupport_target
  ${PROJECT_NAME} rosidl_typesupport_cpp)

target_link_libraries(add_three_ints_server "${cpp_typesupport_target}")
ament_package()