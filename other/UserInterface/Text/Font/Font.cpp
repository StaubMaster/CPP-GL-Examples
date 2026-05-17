#include "Text/Font/Font.hpp"



UI::Text::Font::Character::Character()
	: Code(0)
	, Box(VectorF2(0, 0), VectorF2(1, 1))
{ }



UI::Text::Font::Font() :
	AtlasTexture()
{ }
UI::Text::Font::~Font()
{
	AtlasTexture.Dispose();
}



BoxF2 UI::Text::Font::CharacterBoxFromCode(unsigned int code)
{
	for (unsigned int j = 0; j < CharacterRanges.Count(); j++)
	{
		CharacterRange * range = CharacterRanges[j];
		if (code >= range -> CodeMin && code <= range -> CodeMax)
		{
			return range -> Characters[code - (range -> CodeMin)].Box;
		}
	}

	for (unsigned int i = 0; i < Characters.Count(); i++)
	{
		if (Characters[i].Code == code)
		{
			return Characters[i].Box;
		}
	}

	return DefaultCharacter.Box;
}
