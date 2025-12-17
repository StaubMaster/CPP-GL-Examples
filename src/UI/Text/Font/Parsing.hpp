#ifndef  UI_TEXT_FONT_PARSING_HPP
# define UI_TEXT_FONT_PARSING_HPP

# include "UI/Text/Font/Font.hpp"
# include "Parsing/ParsingCommand.hpp"

# include "DataStruct/Point2D.hpp"

# include <string>
# include <exception>

class FileContext;

namespace UI
{

namespace Text
{

struct Font::ParsingData : public ParsingCommand::EnvironmentData
{
	Font *				Data;
	Font::Template *	Temp;

	ParsingData(const FileContext & file);
	~ParsingData();

	void Parse(const ParsingCommand & cmd) override;

	void Parse_Type(const ParsingCommand & cmd);

	void Parse_Image(const ParsingCommand & cmd);
	void Parse_Scale(const ParsingCommand & cmd);
	void Parse_Character(const ParsingCommand & cmd);
};

};

};

#endif