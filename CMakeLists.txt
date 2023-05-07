cmake_minimum_required(VERSION 3.8)
project(ros2-service)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(rclpy REQUIRED)
find_package(rclcpp_lifecycle REQUIRED)
find_package(rclcpp_components REQUIRED)
find_package(std_srvs REQUIRED)

# BUILD
include_directories(
  include
)

set(executable_server_name srv_server_node)
set(executable_client_name srv_client_node)
set(library_name ${PROJECT_NAME}_lib)

set(dependencies
  rclcpp
  rclpy
  rclcpp_lifecycle
  rclcpp_components
  std_srvs
)

add_library(${library_name} SHARED
  src/srv_server.cpp
  src/srv_client.cpp
)
ament_target_dependencies(${library_name} ${dependencies})

# Server
add_executable(${executable_server_name}
  src/srv_server_node.cpp
)
ament_target_dependencies(${executable_server_name} ${dependencies})
target_link_libraries(${executable_server_name} ${library_name})

# Client
add_executable(${executable_client_name}
  src/srv_client_node.cpp
)
ament_target_dependencies(${executable_client_name} ${dependencies})
target_link_libraries(${executable_client_name} ${library_name})

# INSTALL
install(TARGETS ${library_name}
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION bin
)

install(TARGETS
  ${executable_server_name}
  ${executable_client_name}
  RUNTIME DESTINATION lib/${PROJECT_NAME}
)

install(DIRECTORY include/
  DESTINATION include
)

install(DIRECTORY
  launch
  DESTINATION share/${PROJECT_NAME}
)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # uncomment the line when a copyright and license is not present in all source files
  #set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # uncomment the line when this package is not in a git repo
  #set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
