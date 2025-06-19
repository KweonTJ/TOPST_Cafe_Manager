#!/usr/bin/env python3
#import rospy, serial, serial.serialutil, time
#from std_msgs.msg import String

#def open_port(dev, baud):
#    while not rospy.is_shutdown():
#        try:
#            return serial.Serial(dev, baud, timeout=0.1)
#        except serial.SerialException as e:
#            rospy.logwarn(f"{e} — retry in 2 s")
#            time.sleep(2)

#def main():
#    rospy.init_node("serial_bridge")        # ★ launch 파일의 name 과 동일
#    port = rospy.get_param("~port", "/tmp/ttyV0")
#    baud = rospy.get_param("~baud", 115200)

#    pub  = rospy.Publisher("order_raw", String, queue_size=10)
#    rospy.loginfo("Serial→ROS bridge started on %s", port)

#    ser = open_port(port, baud)

#    while not rospy.is_shutdown():
#        try:
#            data = ser.readline().decode("utf-8", "ignore").strip()
#        except serial.serialutil.SerialException as e:
#            rospy.logwarn(f"Serial lost: {e}")
#            ser.close()
#            ser = open_port(port, baud)
#            continue

#        if data:
#            pub.publish(data)
#            rospy.loginfo(f"QR → {data}")


#!/usr/bin/env python3
"""
Serial → ROS bridge
 - 기본 포트  : /tmp/ttyV0   (가상 PTY 쌍의 PC 측)
 - 기본 보드레이트 : 115200
 - 노드 이름 : serial_bridge   (launch·rosrun 파라미터와 일치)
 - '\n' 기준 한 줄씩 읽어 order_raw 토픽(String)으로 퍼블리시
"""

import rospy
import serial
import serial.serialutil
import time
from std_msgs.msg import String


def open_port(dev, baud):
    """끊어지면 재시도하면서 포트를 연다."""
    while not rospy.is_shutdown():
        try:
            s = serial.Serial(dev, baud, timeout=0.1)
            rospy.loginfo(f"Serial open OK → {dev}")
            return s
        except serial.SerialException as e:
            rospy.logwarn(f"{e} — retry in 2 s")
            time.sleep(2)


def main():
    rospy.init_node("serial_bridge")                    # launch 와 동일
    port = rospy.get_param("~port", "/tmp/ttyV0")
    baud = rospy.get_param("~baud", 115200)

    pub = rospy.Publisher("order_raw", String, queue_size=10)
    rospy.loginfo("Serial→ROS bridge started on %s", port)

    ser = open_port(port, baud)
    buf = ""
    rate = rospy.Rate(100)                              # 100 Hz 루프

    while not rospy.is_shutdown():
        try:
            chunk = ser.read(64).decode("utf-8", "ignore")
        except serial.serialutil.SerialException as e:
            rospy.logwarn_throttle(30, f"Serial lost, retrying: {e}")
            #rospy.logwarn(f"Serial lost: {e}")
            ser.close()
            ser = open_port(port, baud)
            continue

        if chunk:
            buf += chunk
            while '\n' in buf:                          # 줄 단위 분리
                line, buf = buf.split('\n', 1)
                line = line.strip()
                if line:
                    pub.publish(line)
                    rospy.loginfo(f"QR → {line}")
        rate.sleep()


if __name__ == "__main__":
    try:
        main()
    except rospy.ROSInterruptException:
        pass
