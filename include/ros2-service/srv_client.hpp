#ifndef ROS2_SERVICE_SRV_CLIENT_HPP
#define ROS2_SERVICE_SRV_CLIENT_HPP

#include "ros2-service/constants.hpp"

// ROS2
#include <rclcpp/rclcpp.hpp>
#include <rclcpp/client.hpp>
#include <std_srvs/srv/trigger.hpp>

// STL
#include <memory>
#include <string>
#include <chrono>

namespace rs
{
  class Client : public rclcpp::Node
  {
  public:
    Client();
    ~Client();

  private:
    rclcpp::Logger lg_;
    rclcpp::TimerBase::SharedPtr client_timer_;
    rclcpp::Client<std_srvs::srv::Trigger>::SharedPtr client_;

    void callServer();
    void serviceCB(rclcpp::Client<std_srvs::srv::Trigger>::SharedFuture future);
  };
} // namespace rs

#endif /* ROS2_SERVICE_SRV_CLIENT_HPP */
