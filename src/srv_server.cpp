#include "ros2-service/srv_server.hpp"

namespace rs
{
  Server::Server()
  : rclcpp::Node(SERVER_NODE_NAME)
  , lg_{get_logger()}
  , count_{0}
  {
    RCLCPP_INFO(lg_, "Initializing srv_server_node...");
    srv_server_ = this->create_service<std_srvs::srv::Trigger>(SRV_NAME,
      [this](const std::shared_ptr<std_srvs::srv::Trigger::Request> req,
             std::shared_ptr<std_srvs::srv::Trigger::Response> res
      )
      {
        this->triggerCB(req, res);
      }
    );
    RCLCPP_INFO(lg_, "Server is ready.");
  }

  Server::~Server()
  {
  }

  void Server::triggerCB(
      const std::shared_ptr<std_srvs::srv::Trigger::Request> req,
      std::shared_ptr<std_srvs::srv::Trigger::Response> res)
  {
    RCLCPP_INFO_STREAM(lg_, "Incoming request #" << count_ << ".");
    if ( (count_ % 2) == 0 )
    {
      res->message = { "Successfully Enabled Plugin." };
      RCLCPP_INFO_STREAM(lg_, "Successfully Enabled Plugin.");
    }
    else
    {
      res->message = { "Successfully Disabled Plugin." };
      RCLCPP_INFO_STREAM(lg_, "Successfully Disabled Plugin.");
    }
    res->success = true;
    count_++;
  }
} // namespace rs