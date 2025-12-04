#include "Text.hpp"



UI::Control::Text::Text(Manager & manager) : Base(manager)
{
	Layer = 0.1f;
	Anchor.X.Anchor = ANCHOR_MIN;
	Anchor.Y.Anchor = ANCHOR_MIN;
	PixelMinDist = Point2D(12, 12);
	PixelSize = Point2D(120, 60);
	PixelMaxDist = Point2D(12, 12);
	NormalCenter = Point2D(0, 0);
	ColorDefault = Color(1.0f, 1.0f, 1.0f);
	ColorHover = Color(0.875f, 0.875f, 0.875f);
}
UI::Control::Text::~Text()
{ }





std::string UI::Control::Text::GetText() const
{
	return String;
}
void UI::Control::Text::SetText(std::string str)
{
	String = str;
	Changed = true;
}



void UI::Control::Text::UpdateTextString()
{
	if (Changed)
	{
		Point2D min = PixelBox.Min;
		Point2D max = PixelBox.Max;
		Point2D center = (max + min) / 2;
		for (unsigned int i = 0; i < TextEntry.Length(); i++)
		{
			if (i < String.length())
			{
				TextEntry[i].Pallet = UI::Text::Manager::CharToTextCoord(String[i]);
			}
			else
			{
				TextEntry[i].Pallet = UI::Text::Manager::CharToTextCoord('\0');
			}
		}
		Changed = false;
	}
}

void UI::Control::Text::UpdateTextPos()
{
	Point2D min = PixelBox.Min;
	Point2D max = PixelBox.Max;
	Point2D center = (max + min) / 2;
	for (unsigned int i = 0; i < TextEntry.Length(); i++)
	{
		TextEntry[i].Pos = Point2D((min.X + 25) + (i * 50), center.Y);
	}
}
