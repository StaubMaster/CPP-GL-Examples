#ifndef  LAYOUT_PARSER_ATTRIBUTE_HPP
# define LAYOUT_PARSER_ATTRIBUTE_HPP

# include "FileInfo.hpp"

namespace TextCommand { class Args; };

namespace Attribute
{
class Layout;
};

struct AttributeLayoutParser
{
	Attribute::Layout *		Layout = nullptr;

	void	Parse(const TextCommand::Args & cmd_args);

	void	PutDivisor(const TextCommand::Args & cmd_args);

	void	PutMatrix4x4(const TextCommand::Args & cmd_args);

	static Attribute::Layout *	Parse(const FileInfo & file);
};

#endif