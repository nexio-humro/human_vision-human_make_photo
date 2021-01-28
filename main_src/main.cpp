// include ros
#include "ros/ros.h"
#include "ros/package.h"

#include <RosTopics.hpp>
#include <MainData.hpp>
#include <RosServices.hpp>
#include <SystemFunctions.hpp>
#include <DlibFrontalFaceDetection.hpp>
#include <FaceCuttingFunctions.hpp>
#include <DlibFrontalFaceDetectionPaths.hpp>

int main(int argc, char **argv) 
{
	ros::init(argc, argv, "human_make_photo");
	ros::NodeHandle node("/human_make_photo/");
	
	ros::Subscriber imageGetter = node.subscribe("/zed2/zed_node/left/image_rect_color", 1000, RT::grab_image);
	ros::Subscriber objectsGetter = node.subscribe("/zed2/zed_node/obj_det/objects", 1000, RT::grab_objects);
	MD::setDoPhotoServer(node, "doPhoto", RS::doPhoto);
	MD::setSendFaceVectorClient(node, "/human_recognition/facesVector");

	ros::Rate loop_rate(10);

	std::string path = DFFDP::getPathToDetector();
	DlibFrontalFaceDetection::instance()->loadModel(path.c_str());
	
	ros::spin();
	
	return 0;
}
