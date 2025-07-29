cmake_minimum_required(VERSION 3.5)
project(webapi)

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(Boost REQUIRED COMPONENTS system thread)

add_executable(websocket_server src/websocket_server.cpp)

target_include_directories(websocket_server PRIVATE
  ${Boost_INCLUDE_DIRS}
)

target_link_libraries(websocket_server
  ${Boost_LIBRARIES}
)

ament_target_dependencies(websocket_server
  rclcpp
  std_msgs
)

install(TARGETS
  websocket_server
  DESTINATION lib/${PROJECT_NAME}
)

ament_package()
