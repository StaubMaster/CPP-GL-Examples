#include "Text/Font/Font.hpp"



UI::Text::Font::Character::Character() :
	Code(0),
	Box(VectorF2(0, 0), VectorF2(1, 1))
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
	for (unsigned int i = 0; i < Characters.Count(); i++)
	{
		if (Characters[i].Code == code)
		{ return Characters[i].Box; }
	}
	return DefaultCharacter.Box;
}



/*Template * Font::ToTemplate()
{

}*/
