#include "Layout/Parser/Attribute.hpp"

#include "Graphics/Attribute/General/Layout.hpp"
#include "Graphics/Attribute/_Include.hpp"

#include "FileParsing/TextCommand/Args.hpp"
#include "FileParsing/TextCommand/ArgsStream.hpp"
#include "FileParsing/TextCommand/Exceptions.hpp"

#include <iostream>



void AttributeLayoutParser::Parse(const TextCommand::Args & cmd_args)
{
	try
	{
		std::string name = cmd_args.Name();
		if (name == "")					{ }
		else if (name == "Divisor")		{ PutDivisor(cmd_args); }
		else if (name == "Matrix4x4")	{ PutMatrix4x4(cmd_args); }
		else							{ std::cout << "unknown: " << cmd_args << "\n"; }
	}
	catch(std::exception & ex)
	{
		std::cout << "Exception TextCommand: " << cmd_args << '\n';
	}
}



void AttributeLayoutParser::PutDivisor(const TextCommand::Args & cmd_args)
{
	if (!(cmd_args.Count() == 1)) { throw TextCommand::Exception::InvalidArgumentCount(cmd_args, "n == 1"); }

	if (Layout != nullptr) { throw TextCommand::Exception::InvalidState(cmd_args, "Layout already"); }

	Layout = new Attribute::Layout(cmd_args.ToUInt32(0));
}



void AttributeLayoutParser::PutMatrix4x4(const TextCommand::Args & cmd_args)
{
	if (!(cmd_args.Count() == 1)) { throw TextCommand::Exception::InvalidArgumentCount(cmd_args, "n == 1"); }

	if (Layout == nullptr) { throw TextCommand::Exception::InvalidState(cmd_args, "Layout missing"); }

	Attribute::Matrix4x4 * attribute = new Attribute::Matrix4x4(*Layout);
	attribute -> Change(cmd_args.ToInt32(0));
}



#include "FileParsing/TextCommand/ArgsStream.hpp"

Attribute::Layout * AttributeLayoutParser::Parse(const FileInfo & file)
{
	AttributeLayoutParser data;

	TextCommand::ArgsStream stream(file.LoadText());
	TextCommand::Args cmd_args;
	while (stream.Continue(cmd_args))
	{
		data.Parse(cmd_args);
	}

	if (data.Layout != nullptr)
	{
		data.Layout -> CalcStride();
	}

	return data.Layout;
}
