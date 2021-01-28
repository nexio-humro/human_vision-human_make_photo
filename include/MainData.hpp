#ifndef MAIN_DATA_HPP
#define MAIN_DATA_HPP

#include <stdlib.h>
#include <iostream>

#include "ros/ros.h"
#include "human_vision_exchange/DoPhotoReceiver.h"
#include "human_vision_exchange/FaceVectorReceiver.h"

namespace MD
{
	const ros::ServiceServer* getDoPhotoService();
	void setDoPhotoServer(ros::NodeHandle& node, std::string serviceName, bool(*callbackMethod)(human_vision_exchange::DoPhotoReceiver::Request&, human_vision_exchange::DoPhotoReceiver::Response&));
	
	void sendFaceVectorClientRequest(human_vision_exchange::FaceVectorReceiver& fvr);
	void setSendFaceVectorClient(ros::NodeHandle& node, std::string serviceName);
}

#endif
