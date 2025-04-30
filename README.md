# ROS2 Service

This repository demonstrates the usage of ROS2 services.

## Creating the Package

```bash
ros2 pkg create ros2-service --build-type ament_cmake --dependencies rclcpp rclpy rclcpp_lifecycle rcpcpp_components
```

## Usage

Start server:  
```bash
ros2 run ros2-service srv_server_node
```

In another terminal, start client:  
```bash
ros2 run ros2-service srv_client_node
```

## References
- https://docs.ros.org/en/galactic/Tutorials/Beginner-Client-Libraries/Writing-A-Simple-Cpp-Service-And-Client.html
- https://get-help.robotigniteacademy.com/t/ros2-service-client-in-c-with-classes-with-node-inheritance/19647
