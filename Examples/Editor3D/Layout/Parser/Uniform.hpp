#ifndef  LAYOUT_PARSER_UNIFORM_HPP
# define LAYOUT_PARSER_UNIFORM_HPP

# include "FileInfo.hpp"

class TextCommand;
typedef TextCommand TextCommandArgs;

namespace Uniform
{
class Layout;
};

struct UniformLayoutParser
{
	Uniform::Layout *		Layout = nullptr;

	void	Parse(const TextCommandArgs & cmd_args);

//	void	File(const TextCommandArgs & cmd_args);
//	void	FilesDone(const TextCommandArgs & cmd_args);

	void	Matrix4x4(const TextCommandArgs & cmd_args);
	void	Angle(const TextCommandArgs & cmd_args);

	void	DisplaySize(const TextCommandArgs & cmd_args);
	void	Depth(const TextCommandArgs & cmd_args);

	static Uniform::Layout *	Parse(const FileInfo & file);
};

#endif