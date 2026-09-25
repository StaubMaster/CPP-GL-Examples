#ifndef  TEXT_COMMAND_EXCEPTIONS_HPP
# define TEXT_COMMAND_EXCEPTIONS_HPP

# include "TextExceptionBase.hpp"

namespace TextCommand
{
class Args;

namespace Exception
{
class Fatal : public TextExceptionBase
{
	public: Fatal();
	public: Fatal(const Args & cmd_args);
	public: Fatal(const Args & cmd_args, const char * description);
};
class Unknown : public TextExceptionBase
{
	public: Unknown(const Args & cmd_args);
};
class NotImplemented : public TextExceptionBase
{
	public: NotImplemented(const Args & cmd_args);
};
class InvalidArgumentCount : public TextExceptionBase
{
	public: InvalidArgumentCount(const Args & cmd_args, const char * comparison);
};
class InvalidArgument : public TextExceptionBase
{
	public: InvalidArgument(const Args & cmd_args, unsigned int idx);
	public: InvalidArgument(const Args & cmd_args, unsigned int idx, const char * description);
};
class InvalidState : public TextExceptionBase
{
	public: InvalidState(const Args & cmd_args, const char * description);
};
};
};

#endif