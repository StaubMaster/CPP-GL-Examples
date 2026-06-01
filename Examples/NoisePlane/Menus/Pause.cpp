#include "Pause.hpp"
#include "ContextNoisePlane.hpp"



PauseMenu::~PauseMenu() { }
PauseMenu::PauseMenu(ContextNoisePlane & context)
	: UI::Control::Form()
	, Context(context)
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

	Continue.ClickFunc.Assign(this, &PauseMenu::ContinueFunc);
	Options.ClickFunc.Assign(this, &PauseMenu::OptionsFunc);
	Debug.ClickFunc.Assign(this, &PauseMenu::DebugFunc);
	Exit.ClickFunc.Assign(this, &PauseMenu::ExitFunc);

	ChildInsert(Continue);
	ChildInsert(Options);
	ChildInsert(Debug);
	ChildInsert(Exit);
}

void PauseMenu::ContinueFunc(ClickArgs args)
{
	if (args.Action != Action::Press) { return; }
	if (!Context.PauseMenu.IsVisible())
	{
		Context.PauseMenu.Show();
	}
	else
	{
		Context.PauseMenu.Hide();
	}
}
void PauseMenu::OptionsFunc(ClickArgs args)
{
	if (args.Action != Action::Press) { return; }
	if (!Context.OptionsMenu.IsVisible())
	{
		Context.OptionsMenu.Show();
	}
	if (Context.PauseMenu.IsVisible())
	{
		Context.PauseMenu.Hide();
	}
}
void PauseMenu::DebugFunc(ClickArgs args)
{
	if (args.Action != Action::Press) { return; }
	if (Context.DebugMenu.IsVisible())
	{
		Context.DebugMenu.Hide();
	}
	else
	{
		Context.DebugMenu.Show();
	}
}
void PauseMenu::ExitFunc(ClickArgs args)
{
	if (args.Action != Action::Press) { return; }
	ContextBase::ChangeToContext0();
}
