#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <opencv2/highgui/highgui.hpp>
#include <cv_bridge/cv_bridge.h>
#include <sstream>
#include <camera_info_manager/camera_info_manager.h>
#include "std_msgs/Float64MultiArray.h"
#include "std_msgs/Float64MultiArray.h"
#include "std_msgs/Float64MultiArray.h"
#include <string>
#include <image_transport/camera_publisher.h>
#include <time.h>
#include <sensor_msgs/Image.h>
#include <sensor_msgs/image_encodings.h>

using namespace std;

int main(int argc, char** argv)
{
    ros::init(argc, argv, "left_image_publisher");
    ros::NodeHandle nh;
    image_transport::ImageTransport it(nh);
    image_transport::CameraPublisher const pub = it.advertiseCamera("stereo/left/image_raw", 1);
    cv::VideoCapture cap1(1);
    cv::Mat frame1, image1;
    sensor_msgs::CameraInfo info_camera;
    cv_bridge::CvImage img_bridge;
    sensor_msgs::Image img_msg;

     //cap1.open(1);
    if ( !cap1.isOpened() )
    {
        std::cout << "Could not initialize cap1" << std::endl;
        return -1;
    }

    ros::Rate loop_rate(5);
    cv::waitKey(100);
    while (ros::ok()) {
        cap1 >> frame1;
        if ( frame1.empty() )
            break;
        frame1.copyTo(image1);
      
  
        if(!image1.empty()){
        cv::imshow( "Img1", image1 );}
       
        char c = (char)cv::waitKey(10);
        if ( c == 27 )
            break;

     //   cv::Mat image = cv::imread("/home/karmesh/arnav.jpg", CV_LOAD_IMAGE_COLOR);

        //sensor_msgs::ImagePtr msg1 = cv_bridge::CvImage(std_msgs::Header(), "bgr8", image1).toImageMsg();

	std_msgs::Header header; // empty header
        header.stamp = ros::Time::now(); // time
        img_bridge = cv_bridge::CvImage(header, sensor_msgs::image_encodings::RGB8, image1);
        img_bridge.toImageMsg(img_msg); // from cv_bridge to sensor_msgs::Image

	int width,height,i;
	string name,naming;
	std::vector<double>list0;
	std::vector<double>list1;
	std::vector<double>list2;	
	std::vector<double>list3;

	info_camera.header.stamp = ros::Time::now(); 
        nh.getParam("publisher/camera_name", naming);
	info_camera.header.frame_id = naming;
	nh.getParam("publisher/image_width", width);
	info_camera.width = width;
        nh.getParam("publisher/image_height", height);
	info_camera.height = height;
	nh.getParam("publisher/distortion_model", name);
	info_camera.distortion_model = name;
        nh.getParam("publisher/distortion_coefficients/data", list0);
	info_camera.D.clear();
	for (i=0;i<5;i++) {
	    info_camera.D.push_back((double)list0[i]);
	}
	nh.getParam("publisher/camera_matrix/data", list1);
	for (i=0;i<9;i++) {
	    info_camera.K[i] = list1[i];
	}
	nh.getParam("publisher/rectification_matrix/data", list2);
	for (i=0;i<9;i++) {
	    info_camera.R[i] = list2[i];
	}
	nh.getParam("publisher/projection_matrix/data", list3);
	for (i=0;i<12;i++) {
	    info_camera.P[i] = list3[i];
	}	
        //

        pub.publish(img_msg,info_camera,ros::Time::now());


        ros::spinOnce();
        loop_rate.sleep();
    }
}
