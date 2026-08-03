#include "Pause.hpp"
#include "ContextNoisePlane.hpp"



PauseMenu::~PauseMenu() { }
PauseMenu::PauseMenu(ContextNoisePlane & context)
	: UI::Control::Form()
	, Context(context)
{
	// Why make this transparent ?
	// So you can see what is happening.
	// Forms are now movable, just move this or options out of the way if you want to see.
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
	if (!Context.MenuPause.IsVisible())
	{
		Context.MenuPause.Show();
	}
	else
	{
		Context.MenuPause.Hide();
	}
}
void PauseMenu::OptionsFunc(ClickArgs args)
{
	if (args.Action != Action::Press) { return; }
	if (!Context.MenuOptions.IsVisible())
	{
		Context.MenuOptions.Show();
	}
	if (Context.MenuPause.IsVisible())
	{
		Context.MenuPause.Hide();
	}
}
void PauseMenu::DebugFunc(ClickArgs args)
{
	if (args.Action != Action::Press) { return; }
	if (Context.MenuDebug.IsVisible())
	{
		Context.MenuDebug.Hide();
	}
	else
	{
		Context.MenuDebug.Show();
	}
}

//#include "Selector/new.hpp"
void PauseMenu::ExitFunc(ClickArgs args)
{
	if (args.Action == Action::Press)
	{
		//ContextBase::Change(newSelectorContext);
		ContextBase::Quit();
	}
}
