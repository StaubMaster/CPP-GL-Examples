#include "UI/Text/Font/Parsing.hpp"
#include "UI/Text/Font/Template.hpp"

#include "FileContext.hpp"
#include "DirectoryContext.hpp"



UI::Text::Font::ParsingData::ParsingData(const FileContext & file) :
	ParsingCommand::EnvironmentData(file),
	Data(NULL),
	Temp(NULL)
{ }
UI::Text::Font::ParsingData::~ParsingData()
{
	delete Temp;
}



void UI::Text::Font::ParsingData::Parse(const ParsingCommand & cmd)
{
	std::string name = cmd.Name();
	if (name == "")				{ /*std::cout << "empty\n";*/ }
	else if (name == "Type")	{ Parse_Type(cmd); }

	else if (name == "Image")		{ Parse_Image(cmd); }
	else if (name == "Scale")		{ Parse_Scale(cmd); }
	else if (name == "Character")	{ Parse_Character(cmd); }

	else						{ Debug::Log << "unknown: " << cmd << Debug::Done; }
}

void UI::Text::Font::ParsingData::Parse_Type(const ParsingCommand & cmd)
{
	if (!cmd.CheckCount(CountCheckEqual(1))) { throw ParsingCommand::ExceptionInvalidCount(cmd, CountCheckEqual(1)); }
}

void UI::Text::Font::ParsingData::Parse_Image(const ParsingCommand & cmd)
{
	if (!cmd.CheckCount(CountCheckEqual(1))) { throw ParsingCommand::ExceptionInvalidCount(cmd, CountCheckEqual(1)); }

	DirectoryContext dir(File.Directory());
	FileContext imgFile(dir.File(cmd.ToString(0)));
	if (imgFile.Exists())
	{
		Image * img = imgFile.LoadImagePNG();
		if (img != NULL)
		{
			Temp -> Insert_Image(img);
		}
	}
}
void UI::Text::Font::ParsingData::Parse_Scale(const ParsingCommand & cmd)
{
	if (!cmd.CheckCount(CountCheckEqual(2))) { throw ParsingCommand::ExceptionInvalidCount(cmd, CountCheckEqual(2)); }

	Temp -> Change_Scale(Point2D(cmd.ToFloat(0), cmd.ToFloat(1)));
}
void UI::Text::Font::ParsingData::Parse_Character(const ParsingCommand & cmd)
{
	if (!cmd.CheckCount(CountCheckEqual(5))) { throw ParsingCommand::ExceptionInvalidCount(cmd, CountCheckEqual(5)); }

	Point2D pos(cmd.ToFloat(1), cmd.ToFloat(2));
	Point2D size(cmd.ToFloat(3), cmd.ToFloat(4));

	if (cmd.ToString(0) == "Default")
	{ Temp -> Change_DefaultCharacter(pos, size); }
	else
	{ Temp -> Insert_Character(cmd.ToUInt32(0), pos, size); }
}



UI::Text::Font * UI::Text::Font::Parse(const FileContext & file)
{
	ParsingData data(file);
	data.Data = new UI::Text::Font();
	data.Temp = new UI::Text::Font::Template(*data.Data);

	ParsingCommand::SplitFileIntoCommands(data);

	return data.Data;
}
