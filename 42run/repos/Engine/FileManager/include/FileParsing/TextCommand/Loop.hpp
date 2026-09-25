#ifndef  TEXT_COMMAND_LOOP_HPP
# define TEXT_COMMAND_LOOP_HPP

# include "Generics/Container/Binary.hpp"

# include "FileInfo.hpp"

namespace TextCommand
{
class Args;
class Func;

// seperate FuncSelector
struct Loop
{
	unsigned int	ExceptionCount = 0;

	FileInfo	File;

	Container::Binary<TextCommand::Func*>	Commands;

	void	Clear();

	void	Parse(const TextCommand::Args & cmd_args);

	void	ParseFile();
};
};

#endif