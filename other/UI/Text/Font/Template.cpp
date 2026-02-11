#include "UI/Text/Font/Template.hpp"



UI::Text::Font::Template::Template(Font & referance) :
	Referance(referance)
{ }
UI::Text::Font::Template::~Template()
{ }



void UI::Text::Font::Template::Done()
{
	Referance.Characters.Trim();
}



void UI::Text::Font::Template::Change_Scale(Point2D scale)
{
	Scale = scale;
}
void UI::Text::Font::Template::Insert_Image(Image img)
{
	if (!Referance.AtlasTexture.Empty())
	{
		Referance.AtlasTexture.Dispose();
	}
	Referance.AtlasTexture.Bind(img);
}
void UI::Text::Font::Template::Change_DefaultCharacter(Point2D pos, Point2D size)
{
	Referance.DefaultCharacter.Box.Min = (pos / Scale);
	Referance.DefaultCharacter.Box.Max = (pos + size) / Scale;
}
void UI::Text::Font::Template::Insert_Character(unsigned int code, Point2D pos, Point2D size)
{
	Character chr;
	chr.Code = code;
	chr.Box.Min = (pos / Scale);
	chr.Box.Max = (pos + size) / Scale;
	Referance.Characters.Insert(chr);
}
