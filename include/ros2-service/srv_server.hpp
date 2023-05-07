#ifndef ROS2_SERVICE_SRV_SERVER_HPP
#define ROS2_SERVICE_SRV_SERVER_HPP

#include "ros2-service/constants.hpp"

// ROS2
#include <rclcpp/rclcpp.hpp>
#include <rclcpp/service.hpp>
#include <std_srvs/srv/trigger.hpp>

// STL
#include <memory>
#include <string>

namespace rs
{
  class Server : public rclcpp::Node
  {
  public:
    Server();
    ~Server();

  private:
    rclcpp::Logger lg_;
    int count_;
    rclcpp::Service<std_srvs::srv::Trigger>::SharedPtr srv_server_;
    void triggerCB(
      const std::shared_ptr<std_srvs::srv::Trigger::Request> req,
      std::shared_ptr<std_srvs::srv::Trigger::Response> res
    );
  };

} // namespace rs

#endif /* ROS2_SERVICE_SRV_SERVER_HPP */
