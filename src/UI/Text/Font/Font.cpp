#include "UI/Text/Font/Font.hpp"



UI::Text::Font::Character::Character() :
	Code(0),
	Box(Point2D(0, 0), Point2D(1, 1))
{ }



UI::Text::Font::Font()
{
	AtlasTexture = NULL;
}
UI::Text::Font::~Font()
{
	delete AtlasTexture;
}



AxisBox2D UI::Text::Font::CharacterBoxFromCode(unsigned int code)
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
