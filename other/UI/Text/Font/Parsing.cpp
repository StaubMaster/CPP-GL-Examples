#include "UI/Text/Font/Parsing.hpp"
#include "UI/Text/Font/Template.hpp"

#include "FileParsing/Text/TextCommand.hpp"
#include "FileParsing/Text/TextCommandStream.hpp"
#include "FileParsing/Text/Exceptions.hpp"

#include "FileInfo.hpp"
#include "DirectoryInfo.hpp"

#include "Debug.hpp"



UI::Text::Font::ParsingData::ParsingData(const FileInfo & file) :
	File(file),
	Data(NULL),
	Temp(NULL)
{ }
UI::Text::Font::ParsingData::~ParsingData()
{
	delete Temp;
}



void UI::Text::Font::ParsingData::Parse(const TextCommand & cmd)
{
	std::string name = cmd.Name();
	if (name == "")				{ /*std::cout << "empty\n";*/ }
	else if (name == "Type")	{ Parse_Type(cmd); }

	else if (name == "Image")		{ Parse_Image(cmd); }
	else if (name == "Scale")		{ Parse_Scale(cmd); }
	else if (name == "Character")	{ Parse_Character(cmd); }

	else						{ Debug::Log << "unknown: " << cmd << Debug::Done; }
}

void UI::Text::Font::ParsingData::Parse_Type(const TextCommand & cmd)
{
	if (!(cmd.Count() == 1)) { throw InvalidCommandArgumentCount(cmd, "n == 1"); }
}

void UI::Text::Font::ParsingData::Parse_Image(const TextCommand & cmd)
{
	if (!(cmd.Count() == 1)) { throw InvalidCommandArgumentCount(cmd, "n == 1"); }

	DirectoryInfo dir(File.Directory());
	FileInfo imgFile(dir.File(cmd.ToString(0).c_str()));
	if (imgFile.Exists())
	{
		Image img = imgFile.LoadImage();
		if (!img.Empty())
		{
			Temp -> Insert_Image(img);
		}
	}
}
void UI::Text::Font::ParsingData::Parse_Scale(const TextCommand & cmd)
{
	if (!(cmd.Count() == 2)) { throw InvalidCommandArgumentCount(cmd, "n == 2"); }

	Temp -> Change_Scale(Point2D(cmd.ToFloat(0), cmd.ToFloat(1)));
}
void UI::Text::Font::ParsingData::Parse_Character(const TextCommand & cmd)
{
	if (!(cmd.Count() == 5)) { throw InvalidCommandArgumentCount(cmd, "n == 5"); }

	Point2D pos(cmd.ToFloat(1), cmd.ToFloat(2));
	Point2D size(cmd.ToFloat(3), cmd.ToFloat(4));

	if (cmd.ToString(0) == "Default")
	{ Temp -> Change_DefaultCharacter(pos, size); }
	else
	{ Temp -> Insert_Character(cmd.ToUInt32(0), pos, size); }
}



UI::Text::Font * UI::Text::Font::Parse(const FileInfo & file)
{
	ParsingData data(file);
	data.Data = new UI::Text::Font();
	data.Temp = new UI::Text::Font::Template(*data.Data);

	TextCommandStream stream(file.LoadText());
	TextCommand cmd;
	while (stream.Continue(cmd))
	{
		data.Parse(cmd);
	}

	return data.Data;
}
