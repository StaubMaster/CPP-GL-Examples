#include "Main.hpp"



MainMenu::~MainMenu() { }
MainMenu::MainMenu()
	: UI::Control::Form()
{
	MakeTransparent();

	float y;
	y = 0.0f;

	ButtonPlay.Anchor.X.AnchorMin(0);
	ButtonPlay.Anchor.Y.AnchorMin(y);
	ChildInsert(ButtonPlay);

	y = ButtonPlay.Anchor.Y.GetMinSize();

	ButtonTerminate.Anchor.X.AnchorMin(0);
	ButtonTerminate.Anchor.Y.AnchorMin(y);
	ChildInsert(ButtonTerminate);
}
