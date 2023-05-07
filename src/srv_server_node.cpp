#include "ros2-service/srv_server.hpp"

// ROS2
#include <rclcpp/rclcpp.hpp>

int main(int argc, char *argv[])
{
  rclcpp::init(argc, argv);
  auto node = std::make_shared<rs::Server>();
  rclcpp::spin(node);
  rclcpp::shutdown();

  return EXIT_SUCCESS;
}
