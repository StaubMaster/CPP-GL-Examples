#include "Pause.hpp"



PauseMenu::~PauseMenu() { }
PauseMenu::PauseMenu()
	: UI::Control::Form()
{
	MakeTransparent();

	float y;

	y = 0.0f;

	Continue.Anchor.X.AnchorBoth(0.0f, 0.0f);
	Continue.Anchor.Y.AnchorMin(y);
	Continue.SetText("Continue");
	y = Continue.Anchor.Y.GetMinSize();

	Options.Anchor.X.AnchorBoth(0.0f, 0.0f);
	Options.Anchor.Y.AnchorMin(y);
	Options.SetText("Options");
	y = Options.Anchor.Y.GetMinSize();

	y = 0.0f;

	Exit.Anchor.X.AnchorBoth(0.0f, 0.0f);
	Exit.Anchor.Y.AnchorMax(0);
	Exit.SetText("Exit");
	y = Exit.Anchor.Y.GetMaxSize();

	Debug.Anchor.X.AnchorBoth(0.0f, 0.0f);
	Debug.Anchor.Y.AnchorMax(y);
	Debug.SetText("Debug");
	y = Debug.Anchor.Y.GetMaxSize();

	ChildInsert(Continue);
	ChildInsert(Options);
	ChildInsert(Debug);
	ChildInsert(Exit);
}
