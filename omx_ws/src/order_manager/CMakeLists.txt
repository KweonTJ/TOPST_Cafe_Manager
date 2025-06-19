cmake_minimum_required(VERSION 3.0.2)
project(order_manager)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  std_msgs
  rospy
)
find_package(OpenCV REQUIRED)
find_package(PkgConfig REQUIRED)
pkg_check_modules(ZBAR REQUIRED zbar)

catkin_package(
  CATKIN_DEPENDS roscpp std_msgs
  DEPENDS OpenCV
)

include_directories(
  ${catkin_INCLUDE_DIRS}
  ${OpenCV_INCLUDE_DIRS}
  ${ZBAR_INCLUDE_DIRS}
)

add_executable(order_manager src/order_manager.cpp)
target_link_libraries(order_manager ${catkin_LIBRARIES})

add_executable(camera_qr_publisher src/qr_detect.cpp)
target_link_libraries(camera_qr_publisher
   ${catkin_LIBRARIES}
   ${OpenCV_LIBRARIES}
   ${ZBAR_LIBRARIES}
)

catkin_install_python(
  PROGRAMS scripts/serial_to_ros.py
  DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)
