#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <opencv2/highgui/highgui.hpp>
#include <cv_bridge/cv_bridge.h>
#include <sstream>
#include <camera_info_manager/camera_info_manager.h>
#include "std_msgs/Float64MultiArray.h"
#include "std_msgs/Float64MultiArray.h"
#include "std_msgs/Float64MultiArray.h"
#include "sensor_msgs/CameraInfo.h"
#include "sensor_msgs/Image.h"
#include "stereo_msgs/DisparityImage.h"
#include "sensor_msgs/PointCloud2.h"

cv::Mat frame,newframe;
   void left_mono(const sensor_msgs::Image msg){
   try
  {
    
    newframe = cv_bridge::toCvShare(msg, "bgr8")->image;
    ///////////////////////////// DO NOT REMOVE THIS, IT COULD BE INGERIOUS TO HEALTH /////////////////////
    newframe.copyTo(frame);
    ////////////////////////// FATAL ///////////////////////////////////////////////////
    if(!frame.empty()){
        cv::imshow( "frame", frame );}
  }
  catch (cv_bridge::Exception &e)
  {
    ROS_ERROR("%s: Could not convert from  to 'bgr8'.");
  } 
   }
   void right_mono(const sensor_msgs::Image msg){}
   void left_image_color(const sensor_msgs::Image msg){}
   void right_image_color(const sensor_msgs::Image msg){}
   void rectified_left(const sensor_msgs::Image msg){}
   void rectified_right(const sensor_msgs::Image msg){}
   void rectified_left_color(const sensor_msgs::Image msg){}
   void rectified_right_color(const sensor_msgs::Image msg){}
   void disparity_image(const stereo_msgs::DisparityImage disparity){
   
  /*  cv::Mat_<float> disparityMat(disparity->image.height,disparity->image.width,reinterpret_cast<float*>(&(disparity->image.data[0])));

    cv::Mat_<uint8_t> eightBitDisparityMat = disparityMat * (255/disparity->max_disparity);

    sensor_msgs::Image eightBitDisparity;

    uint32_t imageSize = disparity->image.height * disparity->image.width;

    eightBitDisparity.data.resize(imageSize);
    memcpy(&eightBitDisparity.data[0], &(eightBitDisparityMat.at<uint8_t>(0,0)), imageSize);*/
   }
   void point_cloud2(const sensor_msgs::PointCloud2 msg){}

   int main(int argc, char **argv)
   {
     ros::init(argc, argv, "processed_data");
  
     ros::NodeHandle n;
     image_transport::ImageTransport it(n);
     
      ros::Subscriber sub = n.subscribe("/stereo/left/image_rect", 1000, rectified_left);
      ros::Subscriber sub1 = n.subscribe("/stereo/right/image_rect", 1000, rectified_right);
      ros::Subscriber sub2 = n.subscribe("/stereo/left/image_rect_color", 1000, rectified_left_color);
      ros::Subscriber sub3 = n.subscribe("/stereo/right/image_rect_color", 1000, rectified_right_color);
      ros::Subscriber sub4 = n.subscribe("/stereo/disparity", 1000, disparity_image);
      ros::Subscriber sub5 = n.subscribe("/stereo/points2", 1000, point_cloud2);
      ros::Subscriber sub6 = n.subscribe("/stereo/left/image_mono", 1000, left_mono);
      ros::Subscriber sub7 = n.subscribe("/stereo/right/image_mono", 1000, right_mono);
      ros::Subscriber sub8 = n.subscribe("/stereo/left/image_color", 1000, left_image_color);
      ros::Subscriber sub9 = n.subscribe("/stereo/right/image_color", 1000, right_image_color);
    
 
     ros::spin();
  
     return 0;
   }



