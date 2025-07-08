from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    return LaunchDescription([
        Node(
            package='cpp_srvcli',
            executable='server',
            name='server_node',
            output='screen'
        ),
        Node(
            package='cpp_srvcli',
            executable='client',
            name='client_node',
            output='screen',
            arguments=['5', '7']
        )
    ])
