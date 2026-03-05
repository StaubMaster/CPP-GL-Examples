
#include <iostream>
#include <sstream>
#include <exception>

#include "Debug.hpp"

#include "DirectoryInfo.hpp"
#include "FileInfo.hpp"
#include "Image.hpp"


#include "BitMap.hpp"





void Test()
{
	DirectoryInfo image_dir("../../media/Images"):
	Image img = image_dir.File("Test.png").LoadImage();
	img.Dispose();
}

int main(int argc, char * argv[])
{
	std::cout << "int main() ...\n";
	int ret = -1;
	Debug::NewFileInDir(DirectoryInfo("./logs/"));
	if (argc > 0)	{ Debug::Log << argv[0] << Debug::Done; }
	else			{ Debug::Log << "NoName" << Debug::Done; }
	{
		try
		{
			Test();
			ret = 0;
		}
		catch (std::exception & ex)
		{ Debug::Log << "Error: " << ex.what() << Debug::Done; }
		catch (...)
		{ Debug::Log << "Error: " << "Unknown" << Debug::Done; }
	}
	Debug::Log << "main() return " << ret << Debug::Done;
	return ret;
}
