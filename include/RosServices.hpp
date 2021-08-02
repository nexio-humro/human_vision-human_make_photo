#ifndef ROS_SERVICES_HPP
#define ROS_SERVICES_HPP

#include <iostream>

#include "ros/ros.h"

#include "human_vision_exchange/DoPhotoReceiver.h"
#include "human_vision_exchange/FaceVectorReceiver.h"
#include "human_vision_exchange/FaceVectorReceiverFacenet.h"
#include <ZedData.hpp>
#include <MainData.hpp>
#include "BodyPartEnum.hpp"
#include <SystemFunctions.hpp>

namespace RS
{
	bool doPhoto(human_vision_exchange::DoPhotoReceiver::Request  &req, human_vision_exchange::DoPhotoReceiver::Response &res);
	bool doPhotoFacenet(human_vision_exchange::DoPhotoReceiver::Request  &req, human_vision_exchange::DoPhotoReceiver::Response &res);
}

#endif
