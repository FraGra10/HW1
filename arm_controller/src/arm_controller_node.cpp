#include "ros/ros.h"
#include "std_msgs/Float64.h"
#include <sensor_msgs/JointState.h>
#include "std_msgs/String.h"
#include <sstream>

void Call_Fun(const sensor_msgs::JointState::ConstPtr& msg)
{
  for (size_t i = 0; i < msg->position.size(); i++) 
    {
        ROS_INFO("Joint Name: %s, Position: %f", msg->name[i].c_str(), msg->position[i]);
    }
}



int main(int argc, char **argv)
{


    ros::init(argc, argv, "arm_controller_node");
    ros::NodeHandle n;
    
// ********************** SUBSCRIBER **************************
   ros::Subscriber joint_states_sub = n.subscribe("/arm/joint_states", 10, Call_Fun);

// ********************** PUBLISHER **************************

    ros::Publisher j0_controller_pub = n.advertise<std_msgs::Float64>("/arm/PositionJointInterface_J0_controller/command", 10);
    ros::Publisher j1_controller_pub = n.advertise<std_msgs::Float64>("/arm/PositionJointInterface_J1_controller/command", 10);
    ros::Publisher j2_controller_pub = n.advertise<std_msgs::Float64>("/arm/PositionJointInterface_J2_controller/command", 10);
    ros::Publisher j3_controller_pub = n.advertise<std_msgs::Float64>("/arm/PositionJointInterface_J3_controller/command", 10);
    
    ros::Rate loop_rate(10);


    std_msgs::Float64 J2_command;
    
    while (ros::ok())
    {
        std_msgs::Float64 J0_command;
        std_msgs::Float64 J1_command;
        std_msgs::Float64 J2_command;
        std_msgs::Float64 J3_command;
        
         J0_command.data = 0.5;
         j0_controller_pub.publish(J0_command);
        
         J1_command.data = 1;
         j1_controller_pub.publish(J1_command);
        
         J2_command.data = -0.5;
         j2_controller_pub.publish(J2_command);
        
         J3_command.data = 0.8;
         j3_controller_pub.publish(J3_command);


        ros::spinOnce();
        loop_rate.sleep();
    }

    return 0;
}
