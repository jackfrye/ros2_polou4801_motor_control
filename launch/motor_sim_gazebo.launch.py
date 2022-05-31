import os
from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch.actions import IncludeLaunchDescription
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch.substitutions import Command, FindExecutable, PathJoinSubstitution
from launch_ros.substitutions import FindPackageShare

from launch_ros.actions import Node
import xacro

def generate_launch_description():

    # Specify the name of the package and path to xacro file within the package
    pkg_name = 'ros2_polou4801_motor_control'
    #file_subpath = '../../../../urdf/polou4801.xacro'
    file_subpath = 'urdf/motor_w_femur.xacro'


    # Use xacro to process the file
    xacro_file = os.path.join(get_package_share_directory(pkg_name),file_subpath)
    robot_description_raw = xacro.process_file(xacro_file).toxml()


    # Configure the node
    node_robot_state_publisher = Node(
        package='robot_state_publisher',
        executable='robot_state_publisher',
        namespace='my_ns',
        output='screen',
        parameters=[{'robot_description': robot_description_raw, 
                     'use_sim_time': True}] # add other parameters here if required
    )   

    gazebo = IncludeLaunchDescription(
        PythonLaunchDescriptionSource([os.path.join(
            get_package_share_directory('gazebo_ros'), 'launch'), '/gazebo.launch.py']),
        )

    spawn_entity = Node(
                    package='gazebo_ros', 
                    executable='spawn_entity.py',
                    namespace='my_ns',
                    arguments=['-topic', 'robot_description',
                                '-entity', 'polou4801'],
                    output='screen')



    # Run the node
    return LaunchDescription([
        gazebo,
        node_robot_state_publisher,
        spawn_entity
    ])

