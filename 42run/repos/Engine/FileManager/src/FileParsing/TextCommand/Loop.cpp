#include "FileParsing/TextCommand/Loop.hpp"
#include "FileParsing/TextCommand/Args.hpp"
#include "FileParsing/TextCommand/Func.hpp"
#include "FileParsing/TextCommand/Exceptions.hpp"

#include <string>
#include <iostream>



void TextCommand::Loop::Clear()
{
	for (unsigned int i = 0; i < Commands.Count(); i++)
	{
		delete Commands[i];
	}
	Commands.Clear();
}

void TextCommand::Loop::Parse(const TextCommand::Args & cmd_args)
{
	try
	{
		if (cmd_args.Name() == "")
		{
			return;
		}
		for (unsigned int i = 0; i < Commands.Count(); i++)
		{
			const TextCommand::Func & cmd_func = *Commands[i];
			if (cmd_func.TryInvoke(cmd_args))
			{
				return;
			}
		}
		throw TextCommand::Exception::Unknown(cmd_args);
	}
	catch (std::exception & ex)
	{
		if (ExceptionCount == 0)
		{
			std::cout << "Exception in " << File.Path << '\n';
		}
		std::cout << ex.what() << " caused by " << cmd_args << '\n';
		ExceptionCount++;
	}
}



#include "FileInfo.hpp"
#include "FileParsing/TextCommand/ArgsStream.hpp"
void TextCommand::Loop::ParseFile()
{
	//std::cout << "Parsing File " << file.Path << " ....\n";

	TextCommand::ArgsStream stream(File.LoadText());
	TextCommand::Args cmd_args;
	while (stream.Continue(cmd_args))
	{
		Parse(cmd_args);
	}

	//std::cout << "Parsing File " << file.Path << " done\n";
}
