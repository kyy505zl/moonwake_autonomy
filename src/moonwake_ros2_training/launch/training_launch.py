import os
from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    # 获取 YAML 配置文件的绝对路径（它会自动去 install 找）
    config = os.path.join(
        get_package_share_directory('moonwake_ros2_training'),
        'config',
        'training_config.yaml'
    )

    return LaunchDescription([
        Node(
            package='moonwake_ros2_training',
            executable='target_offset_publisher',
            name='target_offset_publisher',
            parameters=[config],
            namespace='training'  # 统一加前缀，防串台
        ),
        Node(
            package='moonwake_ros2_training',
            executable='steering_hint_node',
            name='steering_hint_node',
            parameters=[config],
            namespace='training'
        )
    ])
