################################################################################
# Set minimum required version of cmake, project name and compile options
################################################################################
cmake_minimum_required(VERSION 3.0.2)
project(open_manipulator_teleop)

add_compile_options(-std=c++11)

################################################################################
# Find catkin packages and libraries for catkin and system dependencies
################################################################################
find_package(catkin REQUIRED COMPONENTS
    roscpp
    std_msgs
    sensor_msgs
    open_manipulator_msgs
    open_manipulator_libs
)

################################################################################
# Setup for python modules and scripts
################################################################################

################################################################################
# Declare ROS messages, services and actions
################################################################################

################################################################################
## Declare ROS dynamic reconfigure parameters
################################################################################

################################################################################
# Declare catkin specific configuration to be passed to dependent projects
################################################################################
catkin_package(
  INCLUDE_DIRS include
  CATKIN_DEPENDS roscpp std_msgs sensor_msgs open_manipulator_msgs open_manipulator_libs
)

################################################################################
# Build
################################################################################
include_directories(
  include
  ${catkin_INCLUDE_DIRS}
)

add_library(open_manipulator_teleop_core
  src/open_manipulator_teleop_core.cpp          # ← (구현부만 담겨 있는 새 파일)
)
target_link_libraries(open_manipulator_teleop_core ${catkin_LIBRARIES})

add_executable(open_manipulator_teleop_keyboard
  src/open_manipulator_teleop_keyboard.cpp)
target_link_libraries(open_manipulator_teleop_keyboard
  open_manipulator_teleop_core                  # ★
  ${catkin_LIBRARIES})
add_dependencies(open_manipulator_teleop_keyboard
  ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})

add_executable(open_manipulator_teleop_joystick
  src/open_manipulator_teleop_joystick.cpp)
target_link_libraries(open_manipulator_teleop_joystick
  open_manipulator_teleop_core                  # ★
  ${catkin_LIBRARIES})
add_dependencies(open_manipulator_teleop_joystick
  ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})

add_executable(coffee_cycle_executor
  src/coffee_cycle_executor.cpp)
target_link_libraries(coffee_cycle_executor
  open_manipulator_teleop_core                  # ★
  ${catkin_LIBRARIES})
add_dependencies(coffee_cycle_executor
  ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})

# add_executable(open_manipulator_teleop_keyboard src/open_manipulator_teleop_keyboard.cpp)
# add_dependencies(open_manipulator_teleop_keyboard ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
# target_link_libraries(open_manipulator_teleop_keyboard ${catkin_LIBRARIES} )

# add_executable(open_manipulator_teleop_joystick src/open_manipulator_teleop_joystick.cpp)
# add_dependencies(open_manipulator_teleop_joystick ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
# target_link_libraries(open_manipulator_teleop_joystick ${catkin_LIBRARIES} )

# # cycle
# add_executable(coffee_cycle_executor src/coffee_cycle_executor.cpp)
# add_dependencies(coffee_cycle_executor ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
# target_link_libraries(coffee_cycle_executor ${catkin_LIBRARIES})

################################################################################
# Install
################################################################################
install(TARGETS open_manipulator_teleop_keyboard open_manipulator_teleop_joystick coffee_cycle_executor
  RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)

install(DIRECTORY include/${PROJECT_NAME}/
  DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION}
)

install(DIRECTORY launch
  DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}
)

################################################################################
# Test
################################################################################
