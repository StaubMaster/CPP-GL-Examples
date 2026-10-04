#include "Layout/Parser/Uniform.hpp"

#include "Graphics/Uniform/General/Layout.hpp"
#include "Graphics/Uniform/_Include.hpp"

#include "FileParsing/TextCommand/Args.hpp"
#include "FileParsing/TextCommand/ArgsStream.hpp"
#include "FileParsing/TextCommand/Exceptions.hpp"

#include <iostream>



void UniformLayoutParser::Parse(const TextCommand::Args & cmd_args)
{
	try
	{
		std::string name = cmd_args.Name();
		if (name == "")						{ }

//		else if (name == "File")			{ File(cmd_args); }
//		else if (name == "FilesDone")		{ FilesDone(cmd_args); }

		else if (name == "Matrix4x4")		{ Matrix4x4(cmd_args); }
		else if (name == "Angle")			{ Angle(cmd_args); }
		else if (name == "DisplaySize")		{ DisplaySize(cmd_args); }
		else if (name == "Depth")			{ Depth(cmd_args); }

		else								{ std::cout << "unknown: " << cmd_args << "\n"; }
	}
	catch(std::exception & ex)
	{
		std::cout << "Exception TextCommand: " << cmd_args << '\n';
	}
}



/*void UniformLayoutParser::File(const TextCommand::Args & cmd_args)
{
	if (!(cmd_args.Count() == 1)) { throw TextCommand::Exception::InvalidArgumentCount(cmd_args, "n == 1"); }
}*/
/*void UniformLayoutParser::FilesDone(const TextCommand::Args & cmd_args)
{ }*/



void UniformLayoutParser::Matrix4x4(const TextCommand::Args & cmd_args)
{
	if (!(cmd_args.Count() == 1)) { throw TextCommand::Exception::InvalidArgumentCount(cmd_args, "n == 1"); }

	if (Layout == nullptr) { throw TextCommand::Exception::InvalidState(cmd_args, "Layout missing"); }

	Uniform::Matrix4x4 * uniform = new Uniform::Matrix4x4(*Layout, cmd_args.ToString(0));
//	uniform -> Change(cmd_args.ToString(0));
	(void)uniform;
}
void UniformLayoutParser::Angle(const TextCommand::Args & cmd_args)
{
	if (!(cmd_args.Count() == 1)) { throw TextCommand::Exception::InvalidArgumentCount(cmd_args, "n == 1"); }

	if (Layout == nullptr) { throw TextCommand::Exception::InvalidState(cmd_args, "Layout missing"); }

	Uniform::Angle * uniform = new Uniform::Angle(*Layout, cmd_args.ToString(0));
//	uniform -> Change(cmd_args.ToString(0));
	(void)uniform;
}



void UniformLayoutParser::DisplaySize(const TextCommand::Args & cmd_args)
{
	if (!(cmd_args.Count() == 1)) { throw TextCommand::Exception::InvalidArgumentCount(cmd_args, "n == 1"); }

	if (Layout == nullptr) { throw TextCommand::Exception::InvalidState(cmd_args, "Layout missing"); }

	Uniform::DisplaySize * uniform = new Uniform::DisplaySize(*Layout, cmd_args.ToString(0));
//	uniform -> Change(cmd_args.ToString(0));
	(void)uniform;
}
void UniformLayoutParser::Depth(const TextCommand::Args & cmd_args)
{
	if (!(cmd_args.Count() == 1)) { throw TextCommand::Exception::InvalidArgumentCount(cmd_args, "n == 1"); }

	if (Layout == nullptr) { throw TextCommand::Exception::InvalidState(cmd_args, "Layout missing"); }

	Uniform::Depth * uniform = new Uniform::Depth(*Layout, cmd_args.ToString(0));
//	uniform -> Change(cmd_args.ToString(0));
	(void)uniform;
}



#include "FileParsing/TextCommand/ArgsStream.hpp"

Uniform::Layout * UniformLayoutParser::Parse(const FileInfo & file)
{
	UniformLayoutParser data;
	data.Layout = new Uniform::Layout();

	TextCommand::ArgsStream stream(file.LoadText());
	TextCommand::Args cmd_args;
	while (stream.Continue(cmd_args))
	{
		data.Parse(cmd_args);
	}

	return data.Layout;
}
