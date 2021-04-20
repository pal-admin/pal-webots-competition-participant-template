#include <vector>
#include <webots/Lidar.hpp>
#include <webots/Motor.hpp>
#include <webots/Field.hpp>
#include <webots/Supervisor.hpp>

using namespace webots;
using namespace std;

int main() {
  Supervisor* robot = new Supervisor();
  
  // Get timestep
  const int time_step = robot->getBasicTimeStep();
  
  // Get devices
  Motor* motor_left = robot->getMotor("wheel_left_joint");
  Motor* motor_right = robot->getMotor("wheel_right_joint");
  Lidar* lidar = robot->getLidar("Hokuyo URG-04LX-UG01");
  
  // Get POI list
  vector<Node*> poi_list(10);
  poi_list[0] = robot->getFromDef("POI_1");
  poi_list[1] = robot->getFromDef("POI_2");
  poi_list[2] = robot->getFromDef("POI_3");
  poi_list[3] = robot->getFromDef("POI_4");
  poi_list[4] = robot->getFromDef("POI_5");
  poi_list[5] = robot->getFromDef("POI_6");
  poi_list[6] = robot->getFromDef("POI_7");
  poi_list[7] = robot->getFromDef("POI_8");
  poi_list[8] = robot->getFromDef("POI_9");
  poi_list[9] = robot->getFromDef("POI_F");
  
  vector<Field*> poi_trans_fields(10);
  for (int i = 0; i < 10; ++i) {
    poi_trans_fields[i] = poi_list[i]->getField("translation");
  }
  
  // Get robot node
  Node* robot_node = robot->getFromDef("PARTICIPANT_ROBOT");
  Field* trans_field = robot_node->getField("translation");
  
  // Define lidar variables
  lidar->enable(time_step);
  const int lidar_size = lidar->getHorizontalResolution();
  const double lidar_max_range = lidar->getMaxRange();
  
  // EXAMPLE
  
  motor_left->setPosition(INFINITY);
  motor_right->setPosition(INFINITY);
  motor_left->setVelocity(0);
  motor_right->setVelocity(0);
  
  while (robot->step(time_step) != -1) {
    const float *lidar_image = lidar->getRangeImage();
    const double *robot_values = trans_field->getSFVec3f();
    const double *poi_values = poi_trans_fields[9]->getSFVec3f();
    
    if (poi_values[0] > robot_values[0] && lidar_image[lidar_size/2] > lidar_max_range/2) {
      motor_left->setVelocity(5);
      motor_right->setVelocity(5);
    }
    else {
      motor_left->setVelocity(0);
      motor_right->setVelocity(0);
    }
  }
}
