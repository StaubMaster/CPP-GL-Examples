#include "Layout/Parser/Attribute.hpp"

#include "Graphics/Attribute/General/Layout.hpp"
#include "Graphics/Attribute/_Include.hpp"

#include "FileParsing/Text/TextCommand.hpp"
#include "FileParsing/Text/TextCommandStream.hpp"
#include "FileParsing/Text/Exceptions.hpp"

#include <iostream>



void AttributeLayoutParser::Parse(const TextCommandArgs & cmd_args)
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



void AttributeLayoutParser::PutDivisor(const TextCommandArgs & cmd_args)
{
	if (!(cmd_args.Count() == 1)) { throw InvalidCommandArgumentCount(cmd_args, "n == 1"); }

	if (Layout != nullptr) { throw CommandInvalidState(cmd_args, "Layout already"); }

	Layout = new Attribute::Layout(cmd_args.ToUInt32(0));
}



void AttributeLayoutParser::PutMatrix4x4(const TextCommandArgs & cmd_args)
{
	if (!(cmd_args.Count() == 1)) { throw InvalidCommandArgumentCount(cmd_args, "n == 1"); }

	if (Layout == nullptr) { throw CommandInvalidState(cmd_args, "Layout missing"); }

	Attribute::Matrix4x4 * attribute = new Attribute::Matrix4x4(*Layout);
	attribute -> Change(cmd_args.ToInt32(0));
}



#include "FileParsing/Text/TextCommandStream.hpp"

Attribute::Layout * AttributeLayoutParser::Parse(const FileInfo & file)
{
	AttributeLayoutParser data;

	TextCommandStream stream(file.LoadText());
	TextCommand cmd;
	while (stream.Continue(cmd))
	{
		data.Parse(cmd);
	}

	if (data.Layout != nullptr)
	{
		data.Layout -> CalcStride();
	}

	return data.Layout;
}
