#include "Context1Menu.hpp"
#include "ContextBase.hpp"



Context1Menu::~Context1Menu() { }
Context1Menu::Context1Menu()
	: UI::Control::Form()
	, TitleText()
	, QuitText()
	, QuitButton()
	, Context0Text()
	, Context0Button()
	, Context1Text()
	, Context1Button()
{
	float x = 0.0f;
	float y = 0.0f;

	QuitText.Anchor.X.AnchorMin(0.0f, 200);
	QuitText.Anchor.Y.AnchorMax(0.0f);
	QuitText.SetText("Quit");
	x = QuitText.Anchor.X.GetMinSize();
	QuitButton.Anchor.X.AnchorMin(x);
	QuitButton.Anchor.Y.AnchorMax(0.0f);
	QuitButton.ClickFunc.Assign(this, &Context1Menu::QuitFunc);

	TitleText.Anchor.X.AnchorBoth(0, 0);
	TitleText.Anchor.Y.AnchorMin(y);
	TitleText.SetText("This is Context1");
	y = TitleText.Anchor.Y.GetMinSize();

	Context0Text.Anchor.X.AnchorMin(0, 200);
	Context0Text.Anchor.Y.AnchorMin(y);
	x = Context0Text.Anchor.X.GetMinSize();
	Context0Text.SetText("Context0");
	Context0Button.Anchor.X.AnchorMin(x);
	Context0Button.Anchor.Y.AnchorMin(y);
	Context0Button.ClickFunc.Assign(this, &Context1Menu::Context0Func);
	y = Context0Text.Anchor.Y.GetMinSize();

	Context1Text.Anchor.X.AnchorMin(0, 200);
	Context1Text.Anchor.Y.AnchorMin(y);
	x = Context1Text.Anchor.X.GetMinSize();
	Context1Text.SetText("Context1");
	Context1Button.Anchor.X.AnchorMin(x);
	Context1Button.Anchor.Y.AnchorMin(y);
	Context1Button.ClickFunc.Assign(this, &Context1Menu::Context1Func);
	y = Context1Text.Anchor.Y.GetMinSize();

	ChildInsert(TitleText);
	ChildInsert(QuitText);
	ChildInsert(QuitButton);
	ChildInsert(Context0Text);
	ChildInsert(Context0Button);
	ChildInsert(Context1Text);
	ChildInsert(Context1Button);
}

void Context1Menu::QuitFunc(ClickArgs args)
{
	if (args.Action == Action::Press)
	{
		ContextBase::Quit();
	}
}
void Context1Menu::Context0Func(ClickArgs args)
{
	if (args.Action == Action::Press)
	{
		ContextBase::ChangeToContext0();
	}
}
void Context1Menu::Context1Func(ClickArgs args)
{
	if (args.Action == Action::Press)
	{
		ContextBase::ChangeToContext1();
	}
}
