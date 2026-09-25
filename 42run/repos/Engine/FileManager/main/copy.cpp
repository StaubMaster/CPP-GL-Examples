#include "FileInfo.hpp"
#include <iostream>

int main()
{
	{
		std::cout << "File 0\n";
		FileInfo file0("main/copy.cpp");
		std::cout << "File 0 show\n\n\n";
		std::cout << file0 << "\n";
		std::cout << "File 0 done\n\n\n";
		
		std::cout << "File 1\n";
		FileInfo file1;
		std::cout << "File 1 show\n\n\n";
		std::cout << file1 << "\n";
		std::cout << "File 1 done\n\n\n";

		file1 = file0;
		std::cout << file1 << "\n";
	}
	return 0;
}
