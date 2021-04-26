#!/usr/bin/env python3

from controller import Robot, Lidar

# Initialize the robot
robot = Robot()
timestep = int(robot.getBasicTimeStep())

# Initialize motors
motor_left = robot.getDevice('wheel_left_joint')
motor_right = robot.getDevice('wheel_right_joint')
lidar = robot.getDevice('Hokuyo URG-04LX-UG01')
position = robot.getDevice('gps')

poi_list = []
poi_string_list = robot.getCustomData().split()

for i in range(10):
    poi_element = [float(poi_string_list[2*i]), float(poi_string_list[2*i+1])]
    poi_list.append(poi_element)

position.enable(timestep)
lidar.enable(timestep)
lidar_size = lidar.getHorizontalResolution()
lidar_max_range = lidar.getMaxRange()

motor_left.setPosition(float('inf'))
motor_right.setPosition(float('inf'))
motor_left.setVelocity(0)
motor_right.setVelocity(0)

while robot.step(timestep) != -1:
    lidar_image = lidar.getRangeImage()

    if lidar_image[lidar_size//2] > lidar_max_range/10:
        motor_left.setVelocity(5)
        motor_right.setVelocity(5)
    elif poi_list[9][0] > position.getValues()[0]:
        motor_left.setVelocity(0)
        motor_right.setVelocity(0)
    else:
        motor_left.setVelocity(-2)
        motor_right.setVelocity(2)
