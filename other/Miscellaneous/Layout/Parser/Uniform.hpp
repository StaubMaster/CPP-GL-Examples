#ifndef  LAYOUT_PARSER_UNIFORM_HPP
# define LAYOUT_PARSER_UNIFORM_HPP

# include "FileInfo.hpp"

namespace TextCommand { class Args; };

namespace Uniform
{
class Layout;
};

struct UniformLayoutParser
{
	Uniform::Layout *		Layout = nullptr;

	void	Parse(const TextCommand::Args & cmd_args);

//	void	File(const TextCommand::Args & cmd_args);
//	void	FilesDone(const TextCommand::Args & cmd_args);

	void	Matrix4x4(const TextCommand::Args & cmd_args);
	void	Angle(const TextCommand::Args & cmd_args);

	void	DisplaySize(const TextCommand::Args & cmd_args);
	void	Depth(const TextCommand::Args & cmd_args);

	static Uniform::Layout *	Parse(const FileInfo & file);
};

#endif