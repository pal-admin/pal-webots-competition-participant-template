#!/usr/bin/env python3

from controller import Supervisor, Lidar

# Initialize the robot
robot = Supervisor()
timestep = int(robot.getBasicTimeStep())

# Initialize motors
motor_left = robot.getDevice('wheel_left_joint')
motor_right = robot.getDevice('wheel_right_joint')
lidar = robot.getDevice('Hokuyo URG-04LX-UG01')

poi_list = [robot.getFromDef('POI_1'), robot.getFromDef('POI_2'),
            robot.getFromDef('POI_3'), robot.getFromDef('POI_4'),
            robot.getFromDef('POI_5'), robot.getFromDef('POI_6'),
            robot.getFromDef('POI_7'), robot.getFromDef('POI_8'),
            robot.getFromDef('POI_9'), robot.getFromDef('POI_F')]

robot_node = robot.getFromDef('PARTICIPANT_ROBOT')

lidar.enable(timestep)
lidar_size = lidar.getHorizontalResolution()
lidar_max_range = lidar.getMaxRange()

motor_left.setPosition(float('inf'))
motor_right.setPosition(float('inf'))
motor_left.setVelocity(0)
motor_right.setVelocity(0)

while robot.step(timestep) != -1:
    lidar_image = lidar.getRangeImage()

    if poi_list[9].getPosition()[0] > robot_node.getPosition()[0] and lidar_image[lidar_size//2] > lidar_max_range/2:
        motor_left.setVelocity(5)
        motor_right.setVelocity(5)
    else:
        motor_left.setVelocity(0)
        motor_right.setVelocity(0)
