#include <RosServices.hpp>

namespace
{
	void displayHeadPoints(std::vector<std::vector<double> > &keypoints)
	{ 
		    auto displayVector = [](std::vector<double>&  point)
		    {
				if(point.size() >= 2)
				{
					std::cout<<"["<<point.at(0)<<", "<<point.at(1)<<"]"<<std::endl;
				}
				else
				{
					std::cout<<"[-, -]"<<std::endl;
				}
			};
		
			std::cout<<"uszy: "<<std::endl;
			std::vector<double> leftEar = keypoints.at(static_cast<size_t>(BODY_PARTS::LEFT_EAR));
			std::cout<<"- lewe: ";
			displayVector(leftEar);
			std::vector<double> rightEar = keypoints.at(static_cast<size_t>(BODY_PARTS::RIGHT_EAR));
			std::cout<<"- prawe: ";
			displayVector(rightEar);
			std::cout<<"oczy: "<<std::endl;
			std::vector<double> leftEye = keypoints.at(static_cast<size_t>(BODY_PARTS::LEFT_EYE));
			std::cout<<"- lewe: ";
			displayVector(leftEye);
			std::vector<double> rightEye = keypoints.at(static_cast<size_t>(BODY_PARTS::RIGHT_EYE));
			std::cout<<"- prawe: ";
			displayVector(rightEye);
			std::vector<double> nose = keypoints.at(static_cast<size_t>(BODY_PARTS::NOSE));
			std::cout<<"nos: ";
			displayVector(nose);
			std::vector<double> neck = keypoints.at(static_cast<size_t>(BODY_PARTS::NECK));
			std::cout<<"szyja: ";
			displayVector(neck);
	}
}

namespace RS
{
	bool doPhoto(human_vision_exchange::DoPhotoReceiver::Request  &req, human_vision_exchange::DoPhotoReceiver::Response &res)
	{
		human_vision_exchange::FaceVectorReceiver faceVectorClientData;
		
		int counter = 0;
		
		while(counter < 1)
		{
			ros::spinOnce();
			
			std::vector<human_vision_exchange::Keypoints2d> keypoints2dVector = ZD::getKeypoints2d();
			cv::Mat wholeImage = ZD::getImage();
			
			if(keypoints2dVector.size() > 0)
			{ 
				// cut faces
				human_vision_exchange::CutFaces cutFaces;
				cutFaces.request.keypoints.resize(keypoints2dVector.size());
				for(size_t i = 0; i < keypoints2dVector.size(); i++)
				{
					cutFaces.request.keypoints[i] = keypoints2dVector.at(i);
				}
				
				cv_bridge::CvImage cvImage = cv_bridge::CvImage(std_msgs::Header(), "bgr8", wholeImage);	
				cvImage.toImageMsg(cutFaces.request.image);
				
				MD::sendCutFacesClientRequest(cutFaces);
				
				if(cutFaces.response.faces.size() > 0)
				{
					// find faces vectors
					human_vision_exchange::FindFaceVectors findFaceVectors;
					findFaceVectors.request.faces = cutFaces.response.faces;
					
					MD::sendFindFaceVectorsClientRequest(findFaceVectors);
					
					if(findFaceVectors.response.faceVectors.faces.size() > 0)
					{
						// save image
						if(true)
						{
							cv_bridge::CvImagePtr cv_ptr = cv_bridge::toCvCopy(cutFaces.response.faces[0], sensor_msgs::image_encodings::BGR8);
							cv::Mat cvImage = cv_ptr->image;
							
							std::string path = SF::getPathToCurrentDirectory() + "../output/face" + std::to_string(counter);
							path = path + ".png";
//							std::cout<<"path = "<<path<<std::endl;
							cv::imwrite(path, cvImage);
						}
						
						human_vision_exchange::FaceVectorReceiver faceVectorClientData;
/*						for(size_t i = 0; i < findFaceVectors.response.faceVectors.faces[0].points.size(); i++)
						{
							faceVectorClientData.request.points[i] = findFaceVectors.response.faceVectors.faces[0].points[i];
						}  */
						faceVectorClientData.request.faceDescription = findFaceVectors.response.faceVectors.faces[0];
						MD::sendFaceVectorClientRequest(faceVectorClientData);
						res.status = true;
						counter++;
					}
				}
			}			
		}
		
		return true;
	}
}
