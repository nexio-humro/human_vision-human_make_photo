#ifndef ROS_TOPIC_HPP
#define ROS_TOPIC_HPP

#include <iostream>

#include "ros/ros.h"
#include "sensor_msgs/Image.h"
#include "geometry_msgs/Point32.h"
//#include "zed_interfaces/Objects.h"
#include "human_vision_exchange/Objects.h"
#include <cv_bridge/cv_bridge.h>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>

#include <ZedData.hpp>

namespace RT
{
	void grab_image(const sensor_msgs::ImagePtr&  image);
	void grab_objects(const human_vision_exchange::Objects& objects);
}

#endif
