#ifndef OPEN_MANIPULATOR_TELEOP_H_
#define OPEN_MANIPULATOR_TELEOP_H_

/*------------------------------------------------------------
 * 필요한 ROS ‧ OpenManipulator 헤더
 * (include 경로가 다르면 프로젝트에 맞게 수정)
 *----------------------------------------------------------*/
#include <ros/ros.h>
#include <open_manipulator_libs/open_manipulator.h>

#include <vector>
#include <string>

/*------------------------------------------------------------
 *  OpenManipulatorTeleop  ―  키보드/외부 명령으로
 *  OpenManipulator 를 조작하는 텔레옵 클래스
 *----------------------------------------------------------*/
class OpenManipulatorTeleop
{
public:
  /* 생성자 & 소멸자 */
  OpenManipulatorTeleop();
  ~OpenManipulatorTeleop();

  /* 키 하나(‘0’ ~ ‘9’ 등)를 받아 해당 포즈·동작 수행 */
  void setGoal(char ch);

  /* 주기적 제어 루프 (timer callback 에서 사용) */
  void controlLoop();

  /* ---------- 터미널 유틸 (Linux) ---------- */
  static void restoreTerminalSettings(void);
  static void disableWaitingForEnter(void);
  static int  getch(void);

private:
  /* ROS */
  ros::NodeHandle nh_;
  ros::Timer      timer_;

  /* 매니퓰레이터 핸들 */
  open_manipulator_libs::OpenManipulator* open_manipulator_;

  /* 사용자 파라미터 (예: 경로 시간) */
  double path_time_;

  /* 필요한 경우: 현재 관절/엔드이펙터 상태·플래그 등
     (원본 .cpp 에 있던 멤버 변수를 여기에도 선언) */
};

#endif /* OPEN_MANIPULATOR_TELEOP_H_ */
