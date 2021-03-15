#include <RosTopics.hpp>

namespace RT
{
	void grab_image(const sensor_msgs::ImagePtr&  image)
	{
		cv_bridge::CvImagePtr cv_ptr = cv_bridge::toCvCopy(image, sensor_msgs::image_encodings::BGR8);
		ZD::saveImage(cv_ptr);
	}
	
	void grab_objects(const zed_interfaces::Objects& objects)
	{
		std::vector<human_vision_exchange::Keypoints2d> keypoints2dVector;
		keypoints2dVector.resize(objects.objects.size());
		
		for(size_t i = 0; i < objects.objects.size(); i++)
		{
			human_vision_exchange::Keypoints2d keypoints2d;
			
            for (size_t c = 0; c < objects.objects[i].bbox_2d.size(); c++) 
            {
				geometry_msgs::Point32 point;
				point.x = objects.objects[i].bbox_2d[c].x;
				point.y = objects.objects[i].bbox_2d[c].y;
				point.z = 0.0;
				
				keypoints2d.points[c] = point;
            }
            
			keypoints2dVector.at(i) = keypoints2d;
		}
		
		ZD::saveKeypoints2d(keypoints2dVector);
	}
}
