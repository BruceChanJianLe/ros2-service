from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
  server_node = Node(
    package='ros2-service',
    executable='srv_server_node',
    name='srv_server_node',
  )

  # Define launch description
  ld = LaunchDescription()
  ld.add_action(server_node)

  # Return launch description
  return ld