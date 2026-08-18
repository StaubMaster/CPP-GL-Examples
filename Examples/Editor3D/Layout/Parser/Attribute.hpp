#ifndef  LAYOUT_PARSER_ATTRIBUTE_HPP
# define LAYOUT_PARSER_ATTRIBUTE_HPP

# include "FileInfo.hpp"

class TextCommandArgs;

namespace Attribute
{
class Layout;
};

struct AttributeLayoutParser
{
	Attribute::Layout *		Layout = nullptr;

	void	Parse(const TextCommandArgs & cmd_args);

	void	PutDivisor(const TextCommandArgs & cmd_args);

	void	PutMatrix4x4(const TextCommandArgs & cmd_args);

	static Attribute::Layout *	Parse(const FileInfo & file);
};

#endif