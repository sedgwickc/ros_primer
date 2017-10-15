# ros_primer
A set of two nodes created to demonstrate the use publishing and subscribing to communicate. The two nodes will each prompt the user to  enter a number with the sum of the two numbers printed by the first node.

# Prerequisites
1. ROS Kinetic

# Execution
1. clone into src folder under catkin workspace 
2. build workspace
3. run ```source $WORKSPACE/devel/setup.bash```
4. run roscore
5. open two new terminals and source setup.bash in each
6. in the first terminal, run ```rosrun arvp_challenge chllng_1```
7. in the second terminal, run ```rosrun arvp_challenge chllng_2```
8. follow prompts from nodes
