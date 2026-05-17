#include "Text/Font/Parsing.hpp"

#include "FileParsing/Text/TextCommand.hpp"
#include "FileParsing/Text/TextCommandStream.hpp"
#include "FileParsing/Text/Exceptions.hpp"

#include "FileInfo.hpp"
#include "DirectoryInfo.hpp"

#include "Debug.hpp"



UI::Text::Font::ParsingData::ParsingData(const FileInfo & file)
	: File(file)
	, Data(NULL)
	, Scale(VectorF2(1, 1))
	, Range(nullptr)
{ }
UI::Text::Font::ParsingData::~ParsingData()
{ }



void UI::Text::Font::ParsingData::Parse(const TextCommand & cmd)
{
	std::string name = cmd.Name();
	if (name == "")				{ /*std::cout << "empty\n";*/ }
	else if (name == "Type")	{ Parse_Type(cmd); }

	else if (name == "Image")		{ Parse_Image(cmd); }
	else if (name == "Scale")		{ Parse_Scale(cmd); }
	else if (name == "Character")	{ Parse_Character(cmd); }
	else if (name == "Range")		{ Parse_Range(cmd); }

	else							{ Debug::Log << "unknown: " << cmd << Debug::Done; }
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
			Data -> AtlasTexture = img;
		}
	}
}
void UI::Text::Font::ParsingData::Parse_Scale(const TextCommand & cmd)
{
	if (!(cmd.Count() == 2)) { throw InvalidCommandArgumentCount(cmd, "n == 2"); }

	Scale = VectorF2(cmd.ToFloat(0), cmd.ToFloat(1));
}
void UI::Text::Font::ParsingData::Parse_Character(const TextCommand & cmd)
{
	if (!(cmd.Count() == 5)) { throw InvalidCommandArgumentCount(cmd, "n == 5"); }

	VectorF2 pos(cmd.ToFloat(1), cmd.ToFloat(2));
	VectorF2 size(cmd.ToFloat(3), cmd.ToFloat(4));

	if (cmd.ToString(0) == "Default")
	{
		Data -> DefaultCharacter.Box.Min = pos / Scale;
		Data -> DefaultCharacter.Box.Max = (pos + size) / Scale;
	}
	else
	{
		Character chr;
		chr.Code = cmd.ToUInt32(0);
		chr.Box.Min = (pos / Scale);
		chr.Box.Max = (pos + size) / Scale;
		if (Range == nullptr)
		{
			Data -> Characters.Insert(chr);
		}
		else
		{
			Range -> Characters.Insert(chr);
		}
	}
}

void UI::Text::Font::ParsingData::Parse_Range(const TextCommand & cmd)
{
	if (!(cmd.Count() == 0 || cmd.Count() == 2)) { throw InvalidCommandArgumentCount(cmd, "n == 0 || n == 2"); }

	if (cmd.Count() == 0)
	{
		if (Range != nullptr)
		{
			Range -> Characters.Trim();
			Range = nullptr;
		}
	}
	else
	{
		if (Range != nullptr)
		{
			Range -> Characters.Trim();
		}
		Range = new CharacterRange();
		Range -> CodeMin = cmd.ToUInt32(0);
		Range -> CodeMax = cmd.ToUInt32(1);
		Data -> CharacterRanges.Insert(Range);
	}
}



UI::Text::Font * UI::Text::Font::Parse(const FileInfo & file)
{
	ParsingData data(file);
	data.Data = new UI::Text::Font();

	TextCommandStream stream(file.LoadText());
	TextCommand cmd;
	while (stream.Continue(cmd))
	{
		data.Parse(cmd);
	}

	data.Data -> Characters.Trim();
	data.Data -> CharacterRanges.Trim();

	return data.Data;
}
