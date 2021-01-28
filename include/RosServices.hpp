#ifndef ROS_SERVICES_HPP
#define ROS_SERVICES_HPP

#include <iostream>

#include "ros/ros.h"

#include "human_vision_exchange/DoPhotoReceiver.h"
#include "human_vision_exchange/FaceVectorReceiver.h"
#include <DlibFrontalFaceDetection.hpp>
#include <FaceCuttingFunctions.hpp>
#include <DlibFrontalFaceDetectionPaths.hpp>
#include <ZedData.hpp>
#include <MainData.hpp>

namespace RS
{
	bool doPhoto(human_vision_exchange::DoPhotoReceiver::Request  &req, human_vision_exchange::DoPhotoReceiver::Response &res);
}

#endif
