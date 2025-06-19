// #include <ros/ros.h>
// #include <std_msgs/String.h>
// #include <opencv2/opencv.hpp>
// #include <opencv2/objdetect.hpp>
// #include <zbar.h>

// int main(int argc, char** argv)
// {
//   ros::init(argc, argv, "camera_qr_publisher");
//   ros::NodeHandle nh("~");

//   /*** Parameters ***********************************************************/
//   int cam_idx   = nh.param<int>("camera_index", 0);   // /dev/video0 by default
//   int width     = nh.param<int>("width",        640);
//   int height    = nh.param<int>("height",       480);
//   double fps    = nh.param<double>("fps",       30.0);
//   double pause  = nh.param<double>("publish_pause", 1.0); // duplicate-limit

//   /*** Publisher ************************************************************/
//   ros::Publisher pub =
//       nh.advertise<std_msgs::String>("/order_raw", 1 /*queue*/, true /*latch*/);

//   /*** OpenCV setup *********************************************************/
//   cv::VideoCapture cap(cam_idx, cv::CAP_ANY);
//   if (!cap.isOpened()) {
//     ROS_ERROR_STREAM("Failed to open camera index " << cam_idx);
//     return 1;
//   }
//   cap.set(cv::CAP_PROP_FOURCC, cv::VideoWriter::fourcc('M','J','P','G'));
//   cap.set(cv::CAP_PROP_FRAME_WIDTH,  width);
//   cap.set(cv::CAP_PROP_FRAME_HEIGHT, height);
//   cap.set(cv::CAP_PROP_FPS,          fps);

//   cv::QRCodeDetector detector;
//   zbar::ImageScanner scanner;    // ZBar : 해독
//   scanner.set_config(zbar::ZBAR_QRCODE, zbar::ZBAR_CFG_ENABLE, 1);

//   ROS_INFO_STREAM("QR publisher running on /order_raw (camera #" << cam_idx << ")");

//   /*** Main loop ************************************************************/
//   ros::Rate loop(fps);
//   while (ros::ok())
//   {
//     cv::Mat frame;
//     if (!cap.read(frame)) {      // 캡처 실패
//       ROS_WARN_THROTTLE(5.0, "Camera frame read failed");
//       loop.sleep();  continue;
//     }

//     std::vector<cv::Point> bbox;
//     if (!detector.detect(frame, bbox) || bbox.empty()) {
//       ros::spinOnce();  loop.sleep();  continue;        // QR 미검출
//     }

//     /* ───── 검출된 영역(ROI) 잘라서 그레이 변환 ───── */
//     cv::Rect roi = cv::boundingRect(bbox);
//     roi &= cv::Rect(0,0,frame.cols,frame.rows);         // 경계 보정
//     cv::Mat gray;
//     cv::cvtColor(frame(roi), gray, cv::COLOR_BGR2GRAY);

//     /* ───── ZBar 로 해독 ───── */
//     zbar::Image zimg(gray.cols, gray.rows, "Y800", gray.data, gray.total());
//     int n = scanner.scan(zimg);
//     if (n > 0)
//     {
//       for (auto sym = zimg.symbol_begin(); sym != zimg.symbol_end(); ++sym)
//       {
//         std_msgs::String msg;
//         msg.data = sym->get_data();
//         pub.publish(msg);
//         ROS_INFO_STREAM("QR ▶ '" << msg.data << '\'');
//         break;                        // 첫 번째 QR만 사용
//       }
//       ros::Duration(pause).sleep();   // 중복 발행 제한
//     }

//     ros::spinOnce();
//     loop.sleep();
//   }
//   return 0;
// }

/*  ros::Rate r(fps);
  while (ros::ok())
  {
    cv::Mat frame;
    if (!cap.read(frame))
    {
      ROS_WARN_THROTTLE(5.0, "Camera frame read failed");
      r.sleep();  continue;
    }

    std::string data = qr.detectAndDecode(frame);
    if (!data.empty())
    {
      std_msgs::String msg;
      msg.data = data;
      pub.publish(msg);
      ROS_INFO_STREAM("QR ▶ '" << data << '\'');
      ros::Duration(pause).sleep();  // avoid flooding same QR
    }

    ros::spinOnce();
    r.sleep();
  }
  return 0;
} */


// #include <opencv2/opencv.hpp>
// #include <zbar.h>

// #include <fcntl.h>
// #include <termios.h>
// #include <unistd.h>
// #include <cstring>
// #include <iostream>

// int main(int argc, char** argv)
// {
//   /* ---------- 사용자 조정 파라미터 ---------- */
//   const int    cam_index = 4;        // /dev/video4
//   const int    width     = 640;
//   const int    height    = 480;
//   const double fps       = 30.0;
//   const int    baudrate  = 115200;
//   const double pause_sec = 1.0;      // 중복 전송 억제를 위한 딜레이
//   /* ---------------------------------------- */

//   /* 1. 직렬 포트 열기 */
//   int fd = open("/dev/ttyUSB0", O_RDWR | O_NOCTTY | O_SYNC);
//   if (fd < 0) { perror("serial open"); return 1; }

//   termios tty{};
//   tcgetattr(fd, &tty);
//   cfsetispeed(&tty, B115200);
//   cfsetospeed(&tty, B115200);
//   tty.c_cflag = (tty.c_cflag & ~CSIZE) | CS8;
//   tty.c_cflag |= (CLOCAL | CREAD);          // enable receiver
//   tty.c_cflag &= ~(PARENB | CSTOPB | CRTSCTS);
//   tcsetattr(fd, TCSANOW, &tty);

//   /* 2. 카메라 초기화 */
//   cv::VideoCapture cap(cam_index, cv::CAP_ANY);
//   if (!cap.isOpened()) { std::cerr << "❌ Camera open failed\n"; return 1; }
//   cap.set(cv::CAP_PROP_FOURCC,  cv::VideoWriter::fourcc('M','J','P','G'));
//   cap.set(cv::CAP_PROP_FRAME_WIDTH,  width);
//   cap.set(cv::CAP_PROP_FRAME_HEIGHT, height);
//   cap.set(cv::CAP_PROP_FPS,          fps);

//   /* 3. ZBar 스캐너 준비 */
//   zbar::ImageScanner scanner;
//   scanner.set_config(zbar::ZBAR_QRCODE, zbar::ZBAR_CFG_ENABLE, 1);

//   std::cerr << "QR serial publisher started (fps=" << fps << ")\n";

//   /* 4. 메인 루프 */
//   const int frame_delay_ms = static_cast<int>(1000.0 / fps);
//   while (true)
//   {
//     cv::Mat frame, gray;
//     if (!cap.read(frame)) { std::cerr << "⚠ Frame read error\n"; continue; }

//     /* QR 후보 영역 탐색(간단히 전역 디텍터 사용) */
//     cv::QRCodeDetector detector;
//     std::vector<cv::Point> bbox;
//     if (!detector.detect(frame, bbox) || bbox.empty()) {          // 검출 실패
//       cv::waitKey(frame_delay_ms);  continue;
//     }

//     /* ROI 추출 & 그레이 변환 */
//     cv::Rect roi = cv::boundingRect(bbox);
//     roi &= cv::Rect(0, 0, frame.cols, frame.rows);                // 경계 보정
//     cv::cvtColor(frame(roi), gray, cv::COLOR_BGR2GRAY);

//     /* ZBar 디코딩 */
//     zbar::Image zimg(gray.cols, gray.rows, "Y800", gray.data, gray.total());
//     if (scanner.scan(zimg) > 0)
//     {
//       for (auto sym = zimg.symbol_begin(); sym != zimg.symbol_end(); ++sym)
//       {
//         std::string data = sym->get_data();
//         data.push_back('\n');                       // 줄바꿈 추가

//         /* 직렬 포트로 송신 */
//         ssize_t n = write(fd, data.c_str(), data.size());
//         if (n != static_cast<ssize_t>(data.size()))
//           std::cerr << "⚠ Serial write truncated\n";

//         std::cerr << "QR ▶ " << sym->get_data() << '\n';
//         usleep(static_cast<useconds_t>(pause_sec * 1e6));   // 중복 방지
//         break;                                              // 첫 QR만 사용
//       }
//     }
//     cv::waitKey(frame_delay_ms);
//   }
//   close(fd);
//   return 0;
// }


#include <opencv2/opencv.hpp>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>
#include <iostream>

int main() {
    /* 직렬 포트 준비 (/dev/ttyUSB0) */
    int fd = open("/dev/ttyUSB0", O_RDWR | O_NOCTTY | O_SYNC);
    termios tty{}; tcgetattr(fd,&tty);
    cfsetispeed(&tty,B115200); cfsetospeed(&tty,B115200);
    tty.c_cflag = (tty.c_cflag & ~CSIZE) | CS8 | CLOCAL | CREAD;
    tcsetattr(fd,TCSANOW,&tty);

    /* 카메라 */
    cv::VideoCapture cap(0);
    if(!cap.isOpened()){ std::cerr<<"cam open fail\n"; return 1; }

    /* OpenCV QR 디텍터 */
    cv::QRCodeDetector detector;

    while(true){
        cv::Mat frame; cap >> frame;
        if(frame.empty()) continue;

        std::vector<cv::Point> bbox;
        std::string data = detector.detectAndDecode(frame, bbox);

        if(!data.empty()){                 // QR 성공
            write(fd, data.c_str(), data.size());
            write(fd, "\n", 1);
            std::cerr << "QR ▶ " << data << '\n';
            usleep(1e6);                  // 중복 방지 1 초
        }
        cv::waitKey(1);                   // 1 ms
    }
    close(fd);
    return 0;
}
