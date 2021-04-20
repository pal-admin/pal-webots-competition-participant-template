#include <webots/lidar.h>
#include <webots/motor.h>
#include <webots/robot.h>
#include <webots/supervisor.h>


int main(int argc, char **argv) {
  // init webots stuff
  wb_robot_init();

  // Get timestep
  const int time_step = wb_robot_get_basic_time_step();

  // Get devices
  WbDeviceTag motor_left = wb_robot_get_device("wheel_left_joint");
  WbDeviceTag motor_right = wb_robot_get_device("wheel_right_joint");
  WbDeviceTag lidar = wb_robot_get_device("Hokuyo URG-04LX-UG01");

  // Get POI list
  WbNodeRef poi_list[10];
  poi_list[0] = wb_supervisor_node_get_from_def("POI_1");
  poi_list[1] = wb_supervisor_node_get_from_def("POI_2");
  poi_list[2] = wb_supervisor_node_get_from_def("POI_3");
  poi_list[3] = wb_supervisor_node_get_from_def("POI_4");
  poi_list[4] = wb_supervisor_node_get_from_def("POI_5");
  poi_list[5] = wb_supervisor_node_get_from_def("POI_6");
  poi_list[6] = wb_supervisor_node_get_from_def("POI_7");
  poi_list[7] = wb_supervisor_node_get_from_def("POI_8");
  poi_list[8] = wb_supervisor_node_get_from_def("POI_9");
  poi_list[9] = wb_supervisor_node_get_from_def("POI_F");
  
  WbFieldRef poi_trans_fields[10];
  for (int i = 0; i < 10; ++i) {
    poi_trans_fields[i] = wb_supervisor_node_get_field(poi_list[i], "translation");
  }
  
  // Get robot node
  WbNodeRef robot_node = wb_supervisor_node_get_from_def("PARTICIPANT_ROBOT");
  WbFieldRef trans_field = wb_supervisor_node_get_field(robot_node, "translation");

  // Define lidar variables
  wb_lidar_enable(lidar, time_step);
  const int lidar_size = wb_lidar_get_horizontal_resolution(lidar);
  const float lidar_max_range = wb_lidar_get_max_range(lidar);

  // EXAMPLE

  wb_motor_set_position(motor_left, INFINITY);
  wb_motor_set_position(motor_right, INFINITY);
  wb_motor_set_velocity(motor_left, 0);
  wb_motor_set_velocity(motor_right, 0);

  while (wb_robot_step(time_step) != -1) {
    const float *lidar_image = wb_lidar_get_range_image(lidar);
    const double *robot_values = wb_supervisor_field_get_sf_vec3f(trans_field);
    const double *poi_values = wb_supervisor_field_get_sf_vec3f(poi_trans_fields[9]);
    
    if (poi_values[0] > robot_values[0] && lidar_image[lidar_size/2] > lidar_max_range/2) {
      wb_motor_set_velocity(motor_left, 5);
      wb_motor_set_velocity(motor_right, 5);
    }
    else {
      wb_motor_set_velocity(motor_left, 0);
      wb_motor_set_velocity(motor_right, 0);
    }
  }

  // free(braitenberg_coefficients);
  wb_robot_cleanup();

  return 0;
}
