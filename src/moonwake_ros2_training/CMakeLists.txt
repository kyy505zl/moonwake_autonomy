cmake_minimum_required(VERSION 3.8)
project(moonwake_ros2_training)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # comment the line when a copyright and license is added to all source files
  set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # comment the line when this package is in a git repo and when
  # a copyright and license is added to all source files
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

add_executable(heartbeat_node src/heartbeat_node.cpp)
add_executable(talker_node src/talker_node.cpp)
add_executable(listener_node src/listener_node.cpp)
add_executable(target_offset_publisher src/target_offset_publisher.cpp)
add_executable(steering_hint_node src/steering_hint_node.cpp)

ament_target_dependencies(heartbeat_node rclcpp)
ament_target_dependencies(talker_node rclcpp std_msgs)
ament_target_dependencies(listener_node rclcpp std_msgs)
ament_target_dependencies(target_offset_publisher rclcpp std_msgs)
ament_target_dependencies(steering_hint_node rclcpp std_msgs)

install(TARGETS
  heartbeat_node
  talker_node
  listener_node
  target_offset_publisher
  steering_hint_node
  DESTINATION lib/${PROJECT_NAME})

install(DIRECTORY
  config
  launch
  DESTINATION share/${PROJECT_NAME})
  
ament_package()
