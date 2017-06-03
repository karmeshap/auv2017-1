#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <opencv2/highgui/highgui.hpp>
#include <cv_bridge/cv_bridge.h>
#include <sstream>
#include <camera_info_manager/camera_info_manager.h>
#include "std_msgs/Float64MultiArray.h"
#include "std_msgs/Float64MultiArray.h"
#include "std_msgs/Float64MultiArray.h"






int main(int argc, char** argv)
{
    ros::init(argc, argv, "image_publisher");
    ros::NodeHandle nh;
    image_transport::ImageTransport it(nh);
    image_transport::Publisher pub = it.advertise("stereo/left/image_raw", 1);
    ros::Publisher pub_info_camera = nh.advertise<sensor_msgs::CameraInfo>("stereo/left/camera_info", 1);
    image_transport::Publisher pub1 = it.advertise("stereo/right/image_raw", 1);
    ros::Publisher pub1_info_camera = nh.advertise<sensor_msgs::CameraInfo>("stereo/right/camera_info", 1);
    cv::VideoCapture cap1, cap2;
    cv::Mat frame1, image1,frame2 , image2;
    sensor_msgs::ImagePtr msg;
    sensor_msgs::ImagePtr msg1;
    sensor_msgs::CameraInfo info_camera;
    sensor_msgs::CameraInfo info_camera1;

     cap1.open(1);
     cap2.open(2);
    if ( !cap1.isOpened() )
    {
        std::cout << "Could not initialize cap1" << std::endl;
        return -1;
    }
     if ( !cap2.isOpened() )
    {
        std::cout << "Could not initialize cap2" << std::endl;
        return -1;
    }

    ros::Rate loop_rate(5);
    cv::waitKey(100);
    while (ros::ok()) {
        cap1 >> frame1;
        if ( frame1.empty() )
            break;
        frame1.copyTo(image1);
        cap2 >> frame2;
       if ( frame2.empty() )
            break;
        frame2.copyTo(image2);
  
        if(!image1.empty()){
        cv::imshow( "Img1", image1 );}
        if(!image2.empty()){
         cv::imshow( "Img2", image2 );}

        char c = (char)cv::waitKey(10);
        if ( c == 27 )
            break;

     //   cv::Mat image = cv::imread("/home/karmesh/arnav.jpg", CV_LOAD_IMAGE_COLOR);
        msg = cv_bridge::CvImage(std_msgs::Header(), "bgr8", image1).toImageMsg();
	msg1 = cv_bridge::CvImage(std_msgs::Header(), "bgr8", image2).toImageMsg();
  


        //sensor_msgs::ImagePtr msg1 = cv_bridge::CvImage(std_msgs::Header(), "bgr8", image1).toImageMsg();
        info_camera.header.stamp = ros::Time::now(); //
	info_camera.height=640;
	info_camera.width=480;
	info_camera.distortion_model="plumb_bob";
	info_camera.D.push_back(0.111993);
	info_camera.D.push_back(0.026613);
	info_camera.D.push_back(-0.004207);	
	info_camera.D.push_back(-0.009984);	
	info_camera.D.push_back(0.000000);

	info_camera.K[0]=827.340571;
	info_camera.K[1]=0.000000;
	info_camera.K[2]=338.180659;
	info_camera.K[3]=0.000000;
	info_camera.K[4]=831.700276;
	info_camera.K[5]=242.583992;
	info_camera.K[6]=0.000000;
	info_camera.K[7]=0.000000;
	info_camera.K[8]=1.000000;

	
	info_camera.R[0]=0.988085;
	info_camera.R[1]=-0.070205;
	info_camera.R[2]=-0.136963;
	info_camera.R[3]=0.072322;
	info_camera.R[4]=0.997326;
	info_camera.R[5]=0.010532;
	info_camera.R[6]=0.135857;
	info_camera.R[7]=-0.020312;
	info_camera.R[8]=0.990520;

	
	info_camera.P[0]=1162.113855;	
	info_camera.P[1]=0.000000;	
	info_camera.P[2]=414.786396;
	info_camera.P[3]=0.000000;
	info_camera.P[4]=0.000000;
	info_camera.P[5]=1162.113855;
	info_camera.P[6]=234.846518;
	info_camera.P[7]=0.000000;
	info_camera.P[8]=0.000000;
	info_camera.P[9]=0.000000;
	info_camera.P[10]=1.000000;
	info_camera.P[11]=0.000000;

        pub_info_camera.publish(info_camera);
        pub.publish(msg);

        info_camera1.header.stamp = ros::Time::now(); //
	info_camera1.height=640;
	info_camera1.width=480;
	info_camera1.distortion_model="plumb_bob";
	info_camera1.D.push_back(-0.100712);
	info_camera1.D.push_back(0.262696);
	info_camera1.D.push_back(-0.001080);	
	info_camera1.D.push_back(-0.006699);	
	info_camera1.D.push_back(0.000000);

	info_camera1.K[0]=825.080986;
	info_camera1.K[1]=0.000000;
	info_camera1.K[2]=334.444326;
	info_camera1.K[3]=0.000000;
	info_camera1.K[4]=827.941593;
	info_camera1.K[5]=220.414539;
	info_camera1.K[6]=0.000000;
	info_camera1.K[7]=0.000000;
	info_camera1.K[8]=1.000000;

	info_camera1.R[0]=0.997847;
	info_camera1.R[1]=-0.061888;
	info_camera1.R[2]=-0.021713;
	info_camera1.R[3]=0.061545;
	info_camera1.R[4]=0.997974;
	info_camera1.R[5]=-0.016146;
	info_camera1.R[6]=0.022668;
	info_camera1.R[7]=-0.014775;
	info_camera1.R[8]=0.999634;

	
	info_camera1.P[0]=1162.113855;	
	info_camera1.P[1]=0.000000;	
	info_camera1.P[2]=414.786396;
	info_camera1.P[3]=-366.846972;
	info_camera1.P[4]=0.000000;
	info_camera1.P[5]=1162.113855;
	info_camera1.P[6]=234.846518;
	info_camera1.P[7]=0.000000;
	info_camera1.P[8]=0.000000;
	info_camera1.P[9]=0.000000;
	info_camera1.P[10]=1.000000;
	info_camera1.P[11]=0.000000;
	
        pub1_info_camera.publish(info_camera1);
        pub1.publish(msg1);

        ros::spinOnce();
        loop_rate.sleep();
    }
}












