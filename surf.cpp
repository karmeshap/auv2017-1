#include <stdio.h>

#include <iostream>

#include <vector>

#include <string>

#include <opencv2/core/core.hpp>

#include <opencv2/highgui/highgui.hpp>

#include <opencv2/nonfree/features2d.hpp>

#include <opencv2/opencv.hpp>



using namespace std;

using namespace cv;



int main(int argc,char **argv)

{



	Mat image1;

	Mat image2;



	image1=cv::imread(argv[1],1);             //read the input images

	image2=cv::imread(argv[2],1);



	vector<cv::KeyPoint> kp1;                 

	vector<cv::KeyPoint> kp2;

    Mat des1, des2;



    SurfFeatureDetector surf(500);            //get the keypoints

    surf.detect(image1,kp1);

    surf.detect(image2,kp2);



    SurfDescriptorExtractor extractor;       //get the descriptors

    extractor.compute(image1,kp1,des1);

    extractor.compute(image2,kp2,des2); 	

    

    Ptr<DescriptorMatcher> matcher = DescriptorMatcher::create("BruteForce"); //define matcher object



	std::vector< std::vector< DMatch > >  matches;                            //define DMatch object to store matches
        std::vector< std::vector< DMatch > >  matches1;                            //define DMatch object to store matches

    matcher->knnMatch(des1,des2, matches,2);
    matcher->knnMatch(des2,des1, matches1,2);

    std::vector<DMatch> goodMatches;

    std::vector<DMatch> goodMatches1;

    for(int i=0;i<des1.rows;i++)                                       //ratio test to remove poor matches

    {

        const DMatch &m = matches[i][0];

        const DMatch &n = matches[i][1];

        if(m.distance<0.75*n.distance)

            goodMatches.push_back(m);

        else if(n.distance<0.75*m.distance)

            goodMatches.push_back(n);

	}
     for(int i=0;i<des2.rows;i++)                                       //ratio test to remove poor matches

    {

        const DMatch &m = matches1[i][0];

        const DMatch &n = matches1[i][1];

        if(m.distance<0.75*n.distance)

            goodMatches1.push_back(m);

        else if(n.distance<0.75*m.distance)

            goodMatches1.push_back(n);

	}

    std::vector<cv::DMatch> symMatches;                                       // symmetry test
    
  for (vector<DMatch>::const_iterator matchIterator1= goodMatches.begin();matchIterator1!= goodMatches.end(); ++matchIterator1)

  {

    for (vector<DMatch>::const_iterator matchIterator2= goodMatches1.begin();matchIterator2!= goodMatches1.end();++matchIterator2)

    {

      if ((*matchIterator1).queryIdx ==(*matchIterator2).trainIdx &&(*matchIterator2).queryIdx ==(*matchIterator1).trainIdx)

      {

        symMatches.push_back(DMatch((*matchIterator1).queryIdx,(*matchIterator1).trainIdx,(*matchIterator1).distance));

        break;

      }

    }

  }
   
  std::vector<cv::DMatch> bestMatches;                                                  //ransac test
   
double distance,confidence,minInlierRatio;
   
    // Convert keypoints into Point2f
    std::vector<cv::Point2f> points1, points2;
    for (std::vector<cv::DMatch>::const_iterator it= symMatches.begin();it!= symMatches.end(); ++it)
    {
        // Get the position of left keypoints
        float x= kp1[it->queryIdx].pt.x;
        float y= kp1[it->queryIdx].pt.y;
        points1.push_back(cv::Point2f(x,y));
        // Get the position of right keypoints
        x= kp2[it->trainIdx].pt.x;
        y= kp2[it->trainIdx].pt.y;
        points2.push_back(cv::Point2f(x,y));
    }
    // Compute F matrix using RANSAC
    std::vector<uchar> inliers(points1.size(),0);
    cv::Mat fundemental= findFundamentalMat(cv::Mat(points1),cv::Mat(points2),inliers,CV_FM_RANSAC,distance,confidence); // confidence probability
    // extract the surviving (inliers) matches
    std::vector<uchar>::const_iterator
    itIn= inliers.begin();
    std::vector<cv::DMatch>::const_iterator
    itM= symMatches.begin();
    // for all matches
    for ( ;itIn!= inliers.end(); ++itIn, ++itM)
    {
        if (*itIn)
        { // it is a valid match
            bestMatches.push_back(*itM);
        }
    }

 Mat image3;

    drawMatches(image1,kp1,image2,kp2,symMatches,image3,2);



 	cv::namedWindow("image",CV_WINDOW_NORMAL);

    cv::imshow("image",image3);

    cv::waitKey(0);



    return 0;



}
