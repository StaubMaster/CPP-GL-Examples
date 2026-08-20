#ifndef  UI_TEXT_FONT_PARSING_HPP
# define UI_TEXT_FONT_PARSING_HPP

# include "FileInfo.hpp"
# include "Text/Font/Font.hpp"

# include "ValueType/Vector/F2.hpp"

# include <string>
# include <exception>

namespace TextCommand { class Args; };

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

	void	Parse(const TextCommand::Args & cmd_args);

	void	Parse_Type(const TextCommand::Args & cmd_args);

	void	Parse_Image(const TextCommand::Args & cmd_args);
	void	Parse_Scale(const TextCommand::Args & cmd_args);
	void	Parse_Character(const TextCommand::Args & cmd_args);

	void	Parse_Range(const TextCommand::Args & cmd_args);
};

};

};

#endif