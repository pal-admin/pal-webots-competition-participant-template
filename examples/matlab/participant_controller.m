wb_robot_init();

% Initialize the robot
time_step = wb_robot_get_basic_time_step();

% Initialize motors
motor_left = wb_robot_get_device('wheel_left_joint');
motor_right = wb_robot_get_device('wheel_right_joint');
lidar = wb_robot_get_device('Hokuyo URG-04LX-UG01');

poi_list = [wb_supervisor_node_get_from_def('POI_1'),
            wb_supervisor_node_get_from_def('POI_2'),
            wb_supervisor_node_get_from_def('POI_3'),
            wb_supervisor_node_get_from_def('POI_4'),
            wb_supervisor_node_get_from_def('POI_5'),
            wb_supervisor_node_get_from_def('POI_6'),
            wb_supervisor_node_get_from_def('POI_7'),
            wb_supervisor_node_get_from_def('POI_8'),
            wb_supervisor_node_get_from_def('POI_9'),
            wb_supervisor_node_get_from_def('POI_F')];
            
poi_trans_fields = [wb_supervisor_node_get_field(poi_list(1), 'translation'),
                    wb_supervisor_node_get_field(poi_list(2), 'translation'),
                    wb_supervisor_node_get_field(poi_list(3), 'translation'),
                    wb_supervisor_node_get_field(poi_list(4), 'translation'),
                    wb_supervisor_node_get_field(poi_list(5), 'translation'),
                    wb_supervisor_node_get_field(poi_list(6), 'translation'),
                    wb_supervisor_node_get_field(poi_list(7), 'translation'),
                    wb_supervisor_node_get_field(poi_list(8), 'translation'),
                    wb_supervisor_node_get_field(poi_list(9), 'translation'),
                    wb_supervisor_node_get_field(poi_list(10), 'translation')];

% Get robot node
robot_node = wb_supervisor_node_get_from_def('PARTICIPANT_ROBOT');
trans_field = wb_supervisor_node_get_field(robot_node, 'translation');

% Define lidar variables
wb_lidar_enable(lidar, time_step);
lidar_size = wb_lidar_get_horizontal_resolution(lidar);
lidar_max_range = wb_lidar_get_max_range(lidar);

% EXAMPLE

wb_motor_set_position(motor_left, INFINITY);
wb_motor_set_position(motor_right, INFINITY);
wb_motor_set_velocity(motor_left, 0);
wb_motor_set_velocity(motor_right, 0);


while wb_robot_step(time_step) ~= -1
  lidar_image = wb_lidar_get_range_image(lidar);
  robot_values = wb_supervisor_field_get_sf_vec3f(trans_field);
  poi_values = wb_supervisor_field_get_sf_vec3f(poi_trans_fields(10));

  if (poi_values(1) > robot_values(1) && lidar_image(lidar_size/2) > lidar_max_range/2)
    wb_motor_set_velocity(motor_left, 5);
    wb_motor_set_velocity(motor_right, 5);
  else
    wb_motor_set_velocity(motor_left, 5);
    wb_motor_set_velocity(motor_right, 5);
  end
end