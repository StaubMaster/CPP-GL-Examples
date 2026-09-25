
#include <string>

#include <vector>
#include <sstream>

#include <iostream>

#include "FileInfo.hpp"
#include "FileParsing/StringHelp.hpp"

class LineCommand
{
	public:
		std::string Name;
		std::vector<std::string> Args;
		unsigned int Count;
	public:
		LineCommand(std::string text);



	public:
template <typename ObjectType>
static void Split(const FileInfo & file, ObjectType & object, void (ObjectType::*func)(const LineCommand &))
{
	std::stringstream stream(file.LoadText());
	std::string segment;
	while (std::getline(stream, segment, '\n'))
	{
		segment = StringHelp::RemoveFromString(segment, StringHelp::CharPallet("\n\r"));
		segment = StringHelp::RemoveFromString(segment, StringHelp::CharPallet("#"), StringHelp::CharPallet("\n"));
		(object.*func)(LineCommand(segment));
	}
}

template <typename ObjectType>
static ObjectType * Split(const FileInfo & file, ObjectType * object, ObjectType * (*func)(ObjectType *, const LineCommand &))
{
	std::stringstream stream(file.LoadText());
	std::string segment;
	while (std::getline(stream, segment, '\n'))
	{
		segment = StringHelp::RemoveFromString(segment, StringHelp::CharPallet("\n\r"));
		segment = StringHelp::RemoveFromString(segment, StringHelp::CharPallet("#"), StringHelp::CharPallet("\n"));
		object = (*func)(object, LineCommand(segment));
	}
	return object;
}


};
