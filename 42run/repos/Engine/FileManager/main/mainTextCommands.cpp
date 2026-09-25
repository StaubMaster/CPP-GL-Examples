#include "FileParsing/Text/TextCommandStream.hpp"
#include "FileInfo.hpp"

#include <iostream>

int main(int argc, char * argv[])
{
	FileInfo file;
	if (argc > 1) { file = FileInfo(argv[1]); }
	else { file = FileInfo("text/commands.txt"); }
	std::cout << '\n';
	{
		TextCommandStream stream(file.LoadText());
		TextCommand cmd;
		while (stream.Continue(cmd))
		{
			std::cout << cmd << '\n';
		}
		std::cout << "done\n";
	}
	std::cout << '\n';
	return 0;
}
