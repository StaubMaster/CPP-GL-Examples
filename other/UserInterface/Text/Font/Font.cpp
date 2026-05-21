#include "Text/Font/Font.hpp"



UI::Text::Font::Character::Character()
	: Code(0)
	, Box(VectorF2(0, 0), VectorF2(1, 1))
{ }



const UI::Text::Font::Character & UI::Text::Font::operator[](unsigned int code) const
{
	for (unsigned int j = 0; j < CharacterRanges.Count(); j++)
	{
		CharacterRange * range = CharacterRanges[j];
		if (code >= range -> CodeMin && code <= range -> CodeMax)
		{
			return range -> Characters[code - (range -> CodeMin)];
		}
	}

	for (unsigned int i = 0; i < Characters.Count(); i++)
	{
		if (Characters[i].Code == code)
		{
			return Characters[i];
		}
	}

	return DefaultCharacter;
}
unsigned int UI::Text::Font::FindCodeIndex(unsigned int code) const
{
	unsigned int idx = 0;

	for (unsigned int j = 0; j < CharacterRanges.Count(); j++)
	{
		CharacterRange * range = CharacterRanges[j];
		if (code >= range -> CodeMin && code <= range -> CodeMax)
		{
			return idx + (code - range -> CodeMin);
		}
		idx += CharacterRanges[j] -> Characters.Count();
	}

	for (unsigned int i = 0; i < Characters.Count(); i++)
	{
		if (Characters[i].Code == code)
		{
			return idx;
		}
		idx++;
	}

	return idx;
}





UI::Text::Font::Font() :
	AtlasTexture()
{ }
UI::Text::Font::~Font()
{
	AtlasTexture.Dispose();
}
