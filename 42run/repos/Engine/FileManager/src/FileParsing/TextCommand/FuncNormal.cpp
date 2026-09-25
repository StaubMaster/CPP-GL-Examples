#include "FileParsing/TextCommand/FuncNormal.hpp"



TextCommand::FuncNormal::~FuncNormal()
{ }



bool TextCommand::FuncNormal::TryInvoke(const Args & cmd_args) const
{
	if (Name == cmd_args.Name())
	{
		Function(cmd_args);
		return true;
	}
	return false;
}
