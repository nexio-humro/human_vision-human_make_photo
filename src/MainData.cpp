#include <MainData.hpp>

namespace
{
	ros::ServiceServer doPhotoService;
	ros::ServiceClient sendFaceVector;
	ros::ServiceClient sendFaceVectorFacenet;
	ros::ServiceClient findFaceVectorsClient;
	ros::ServiceClient findFaceVectorsFacenetClient;
	ros::ServiceClient cutFaceClient;
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
	}
	
	void setSendFaceVectorClient(ros::NodeHandle& node, std::string serviceName)
	{
		sendFaceVector = node.serviceClient<human_vision_exchange::FaceVectorReceiver>(serviceName.c_str());
	}
	
	void sendFaceVectorFacenetClientRequest(human_vision_exchange::FaceVectorReceiverFacenet& fvr)
	{
		sendFaceVector.call(fvr);
	}
	
	void setSendFaceVectorFacenetClient(ros::NodeHandle& node, std::string serviceName)
	{
		sendFaceVector = node.serviceClient<human_vision_exchange::FaceVectorReceiverFacenet>(serviceName.c_str());
	}
	
	void sendFindFaceVectorsClientRequest(human_vision_exchange::FindFaceVectors& ffv)
	{
		findFaceVectorsClient.call(ffv);
	}
	
	void setSendFindFaceVectorsClient(ros::NodeHandle& node, std::string serviceName)
	{
		findFaceVectorsClient = node.serviceClient<human_vision_exchange::FindFaceVectors>(serviceName.c_str());
	}
	
	void sendFindFaceVectorsFacenetClientRequest(human_vision_exchange::FindFaceVectorsFacenet& ffv)
	{
		std::cout<<"sendFindFaceVectorsFacenetClientRequest()"<<std::endl;
		findFaceVectorsFacenetClient.call(ffv);
	}
	
	void setSendFindFaceVectorsFacenetClient(ros::NodeHandle& node, std::string serviceName)
	{
		findFaceVectorsFacenetClient = node.serviceClient<human_vision_exchange::FindFaceVectorsFacenet>(serviceName.c_str());
	}
	
	void sendCutFacesClientRequest(human_vision_exchange::CutFaces& cf)
	{
		cutFaceClient.call(cf);
	}
	
	void setCutFacesClient(ros::NodeHandle& node, std::string serviceName)
	{
		cutFaceClient = node.serviceClient<human_vision_exchange::CutFaces>(serviceName.c_str());
	}
}
