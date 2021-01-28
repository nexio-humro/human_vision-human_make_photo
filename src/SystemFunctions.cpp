#include <SystemFunctions.hpp>

namespace
{
	std::string pathToCurrentDirectory;
}

namespace SF
{

	
	std::string getPathToCurrentDirectory()
	{
		if(pathToCurrentDirectory == "")
		{
			pathToCurrentDirectory = ros::package::getPath("human_make_photo") + "/src/";
		}
		
		return pathToCurrentDirectory;
	}
}
