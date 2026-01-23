#ifndef  UI_TEXT_FONT_PARSING_HPP
# define UI_TEXT_FONT_PARSING_HPP

# include "FileInfo.hpp"
# include "UI/Text/Font/Font.hpp"

# include "ValueType/Point2D.hpp"

# include <string>
# include <exception>

class TextCommand;

namespace UI
{

namespace Text
{

struct Font::ParsingData
{
	FileInfo			File;
	Font *				Data;
	Font::Template *	Temp;

	ParsingData(const FileInfo & file);
	~ParsingData();

	void Parse(const TextCommand & cmd);

	void Parse_Type(const TextCommand & cmd);

	void Parse_Image(const TextCommand & cmd);
	void Parse_Scale(const TextCommand & cmd);
	void Parse_Character(const TextCommand & cmd);
};

};

};

#endif