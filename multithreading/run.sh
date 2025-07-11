#!/bin/bash
colcon build --packages-select many_to_many
source install/local_setup.bash
ros2 run many_to_many many1

