#include "FileParsing/LineCommand.hpp"
#include "FileParsing/StringHelp.hpp"



LineCommand::LineCommand(std::string text)
{
	std::vector<std::string> segments;
	{
		std::stringstream stream(text);
		std::string segment;
		while (std::getline(stream, segment, ' '))
		{
			segment = StringHelp::RemoveFromString(segment, StringHelp::CharPallet(" \t"));
			segments.push_back(segment);
		}
	}

	if (segments.size() != 0)
	{
		Name = segments[0];
	}
	for (size_t i = 1; i < segments.size(); i++)
	{
		Args.push_back(segments[i]);
	}
	Count = Args.size();
}
