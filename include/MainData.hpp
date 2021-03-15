#ifndef MAIN_DATA_HPP
#define MAIN_DATA_HPP

#include <stdlib.h>
#include <iostream>

#include "ros/ros.h"
#include "human_vision_exchange/DoPhotoReceiver.h"
#include "human_vision_exchange/FaceVectorReceiver.h"
#include "human_vision_exchange/FindFaceVectors.h"
#include "human_vision_exchange/CutFaces.h"

namespace MD
{
	const ros::ServiceServer* getDoPhotoService();
	void setDoPhotoServer(ros::NodeHandle& node, std::string serviceName, bool(*callbackMethod)(human_vision_exchange::DoPhotoReceiver::Request&, human_vision_exchange::DoPhotoReceiver::Response&));
	
	void sendFaceVectorClientRequest(human_vision_exchange::FaceVectorReceiver& fvr);
	void setSendFaceVectorClient(ros::NodeHandle& node, std::string serviceName);
	
	void sendFindFaceVectorsClientRequest(human_vision_exchange::FindFaceVectors& fvr);
	void setSendFindFaceVectorsClient(ros::NodeHandle& node, std::string serviceName);
	
	void sendCutFacesClientRequest(human_vision_exchange::CutFaces& fvr);
	void setCutFacesClient(ros::NodeHandle& node, std::string serviceName);
}

#endif
