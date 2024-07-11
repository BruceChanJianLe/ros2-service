cmake_minimum_required(VERSION 3.8)
project(ros2-service)

# Default to C99
if(NOT CMAKE_C_STANDARD)
  set(CMAKE_C_STANDARD 99)
endif()

# Default to C++20
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 20)
  set(CMAKE_CXX_STANDARD_REQUIRED ON)
endif()

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies_pkgs
find_package(ament_cmake REQUIRED)

set(dependencies_pkgs
  rclcpp
  rclpy
  rclcpp_lifecycle
  rclcpp_components
  std_srvs
)

foreach(pkg IN LISTS dependencies_pkgs)
  find_package(${pkg} REQUIRED)
endforeach()

include_directories(include)

# BUILD
set(executable_server_name srv_server_node)
set(executable_client_name srv_client_node)
set(library_name ${PROJECT_NAME}_lib)

add_library(${library_name} SHARED
  src/srv_server.cpp
  src/srv_client.cpp
)
ament_target_dependencies(${library_name} ${dependencies_pkgs})

# Server
add_executable(${executable_server_name}
  src/srv_server_node.cpp
)
ament_target_dependencies(${executable_server_name} ${dependencies_pkgs})
target_link_libraries(${executable_server_name} ${library_name})

# Client
add_executable(${executable_client_name}
  src/srv_client_node.cpp
)
ament_target_dependencies(${executable_client_name} ${dependencies_pkgs})
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

ament_export_libraries(${library_name})
ament_export_include_directories(include)
ament_export_dependencies(${dependencies_pkgs})

ament_package()
