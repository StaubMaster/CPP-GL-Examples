#include "Context0Menu.hpp"
#include "ContextBase.hpp"



Context0Menu::~Context0Menu() { }
Context0Menu::Context0Menu()
	: UI::Control::Form()
	, TitleText()
	, QuitText()
	, QuitButton()
	, Context0Text()
	, Context0Button()
	, Context1Text()
	, Context1Button()
	, ContextNoisePlaneText()
	, ContextNoisePlaneButton()
{
	float x = 0.0f;
	float y = 0.0f;

	QuitText.Anchor.X.AnchorMin(0.0f, 200);
	QuitText.Anchor.Y.AnchorMax(0.0f);
	QuitText.SetText("Quit");
	x = QuitText.Anchor.X.GetMinSize();
	QuitButton.Anchor.X.AnchorMin(x);
	QuitButton.Anchor.Y.AnchorMax(0.0f);
	QuitButton.ClickFunc.Assign(this, &Context0Menu::QuitFunc);

	TitleText.Anchor.X.AnchorBoth(0, 0);
	TitleText.Anchor.Y.AnchorMin(y);
	TitleText.SetText("This is Context0");
	y = TitleText.Anchor.Y.GetMinSize();

	Context0Text.Anchor.X.AnchorMin(0.0f, 200);
	Context0Text.Anchor.Y.AnchorMin(y);
	x = Context0Text.Anchor.X.GetMinSize();
	Context0Text.SetText("Context0");
	Context0Button.Anchor.X.AnchorMin(x);
	Context0Button.Anchor.Y.AnchorMin(y);
	Context0Button.ClickFunc.Assign(this, &Context0Menu::Context0Func);
	y = Context0Text.Anchor.Y.GetMinSize();

	Context1Text.Anchor.X.AnchorMin(0.0f, 200);
	Context1Text.Anchor.Y.AnchorMin(y);
	x = Context1Text.Anchor.X.GetMinSize();
	Context1Text.SetText("Context1");
	Context1Button.Anchor.X.AnchorMin(x);
	Context1Button.Anchor.Y.AnchorMin(y);
	Context1Button.ClickFunc.Assign(this, &Context0Menu::Context1Func);
	y = Context1Text.Anchor.Y.GetMinSize();

	ContextNoisePlaneText.Anchor.X.AnchorMin(0.0f, 200);
	ContextNoisePlaneText.Anchor.Y.AnchorMin(y);
	x = ContextNoisePlaneText.Anchor.X.GetMinSize();
	ContextNoisePlaneText.SetText("NoisePlane");
	ContextNoisePlaneButton.Anchor.X.AnchorMin(x);
	ContextNoisePlaneButton.Anchor.Y.AnchorMin(y);
	ContextNoisePlaneButton.ClickFunc.Assign(this, &Context0Menu::ContextNoisePlaneFunc);
	y = ContextNoisePlaneText.Anchor.Y.GetMinSize();

	ChildInsert(TitleText);
	ChildInsert(QuitText);
	ChildInsert(QuitButton);
	ChildInsert(Context0Text);
	ChildInsert(Context0Button);
	ChildInsert(Context1Text);
	ChildInsert(Context1Button);
	ChildInsert(ContextNoisePlaneText);
	ChildInsert(ContextNoisePlaneButton);
}

void Context0Menu::QuitFunc(ClickArgs args)
{
	if (args.Action == Action::Press)
	{
		ContextBase::Quit();
	}
}
void Context0Menu::Context0Func(ClickArgs args)
{
	if (args.Action == Action::Press)
	{
		ContextBase::ChangeToContext0();
	}
}
void Context0Menu::Context1Func(ClickArgs args)
{
	if (args.Action == Action::Press)
	{
		ContextBase::ChangeToContext1();
	}
}
void Context0Menu::ContextNoisePlaneFunc(ClickArgs args)
{
	if (args.Action == Action::Press)
	{
		ContextBase::ChangeToNoisePlane();
	}
}
