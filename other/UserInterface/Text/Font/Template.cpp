#include "Text/Font/Template.hpp"



UI::Text::Font::Template::Template(Font & referance) :
	Referance(referance)
{ }
UI::Text::Font::Template::~Template()
{ }



void UI::Text::Font::Template::Done()
{
	Referance.Characters.Trim();
}



void UI::Text::Font::Template::Change_Scale(VectorF2 scale)
{
	Scale = scale;
}
void UI::Text::Font::Template::Insert_Image(Image img)
{
	Referance.AtlasTexture = img;
}
void UI::Text::Font::Template::Change_DefaultCharacter(VectorF2 pos, VectorF2 size)
{
	Referance.DefaultCharacter.Box.Min = (pos / Scale);
	Referance.DefaultCharacter.Box.Max = (pos + size) / Scale;
}
void UI::Text::Font::Template::Insert_Character(unsigned int code, VectorF2 pos, VectorF2 size)
{
	Character chr;
	chr.Code = code;
	chr.Box.Min = (pos / Scale);
	chr.Box.Max = (pos + size) / Scale;
	Referance.Characters.Insert(chr);
}
