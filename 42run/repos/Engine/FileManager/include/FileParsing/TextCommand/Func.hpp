#ifndef  TEXT_COMMAND_FUNC_HPP
# define TEXT_COMMAND_FUNC_HPP

# include <string>

namespace TextCommand
{
class Args;
struct Func
{
	std::string		Name;

	virtual ~Func();
	Func(std::string name);

	virtual bool	TryInvoke(const Args & cmd_args) const = 0;
	// seperate ?
	// bool Check(name)
	// void Invoke(args)
	// what if other stuff gets extracted from the name for checking
	// that gets lost after check and has to be extracted again
};
};

#endif