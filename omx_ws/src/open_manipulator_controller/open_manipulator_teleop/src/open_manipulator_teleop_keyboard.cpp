/*******************************************************************************
* Copyright 2018 ROBOTIS CO., LTD.
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*     http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*******************************************************************************/

/* Authors: Darby Lim, Hye-Jong KIM, Ryan Shim, Yong-Ho Na */

#include "open_manipulator_teleop/open_manipulator_teleop_keyboard.h"
//#include "open_manipulator_teleop/open_manipulator_teleop.h"

// OpenManipulatorTeleop::OpenManipulatorTeleop()
// : node_handle_(""),
//   priv_node_handle_("~")
// {
//   /************************************************************
//   ** Initialize variables
//   ************************************************************/
//   present_joint_angle_.resize(NUM_OF_JOINT);
//   present_kinematic_position_.resize(3);

//   /************************************************************
//   ** Initialize ROS Subscribers and Clients
//   ************************************************************/
//   initSubscriber();
//   initClient();

//   disableWaitingForEnter();
//   ROS_INFO("OpenManipulator teleoperation using keyboard start");
// }

// OpenManipulatorTeleop::~OpenManipulatorTeleop()
// {
//   restoreTerminalSettings();
//   ROS_INFO("Terminate OpenManipulator Joystick");
//   ros::shutdown();
// }

// void OpenManipulatorTeleop::initClient()
// {
//   goal_joint_space_path_client_ = node_handle_.serviceClient<open_manipulator_msgs::SetJointPosition>("goal_joint_space_path");
//   goal_joint_space_path_from_present_client_ = node_handle_.serviceClient<open_manipulator_msgs::SetJointPosition>("goal_joint_space_path_from_present");
//   goal_task_space_path_from_present_position_only_client_ = node_handle_.serviceClient<open_manipulator_msgs::SetKinematicsPose>("goal_task_space_path_from_present_position_only");
//   goal_tool_control_client_ = node_handle_.serviceClient<open_manipulator_msgs::SetJointPosition>("goal_tool_control");
// }

// void OpenManipulatorTeleop::initSubscriber()
// {
//   joint_states_sub_ = node_handle_.subscribe("joint_states", 10, &OpenManipulatorTeleop::jointStatesCallback, this);
//   kinematics_pose_sub_ = node_handle_.subscribe("kinematics_pose", 10, &OpenManipulatorTeleop::kinematicsPoseCallback, this);
// }

// void OpenManipulatorTeleop::jointStatesCallback(const sensor_msgs::JointState::ConstPtr &msg)
// {
//   std::vector<double> temp_angle;
//   temp_angle.resize(NUM_OF_JOINT);
//   for (std::vector<int>::size_type i = 0; i < msg->name.size(); i ++)
//   {
//     if (!msg->name.at(i).compare("joint1"))  temp_angle.at(0) = (msg->position.at(i));
//     else if (!msg->name.at(i).compare("joint2"))  temp_angle.at(1) = (msg->position.at(i));
//     else if (!msg->name.at(i).compare("joint3"))  temp_angle.at(2) = (msg->position.at(i));
//     else if (!msg->name.at(i).compare("joint4"))  temp_angle.at(3) = (msg->position.at(i));
//     else if (!msg->name.at(i).compare("joint5"))  temp_angle.at(4) = (msg->position.at(i));
//   }
//   present_joint_angle_ = temp_angle;
// }

// void OpenManipulatorTeleop::kinematicsPoseCallback(const open_manipulator_msgs::KinematicsPose::ConstPtr &msg)
// {
//   std::vector<double> temp_position;
//   temp_position.push_back(msg->pose.position.x);
//   temp_position.push_back(msg->pose.position.y);
//   temp_position.push_back(msg->pose.position.z);
//   present_kinematic_position_ = temp_position;
// }

// std::vector<double> OpenManipulatorTeleop::getPresentJointAngle()
// {
//   return present_joint_angle_;
// }

// std::vector<double> OpenManipulatorTeleop::getPresentKinematicsPose()
// {
//   return present_kinematic_position_;
// }

// bool OpenManipulatorTeleop::setJointSpacePathFromPresent(std::vector<std::string> joint_name, std::vector<double> joint_angle, double path_time)
// {
//   open_manipulator_msgs::SetJointPosition srv;
//   srv.request.joint_position.joint_name = joint_name;
//   srv.request.joint_position.position = joint_angle;
//   srv.request.path_time = path_time;

//   if (goal_joint_space_path_from_present_client_.call(srv))
//   {
//     return srv.response.is_planned;
//   }
//   return false;
// }

// bool OpenManipulatorTeleop::setJointSpacePath(std::vector<std::string> joint_name, std::vector<double> joint_angle, double path_time)
// {
//   open_manipulator_msgs::SetJointPosition srv;
//   srv.request.joint_position.joint_name = joint_name;
//   srv.request.joint_position.position = joint_angle;
//   srv.request.path_time = path_time;

//   if (goal_joint_space_path_client_.call(srv))
//   {
//     return srv.response.is_planned;
//   }
//   return false;
// }

// bool OpenManipulatorTeleop::setToolControl(std::vector<double> joint_angle)
// {
//   open_manipulator_msgs::SetJointPosition srv;
//   srv.request.joint_position.joint_name.push_back(priv_node_handle_.param<std::string>("end_effector_name", "gripper"));
//   srv.request.joint_position.position = joint_angle;

//   if (goal_tool_control_client_.call(srv))
//   {
//     return srv.response.is_planned;
//   }
//   return false;
// }

// bool OpenManipulatorTeleop::setTaskSpacePathFromPresentPositionOnly(std::vector<double> kinematics_pose, double path_time)
// {
//   open_manipulator_msgs::SetKinematicsPose srv;
//   srv.request.planning_group = priv_node_handle_.param<std::string>("end_effector_name", "gripper");
//   srv.request.kinematics_pose.pose.position.x = kinematics_pose.at(0);
//   srv.request.kinematics_pose.pose.position.y = kinematics_pose.at(1);
//   srv.request.kinematics_pose.pose.position.z = kinematics_pose.at(2);
//   srv.request.path_time = path_time;

//   if (goal_task_space_path_from_present_position_only_client_.call(srv))
//   {
//     return srv.response.is_planned;
//   }
//   return false;
// }

// void OpenManipulatorTeleop::printText()
// {
//   printf("\n");
//   printf("---------------------------\n");
//   printf("Control Your OpenManipulator!\n");
//   printf("---------------------------\n");
//   printf("w : increase x axis in task space\n");
//   printf("s : decrease x axis in task space\n");
//   printf("a : increase y axis in task space\n");
//   printf("d : decrease y axis in task space\n");
//   printf("z : increase z axis in task space\n");
//   printf("x : decrease z axis in task space\n");
//   printf("\n");
//   printf("y : increase joint 1 angle\n");
//   printf("h : decrease joint 1 angle\n");
//   printf("u : increase joint 2 angle\n");
//   printf("j : decrease joint 2 angle\n");
//   printf("i : increase joint 3 angle\n");
//   printf("k : decrease joint 3 angle\n");
//   printf("o : increase joint 4 angle\n");
//   printf("l : decrease joint 4 angle\n");
//   printf("\n");
//   printf("g : gripper open\n");
//   printf("f : gripper close\n");
//   printf("\n");
//   printf("1 : setting1 pose\n");
//   printf("2 : setting2 pose\n");
//   printf("3 : setting3 pose\n");
//   printf("4 : setting4 pose\n");
//   printf("5 : setting5 pose (rsest)\n");
//   printf("6 : setting6 pose\n");
//   printf("7 : setting7 pose\n");
//   printf("0 : setting0 pose\n");
//   printf("       \n");
//   printf("q to quit\n");
//   printf("---------------------------\n");
//   printf("Present Joint Angle J1: %.3lf J2: %.3lf J3: %.3lf J4: %.3lf\n",
//          getPresentJointAngle().at(0),
//          getPresentJointAngle().at(1),
//          getPresentJointAngle().at(2),
//          getPresentJointAngle().at(3));
//   printf("Present Kinematics Position X: %.3lf Y: %.3lf Z: %.3lf\n",
//          getPresentKinematicsPose().at(0),
//          getPresentKinematicsPose().at(1),
//          getPresentKinematicsPose().at(2));
//   printf("---------------------------\n");

// }

// void OpenManipulatorTeleop::setGoal(char ch)
// {
//   std::vector<double> goalPose;  goalPose.resize(3, 0.0);
//   std::vector<double> goalJoint; goalJoint.resize(NUM_OF_JOINT, 0.0);

//   if (ch == 'w' || ch == 'W')
//   {
//     printf("input : w \tincrease(++) x axis in task space\n");
//     goalPose.at(0) = DELTA;
//     setTaskSpacePathFromPresentPositionOnly(goalPose, PATH_TIME);
//   }
//   else if (ch == 's' || ch == 'S')
//   {
//     printf("input : s \tdecrease(--) x axis in task space\n");
//     goalPose.at(0) = -DELTA;
//     setTaskSpacePathFromPresentPositionOnly(goalPose, PATH_TIME);
//   }
//   else if (ch == 'a' || ch == 'A')
//   {
//     printf("input : a \tincrease(++) y axis in task space\n");
//     goalPose.at(1) = DELTA;
//     setTaskSpacePathFromPresentPositionOnly(goalPose, PATH_TIME);
//   }
//   else if (ch == 'd' || ch == 'D')
//   {
//     printf("input : d \tdecrease(--) y axis in task space\n");
//     goalPose.at(1) = -DELTA;
//     setTaskSpacePathFromPresentPositionOnly(goalPose, PATH_TIME);
//   }
//   else if (ch == 'z' || ch == 'Z')
//   {
//     printf("input : z \tincrease(++) z axis in task space\n");
//     goalPose.at(2) = DELTA;
//     setTaskSpacePathFromPresentPositionOnly(goalPose, PATH_TIME);
//   }
//   else if (ch == 'x' || ch == 'X')
//   {
//     printf("input : x \tdecrease(--) z axis in task space\n");
//     goalPose.at(2) = -DELTA;
//     setTaskSpacePathFromPresentPositionOnly(goalPose, PATH_TIME);
//   }
//   else if (ch == 'y' || ch == 'Y')
//   {
//     printf("input : y \tincrease(++) joint 1 angle\n");
//     std::vector<std::string> joint_name;
//     joint_name.push_back("joint1"); goalJoint.at(0) = JOINT_DELTA;
//     joint_name.push_back("joint2");
//     joint_name.push_back("joint3");
//     joint_name.push_back("joint4");
//     setJointSpacePathFromPresent(joint_name, goalJoint, PATH_TIME);
//   }
//   else if (ch == 'h' || ch == 'H')
//   {
//     printf("input : h \tdecrease(--) joint 1 angle\n");
//     std::vector<std::string> joint_name;
//     joint_name.push_back("joint1"); goalJoint.at(0) = -JOINT_DELTA;
//     joint_name.push_back("joint2");
//     joint_name.push_back("joint3");
//     joint_name.push_back("joint4");
//     setJointSpacePathFromPresent(joint_name, goalJoint, PATH_TIME);
//   }
//   else if (ch == 'u' || ch == 'U')
//   {
//     printf("input : u \tincrease(++) joint 2 angle\n");
//     std::vector<std::string> joint_name;
//     joint_name.push_back("joint1");
//     joint_name.push_back("joint2"); goalJoint.at(1) = JOINT_DELTA;
//     joint_name.push_back("joint3");
//     joint_name.push_back("joint4");
//     setJointSpacePathFromPresent(joint_name, goalJoint, PATH_TIME);
//   }
//   else if (ch == 'j' || ch == 'J')
//   {
//     printf("input : j \tdecrease(--) joint 2 angle\n");
//     std::vector<std::string> joint_name;
//     joint_name.push_back("joint1");
//     joint_name.push_back("joint2"); goalJoint.at(1) = -JOINT_DELTA;
//     joint_name.push_back("joint3");
//     joint_name.push_back("joint4");
//     setJointSpacePathFromPresent(joint_name, goalJoint, PATH_TIME);
//   }
//   else if (ch == 'i' || ch == 'I')
//   {
//     printf("input : i \tincrease(++) joint 3 angle\n");
//     std::vector<std::string> joint_name;
//     joint_name.push_back("joint1");
//     joint_name.push_back("joint2");
//     joint_name.push_back("joint3"); goalJoint.at(2) = JOINT_DELTA;
//     joint_name.push_back("joint4");
//     setJointSpacePathFromPresent(joint_name, goalJoint, PATH_TIME);
//   }
//   else if (ch == 'k' || ch == 'K')
//   {
//     printf("input : k \tdecrease(--) joint 3 angle\n");
//     std::vector<std::string> joint_name;
//     joint_name.push_back("joint1");
//     joint_name.push_back("joint2");
//     joint_name.push_back("joint3"); goalJoint.at(2) = -JOINT_DELTA;
//     joint_name.push_back("joint4");
//     setJointSpacePathFromPresent(joint_name, goalJoint, PATH_TIME);
//   }
//   else if (ch == 'o' || ch == 'O')
//   {
//     printf("input : o \tincrease(++) joint 4 angle\n");
//     std::vector<std::string> joint_name;
//     joint_name.push_back("joint1");
//     joint_name.push_back("joint2");
//     joint_name.push_back("joint3");
//     joint_name.push_back("joint4"); goalJoint.at(3) = JOINT_DELTA;
//     setJointSpacePathFromPresent(joint_name, goalJoint, PATH_TIME);
//   }
//   else if (ch == 'l' || ch == 'L')
//   {
//     printf("input : l \tdecrease(--) joint 4 angle\n");
//     std::vector<std::string> joint_name;
//     joint_name.push_back("joint1");
//     joint_name.push_back("joint2");
//     joint_name.push_back("joint3");
//     joint_name.push_back("joint4"); goalJoint.at(3) = -JOINT_DELTA;
//     setJointSpacePathFromPresent(joint_name, goalJoint, PATH_TIME);
//   }
//   else if (ch == 'g' || ch == 'G')
//   {
//     printf("input : g \topen gripper\n");
//     std::vector<double> joint_angle;

//     joint_angle.push_back(0.01);
//     setToolControl(joint_angle);
//   }
//   else if (ch == 'f' || ch == 'F')
//   {
//     printf("input : f \tclose gripper\n");
//     std::vector<double> joint_angle;
//     joint_angle.push_back(-0.01);
//     setToolControl(joint_angle);
//   }
//   else if (ch == '0')
// {
//   printf("input : 0 \tsetting0 pose (with gripper closed first)\n");

//   // 1) 그리퍼 먼저 열기
//   {
//     std::vector<double> tool_angle;
//     tool_angle.push_back(0.01);    // 그리퍼 열기
//     setToolControl(tool_angle);
//     ros::Duration(0.5).sleep();     // 닫힘 동작 완료 대기
//   }

//   // 2) Joint 0번(초기) 포즈로 이동
//   {
//     std::vector<std::string> joint_name;
//     std::vector<double> joint_angle;
//     double path_time = 2.0;

//     joint_name.push_back("joint1"); joint_angle.push_back(2.391);
//     joint_name.push_back("joint2"); joint_angle.push_back(-0.094);
//     joint_name.push_back("joint3"); joint_angle.push_back(0.690);
//     joint_name.push_back("joint4"); joint_angle.push_back(-1.307);

//     setJointSpacePath(joint_name, joint_angle, path_time);
//   }
// }
// else if (ch == '7')
// {
//   printf("input : 7 \tcustom pose\n");

//   // Joint 7번 포즈로 이동
//   std::vector<std::string> joint_name;
//   std::vector<double> joint_angle;
//   double path_time = 2.0;

//   joint_name.push_back("joint1"); joint_angle.push_back(2.138);
//   joint_name.push_back("joint2"); joint_angle.push_back(0.792);
//   joint_name.push_back("joint3"); joint_angle.push_back(-0.851);
//   joint_name.push_back("joint4"); joint_angle.push_back(-0.782);

//   setJointSpacePath(joint_name, joint_angle, path_time);
// }

// else if (ch == '6')
// {
//   printf("input : 6 \tcustom pose\n");

//   // Joint 6번 포즈로 이동
//   std::vector<std::string> joint_name;
//   std::vector<double> joint_angle;
//   double path_time = 2.0;

//   joint_name.push_back("joint1"); joint_angle.push_back(2.643);
//   joint_name.push_back("joint2"); joint_angle.push_back(0.836);
//   joint_name.push_back("joint3"); joint_angle.push_back(-0.845);
//   joint_name.push_back("joint4"); joint_angle.push_back(-0.776);

//   setJointSpacePath(joint_name, joint_angle, path_time);
// }

// else if (ch == '5')
// {
//   printf("input : 5 \treset pose\n");

//   // Joint 5번 포즈로 이동
//   std::vector<std::string> joint_name;
//   std::vector<double> joint_angle;
//   double path_time = 2.0;

//   joint_name.push_back("joint1"); joint_angle.push_back(2.391);
//   joint_name.push_back("joint2"); joint_angle.push_back(-0.037);
//   joint_name.push_back("joint3"); joint_angle.push_back(-0.402);
//   joint_name.push_back("joint4"); joint_angle.push_back(1.269);

//   setJointSpacePath(joint_name, joint_angle, path_time);
// }

//   else if (ch == '4')
// {
//   printf("input : 4 \tsetting4 pose\n");

//   // 1) Joint 4번 포즈로 이동
//   {
//     std::vector<std::string> joint_name;
//     std::vector<double> joint_angle;
//     double path_time = 2.0;

//     joint_name.push_back("joint1"); joint_angle.push_back(0.782);
//     joint_name.push_back("joint2"); joint_angle.push_back(0.186);
//     joint_name.push_back("joint3"); joint_angle.push_back(0.479);
//     joint_name.push_back("joint4"); joint_angle.push_back(-1.341);
//     setJointSpacePath(joint_name, joint_angle, path_time);
    
//     // 이동이 완료될 때까지 대기
//     ros::Duration(path_time).sleep();
//   }

//   // 2) 그리퍼 열기
//   {
//     std::vector<double> tool_angle;
//     tool_angle.push_back(0.01);   // 그리퍼 열기
//     setToolControl(tool_angle);
//   }
// }
//   else if (ch == '3')
//   {
//     printf("input : 3 \tsetting3 pose\n");
    
//     {
//     	// 그리퍼 열기
//     	std::vector<double> tool_angle;
//     	tool_angle.push_back(0.01);
//     	setToolControl(tool_angle);
//     	ros::Duration(0.5).sleep();
//     }

//     {// Joint 3번 포즈 설정
//     	std::vector<std::string> joint_name;
//     	std::vector<double> joint_angle;
//     	double path_time = 2.0;
	
//     	joint_name.push_back("joint1"); joint_angle.push_back(0.782);
//     	joint_name.push_back("joint2"); joint_angle.push_back(0.163);
//     	joint_name.push_back("joint3"); joint_angle.push_back(0.440);
//     	joint_name.push_back("joint4"); joint_angle.push_back(-1.310);
//     	setJointSpacePath(joint_name, joint_angle, path_time);
//     }
    	
//   }
//   else if (ch == '2')
//   {
//     printf("input : 2 \tsetting2 pose\n");
//     std::vector<std::string> joint_name;
//     std::vector<double> joint_angle;
//     double path_time = 2.0;

//     joint_name.push_back("joint1"); joint_angle.push_back(0.755);
//     joint_name.push_back("joint2"); joint_angle.push_back(-0.018);
//     joint_name.push_back("joint3"); joint_angle.push_back(0.670);
//     joint_name.push_back("joint4"); joint_angle.push_back(-1.422);
//     setJointSpacePath(joint_name, joint_angle, path_time);
    
//     std::vector<double> tool_angle;
//     tool_angle.push_back(-0.01);
//     setToolControl(tool_angle);
//   }
//   else if (ch == '1')
//   {
//     printf("input : 1 \tsetting1 pose\n");
    
//     // 그리퍼를 먼저 닫기
//   {
//     std::vector<double> tool_angle;
//     tool_angle.push_back(-0.01);  // 그리퍼 닫기
//     setToolControl(tool_angle);
//     ros::Duration(0.5).sleep();   // 닫힘 동작이 완료될 때까지 잠시 대기
//   }

//   // 그 다음 Joint 1번 포즈로 이동
//   {
//     std::vector<std::string> joint_name;
//     std::vector<double> joint_angle;
//     double path_time = 2.0;

//     joint_name.push_back("joint1"); joint_angle.push_back(2.372);
//     joint_name.push_back("joint2"); joint_angle.push_back(0.169);
//     joint_name.push_back("joint3"); joint_angle.push_back(0.509);
//     joint_name.push_back("joint4"); joint_angle.push_back(-1.416);
//     setJointSpacePath(joint_name, joint_angle, path_time);
//   }

//     /*std::vector<std::string> joint_name;
//     std::vector<double> joint_angle;
//     double path_time = 2.0;
//     joint_name.push_back("joint1"); joint_angle.push_back(2.372);
//     joint_name.push_back("joint2"); joint_angle.push_back(0.169);
//     joint_name.push_back("joint3"); joint_angle.push_back(0.509);
//     joint_name.push_back("joint4"); joint_angle.push_back(-1.416);
//     setJointSpacePath(joint_name, joint_angle, path_time);
    
//     std::vector<double> tool_angle;
//     tool_angle.push_back(-0.01);
//     setToolControl(tool_angle);*/
//   }
// }

// void OpenManipulatorTeleop::restoreTerminalSettings(void)
// {
//   tcsetattr(0, TCSANOW, &oldt_);  /* Apply saved settings */
// }

// void OpenManipulatorTeleop::disableWaitingForEnter(void)
// {
//   struct termios newt;

//   tcgetattr(0, &oldt_);  /* Save terminal settings */
//   newt = oldt_;  /* Init new settings */
//   newt.c_lflag &= ~(ICANON | ECHO);  /* Change settings */
//   tcsetattr(0, TCSANOW, &newt);  /* Apply settings */
// }

int main(int argc, char **argv)
{
  // Init ROS node
  ros::init(argc, argv, "open_manipulator_teleop_keyboard");
  OpenManipulatorTeleop openManipulatorTeleop;

  char ch;
  openManipulatorTeleop.printText();
  while (ros::ok() && (ch = std::getchar()) != 'q')
  {
    ros::spinOnce();
    openManipulatorTeleop.printText();
    ros::spinOnce();
    openManipulatorTeleop.setGoal(ch);
  }

  return 0;
}
