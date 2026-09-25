#ifndef  TEXT_COMMAND_ARGS_STREAM_HPP
# define TEXT_COMMAND_ARGS_STREAM_HPP

# include "Args.hpp"
# include "LineStream.hpp"

namespace TextCommand
{
class ArgsStream
{
	private:
	LineStream	_Stream;

	public:
	~ArgsStream();
	ArgsStream(const std::string & text);

	public:
	bool	Continue(Args & cmd_args);
};
};

#endif