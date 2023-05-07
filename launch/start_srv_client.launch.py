from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
  client_node = Node(
    package='ros2-service',
    executable='srv_client_node',
    name='srv_client_node',
  )

  # Define launch description
  ld = LaunchDescription()
  ld.add_action(client_node)

  # Return launch description
  return ld