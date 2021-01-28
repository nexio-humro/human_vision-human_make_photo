#include <RosServices.hpp>
#include <dlib/image_io.h>

namespace
{
	void displayHeadPoints(sl::ObjectData &obj)
	{ 
			auto keypoints = obj.keypoint_2d;
			std::cout<<"uszy: "<<std::endl;
			sl::float2 leftEar = keypoints[getIdx(sl::BODY_PARTS::LEFT_EAR)];
			std::cout<<"- lewe: "<<leftEar<<std::endl;
			sl::float2 rightEar = keypoints[getIdx(sl::BODY_PARTS::RIGHT_EAR)];
			std::cout<<"- prawe: "<<rightEar<<std::endl;
			std::cout<<"oczy: "<<std::endl;
			sl::float2 leftEye = keypoints[getIdx(sl::BODY_PARTS::LEFT_EYE)];
			std::cout<<"- lewe: "<<leftEye<<std::endl;
			sl::float2 rightEye = keypoints[getIdx(sl::BODY_PARTS::RIGHT_EYE)];
			std::cout<<"- prawe: "<<rightEye<<std::endl;
			sl::float2 nose = keypoints[getIdx(sl::BODY_PARTS::NOSE)];
			std::cout<<"nos: "<<nose<<std::endl;
			sl::float2 neck = keypoints[getIdx(sl::BODY_PARTS::NECK)];
			std::cout<<"szyja: "<<nose<<std::endl;
	}
}

namespace RS
{
	bool doPhoto(human_vision_exchange::DoPhotoReceiver::Request  &req, human_vision_exchange::DoPhotoReceiver::Response &res)
	{
		const int vectorSize = 128;
		dlib::matrix<float,0,1> result;
		
		int counter = 0;
		
		FCF::pairFacesImages faces;
		
		while(counter < 1)
		{
			ros::spinOnce();
			
			sl::Objects obiekty = ZD::getObjects();
			cv::Mat zdjecie = ZD::getImage();
			faces = FCF::extractAllFaces(zdjecie, obiekty);
			
			if(obiekty.object_list.size() > 0)
			{
				displayHeadPoints(obiekty.object_list.at(0));
			}  
			
			std::vector<dlib::matrix<float,0,1>> faceDescriptions;
			
			if(faces.first.size() > 0)
			{
				faceDescriptions = DlibFrontalFaceDetection::instance()->computeFaceVectors(faces.first);
				if(faceDescriptions.size() > 0)
				{
					result = faceDescriptions.at(0);
					counter++;
					
					// save image
					if(true)
					{
						std::string path = SF::getPathToCurrentDirectory() + "../output/face" + std::to_string(counter);
						path = path + ".png";
						std::cout<<"path = "<<path<<std::endl;
						dlib::save_png (faces.first.at(0), path);
					}
				}
			}
			
		}
		
		if(result.size() == vectorSize)
		{
			human_vision_exchange::FaceVectorReceiver faceVectorClientData;
			for(size_t i = 0; i < vectorSize; i++)
			{
				faceVectorClientData.request.points[i] = result(i);
			}
			MD::sendFaceVectorClientRequest(faceVectorClientData);
			res.status = true;
		}
		
		return true;
	}
}
