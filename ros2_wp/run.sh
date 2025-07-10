#!/bin/bash
colcon build --packages-select node
source install/local_setup.bash
ros2 run node run_node