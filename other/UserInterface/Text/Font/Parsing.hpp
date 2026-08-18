#ifndef  UI_TEXT_FONT_PARSING_HPP
# define UI_TEXT_FONT_PARSING_HPP

# include "FileInfo.hpp"
# include "Text/Font/Font.hpp"

# include "ValueType/Vector/F2.hpp"

# include <string>
# include <exception>

class TextCommandArgs;

namespace UI
{

namespace Text
{

struct Font::ParsingData
{
	FileInfo			File;
	Font *				Data;
	VectorF2			Scale;
	CharacterRange *	Range;

	ParsingData(const FileInfo & file);
	~ParsingData();

	void	Parse(const TextCommandArgs & cmd_args);

	void	Parse_Type(const TextCommandArgs & cmd_args);

	void	Parse_Image(const TextCommandArgs & cmd_args);
	void	Parse_Scale(const TextCommandArgs & cmd_args);
	void	Parse_Character(const TextCommandArgs & cmd_args);

	void	Parse_Range(const TextCommandArgs & cmd_args);
};

};

};

#endif