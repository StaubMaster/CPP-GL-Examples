#include "FileParsing/TextCommand/Exceptions.hpp"
#include "FileParsing/TextCommand/Args.hpp"

#include <sstream>



TextCommand::Exception::Unknown::Unknown(const Args & cmd_args)
{
	std::stringstream ss;
	ss << '"' << cmd_args.Name() << '"';
	ss << " is unknown";
	ss << '.';
	Text = ss.str();
}



TextCommand::Exception::NotImplemented::NotImplemented(const Args & cmd_args)
{
	std::stringstream ss;
	ss << '"' << cmd_args.Name() << '"';
	ss << " is not implemented";
	ss << '.';
	Text = ss.str();
}



TextCommand::Exception::InvalidArgumentCount::InvalidArgumentCount(const Args & cmd_args, const char * comparison)
{
	std::stringstream ss;
	ss << cmd_args.Name() << ": ";
	ss << "invalid Argument Count: ";
	ss << cmd_args.Count();
	ss << " is not ";
	ss << '(' << comparison << ')';
	ss << '.';
	Text = ss.str();
}



TextCommand::Exception::InvalidArgument::InvalidArgument(const Args & cmd_args, unsigned int idx)
{
	std::stringstream ss;
	ss << cmd_args.Name() << ": ";
	ss << "Invalid Command Argument: ";
	ss << '"' << cmd_args.ToString(idx) << '"';
	ss << '.';
	Text = ss.str();
}
TextCommand::Exception::InvalidArgument::InvalidArgument(const Args & cmd_args, unsigned int idx,  const char * description)
{
	std::stringstream ss;
	ss << cmd_args.Name() << ": ";
	ss << "Invalid Command Argument: ";
	ss << '"' << cmd_args.ToString(idx) << '"';
	ss << ": ";
	ss << description;
	ss << '.';
	Text = ss.str();
}



TextCommand::Exception::InvalidState::InvalidState(const Args & cmd_args, const char * description)
{
	std::stringstream ss;
	ss << cmd_args.Name() << ": ";
	ss << "invalid State: ";
	ss << description;
	ss << '.';
	Text = ss.str();
}
