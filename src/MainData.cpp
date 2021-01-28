#include <MainData.hpp>

namespace
{
	ros::ServiceServer doPhotoService;
	ros::ServiceClient sendFaceVector;
}

namespace MD
{
	const ros::ServiceServer* getDoPhotoService()
	{
		return &doPhotoService;
	}
	
	void setDoPhotoServer(ros::NodeHandle& node, std::string serviceName, bool(*callbackMethod)(human_vision_exchange::DoPhotoReceiver::Request&, human_vision_exchange::DoPhotoReceiver::Response&))
	{
		doPhotoService = node.advertiseService(serviceName.c_str(), callbackMethod);
	}
	
	void sendFaceVectorClientRequest(human_vision_exchange::FaceVectorReceiver& fvr)
	{
		sendFaceVector.call(fvr);
		std::cout<<"sendFaceVectorClientRequest: fvr.response.status = "<<fvr.response.status<<std::endl;
	}
	
	void setSendFaceVectorClient(ros::NodeHandle& node, std::string serviceName)
	{
		sendFaceVector = node.serviceClient<human_vision_exchange::FaceVectorReceiver>(serviceName.c_str());
	}
}
