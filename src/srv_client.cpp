#include "ros2-service/srv_client.hpp"

namespace rs
{
  Client::Client()
  : rclcpp::Node(CLIENT_NODE_NAME)
  , lg_{get_logger()}
  {
    client_ = this->create_client<std_srvs::srv::Trigger>(SRV_NAME);

    while (!client_->wait_for_service(std::chrono::seconds(1)))
    {
      if (!rclcpp::ok())
      {
        RCLCPP_INFO(lg_, "Interrupted while waiting for service server. Exiting.");
        return;
      }
      RCLCPP_INFO_THROTTLE(lg_, *this->get_clock(), 5000, "Waiting for service server to be available...");
    }

    // Start a timer to call the service server periodically.
    client_timer_ = this->create_wall_timer(std::chrono::milliseconds(1000),
      [this]()
      {
        this->callServer();
      }
    );

    RCLCPP_INFO(lg_, "srv_client_node will start to call the service periodically to enable/disable plugin service.");
  }

  Client::~Client()
  {
  }

  void Client::callServer()
  {
    // Create request
    auto req = std::make_shared<std_srvs::srv::Trigger::Request>();
    // Send request (result will come back in the form of callback)
    // Hence, result here is unused.
    auto result = client_->async_send_request(req, [this](rclcpp::Client<std_srvs::srv::Trigger>::SharedFuture future){ this->serviceCB(future); });
  }

  void Client::serviceCB(rclcpp::Client<std_srvs::srv::Trigger>::SharedFuture future)
  {
    // Wait for result
    // if (std::future_status::ready == future.wait_for(std::chrono::milliseconds(500)))
    // {
      auto result = future.get();
      if (result->success)
      {
        RCLCPP_INFO_STREAM(lg_, "Successfully with message: " << result->message.c_str());
      }
      else
      {
        RCLCPP_WARN_STREAM(lg_, "Failed with message: " << result->message.c_str());
      }
    // }
    // else
    // {
    //   RCLCPP_WARN_STREAM(lg_, "[timeout] Service server did not get back in time.");
    // }
  }
} // namespace rs