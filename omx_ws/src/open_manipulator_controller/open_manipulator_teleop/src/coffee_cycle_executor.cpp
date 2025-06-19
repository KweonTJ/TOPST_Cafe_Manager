/*****************************************************************
 *  coffee_cycle_executor.cpp
 *
 *  /coffee_cycle  토픽(예: "5 1 2 3 1 6 …")을 구독하여
 *  기존 Teleop 클래스(OpenManipulatorTeleop)의 setGoal(char) 을
 *  순서대로 호출해 자동으로 한 사이클을 수행한다.
 *****************************************************************/
#include <ros/ros.h>
#include <std_msgs/String.h>
#include <sstream>
#include <vector>
#include <string>
#include "open_manipulator_teleop/open_manipulator_teleop_keyboard.h"
//#include "../include/open_manipulator_teleop/open_manipulator_teleop.h"   // Teleop 헤더 경로
                                                                          // (include path에 맞게 수정)

class CoffeeCycleExecutor
{
public:
  CoffeeCycleExecutor(ros::NodeHandle& nh)
  : teleop_()
  {
    sub_ = nh.subscribe("coffee_cycle", 1,
            &CoffeeCycleExecutor::cycleCallback, this);
    ROS_INFO("CoffeeCycleExecutor ready – waiting for /coffee_cycle …");
  }

private:
  void cycleCallback(const std_msgs::String::ConstPtr& msg)
  {
    /* 문자열 → 공백 구분 int 벡터 */
    std::istringstream iss(msg->data);
    std::vector<int> seq;
    int n;
    while (iss >> n)
      seq.push_back(n);

    if (seq.empty())
    {
      ROS_WARN("Received empty cycle.");
      return;
    }

    ROS_INFO_STREAM("Executing cycle: " << msg->data);

    /* 순서대로 setGoal(char) 호출 */
    for (int cmd : seq)
    {
      char key = '0' + cmd;          // 0 → '0', 5 → '5', …
      teleop_.setGoal(key);          // 기존 Teleop API 재사용
      ros::Duration(2.5).sleep();    // PATH_TIME(2s)+여유 0.5s

      if (cmd == 8) {
        ROS_INFO("Reached step 8 -> waiting 15 seconds before next step...");
        ros::Duration(15.0).sleep();
      }
    }
    ROS_INFO("Cycle finished.");
  }

  ros::Subscriber sub_;
  OpenManipulatorTeleop teleop_;   // 기존 텔레옵 객체
};

int main(int argc, char **argv)
{
  ros::init(argc, argv, "coffee_cycle_executor");
  ros::NodeHandle nh;
  CoffeeCycleExecutor exec(nh);
  
  ros::AsyncSpinner spinner(2);
  spinner.start();
  ros::waitForShutdown();
//  ros::spin();
  return 0;
}
