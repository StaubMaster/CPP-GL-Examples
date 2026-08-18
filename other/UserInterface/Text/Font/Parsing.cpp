#include "Text/Font/Parsing.hpp"

#include "FileParsing/Text/TextCommandArgs.hpp"
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



void UI::Text::Font::ParsingData::Parse(const TextCommandArgs & cmd_args)
{
	std::string name = cmd_args.Name();

	if (name == "")				{ /*std::cout << "empty\n";*/ }
	else if (name == "Type")	{ Parse_Type(cmd_args); }

	else if (name == "Image")		{ Parse_Image(cmd_args); }
	else if (name == "Scale")		{ Parse_Scale(cmd_args); }
	else if (name == "Character")	{ Parse_Character(cmd_args); }
	else if (name == "Range")		{ Parse_Range(cmd_args); }

	else							{ throw TextCommand::Unknown(cmd_args); }
}

void UI::Text::Font::ParsingData::Parse_Type(const TextCommandArgs & cmd_args)
{
	if (!(cmd_args.Count() == 1)) { throw TextCommand::InvalidArgumentCount(cmd_args, "n == 1"); }
}

void UI::Text::Font::ParsingData::Parse_Image(const TextCommandArgs & cmd_args)
{
	if (!(cmd_args.Count() == 1)) { throw TextCommand::InvalidArgumentCount(cmd_args, "n == 1"); }

	DirectoryInfo dir(File.Directory());
	FileInfo imgFile(dir.File(cmd_args.ToString(0).c_str()));
	if (imgFile.Exists())
	{
		Image img = imgFile.LoadImage();
		if (!img.Empty())
		{
			Data -> AtlasTexture = img;
		}
	}
}
void UI::Text::Font::ParsingData::Parse_Scale(const TextCommandArgs & cmd_args)
{
	if (!(cmd_args.Count() == 2)) { throw TextCommand::InvalidArgumentCount(cmd_args, "n == 2"); }

	Scale = VectorF2(cmd_args.ToFloat(0), cmd_args.ToFloat(1));
}
void UI::Text::Font::ParsingData::Parse_Character(const TextCommandArgs & cmd_args)
{
	if (!(cmd_args.Count() == 5)) { throw TextCommand::InvalidArgumentCount(cmd_args, "n == 5"); }

	VectorF2 pos(cmd_args.ToFloat(1), cmd_args.ToFloat(2));
	VectorF2 size(cmd_args.ToFloat(3), cmd_args.ToFloat(4));

	if (cmd_args.ToString(0) == "Default")
	{
		Data -> DefaultCharacter.Box.Min = pos / Scale;
		Data -> DefaultCharacter.Box.Max = (pos + size) / Scale;
	}
	else
	{
		Character chr;
		chr.Code = cmd_args.ToUInt32(0);
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

void UI::Text::Font::ParsingData::Parse_Range(const TextCommandArgs & cmd_args)
{
	if (!(cmd_args.Count() == 0 || cmd_args.Count() == 2)) { throw TextCommand::InvalidArgumentCount(cmd_args, "n == 0 || n == 2"); }

	if (cmd_args.Count() == 0)
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
		Range -> CodeMin = cmd_args.ToUInt32(0);
		Range -> CodeMax = cmd_args.ToUInt32(1);
		Data -> CharacterRanges.Insert(Range);
	}
}



UI::Text::Font * UI::Text::Font::Parse(const FileInfo & file)
{
	ParsingData data(file);
	data.Data = new UI::Text::Font();

	TextCommandStream stream(file.LoadText());
	TextCommandArgs cmd_args;
	while (stream.Continue(cmd_args))
	{
		data.Parse(cmd_args);
	}

	data.Data -> Characters.Trim();
	data.Data -> CharacterRanges.Trim();

	return data.Data;
}
