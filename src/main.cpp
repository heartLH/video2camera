//
// Created by cj on 8/24/19.
//

#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/image_encodings.h>
#include <string>
using namespace cv;
using namespace std;
using namespace ros;
int main(int argc,char** argv)
{

    init(argc,argv,"video2camera");
    NodeHandle n;
    ros::Publisher camera_pub=n.advertise<cv_bridge::CvImage>("/usb_cam/image_raw",1000);
    string filename ="/home/cj/Desktop/VID_20190824_161710.mp4" ;
    int show=0;
   n.getParam("file_name",filename);
   n.getParam("show",show);
    //int ifshou=show.
    VideoCapture capture;
    capture.open(filename);
    if (!capture.isOpened())//判断是否打开视频文件
    {
        ROS_ERROR("Can't Open the video,Please check the path!");
        return -1;
    }

    else
    {
        double rate = capture.get(CV_CAP_PROP_FPS);//获取视频文件的帧率
        ros::Rate loop_rate(rate);
        while (ros::ok())
        {
            Mat frame;
            capture >> frame;//读出每一帧的图像
            if (frame.empty()) break;
            sensor_msgs::ImagePtr msg=cv_bridge::CvImage(std_msgs::Header(),"bgr8",frame).toImageMsg();
            cv::namedWindow("处理前视频", CV_WINDOW_NORMAL);
            imshow("处理前视频", frame);
            camera_pub.publish(msg);
            ros::spinOnce();
            loop_rate.sleep();
            if(show)
                waitKey(1);
        }
    }

    return 0;
}