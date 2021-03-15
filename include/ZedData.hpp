#ifndef ZED_DATA_HPP
#define ZED_DATA_HPP

#include <iostream>
#include <mutex>

#include "ros/ros.h"
#include "ros/package.h"
#include <cv_bridge/cv_bridge.h>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>

#include <human_vision_exchange/Keypoints2d.h>

namespace ZD
{
	void saveImage(cv_bridge::CvImagePtr image);
	cv::Mat getImage();
	
	void saveKeypoints2d(std::vector<human_vision_exchange::Keypoints2d>& objects);
	std::vector<human_vision_exchange::Keypoints2d> getKeypoints2d();
}

#endif

