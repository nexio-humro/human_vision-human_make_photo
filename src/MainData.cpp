#include <MainData.hpp>

namespace
{
	ros::ServiceServer doPhotoService;
	ros::ServiceClient sendFaceVector;
	ros::ServiceClient findFaceVectorsClient;
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
		std::cout<<"sendFaceVectorClientRequest: fvr.response.status = "<<fvr.response.status<<std::endl;
	}
	
	void setSendFaceVectorClient(ros::NodeHandle& node, std::string serviceName)
	{
		sendFaceVector = node.serviceClient<human_vision_exchange::FaceVectorReceiver>(serviceName.c_str());
	}
	
	void sendFindFaceVectorsClientRequest(human_vision_exchange::FindFaceVectors& ffv)
	{
		findFaceVectorsClient.call(ffv);
	}
	
	void setSendFindFaceVectorsClient(ros::NodeHandle& node, std::string serviceName)
	{
		findFaceVectorsClient = node.serviceClient<human_vision_exchange::FindFaceVectors>(serviceName.c_str());
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
