#include "FileParsing/TextCommand/ArgsStream.hpp"
#include "FileParsing/StringHelp.hpp"
#include <string>

#include <iostream>



TextCommand::ArgsStream::~ArgsStream()
{ }
TextCommand::ArgsStream::ArgsStream(const std::string & text)
	: _Stream(text)
{ }



bool TextCommand::ArgsStream::Continue(Args & cmd_args)
{
	std::string line;
	if (_Stream.Continue(line))
	{
		line = StringHelp::RemoveFromString(line, StringHelp::CharPallet("#"), StringHelp::CharPallet("\n"));
		cmd_args.Split(line);
		return true;
	}
	return false;
}
