#include "Context0Menu.hpp"
#include "ContextBase.hpp"



Context0Menu::~Context0Menu() { }
Context0Menu::Context0Menu()
	: UI::Control::Form()
	, TitleText()
	, QuitButton()
	, Context0Button()
	, Context1Button()
	, ContextNoisePlaneButton()
	, ContextTestTextAlignmentButton()
{
	QuitButton.Anchor.X.AnchorBoth(0.0f, 0.0f);
	QuitButton.Anchor.Y.AnchorMax(0.0f);
	QuitButton.ClickFunc.Assign(this, &Context0Menu::QuitFunc);
	QuitButton.SetText("Quit");

	float y = 0.0f;

	TitleText.Anchor.X.AnchorBoth(0.0f, 0.0f);
	TitleText.Anchor.Y.AnchorMin(y);
	TitleText.SetText("This is Context0");
	y = TitleText.Anchor.Y.GetMinSize();

	Context0Button.Anchor.X.AnchorBoth(0.0f, 0.0f);
	Context0Button.Anchor.Y.AnchorMin(y);
	Context0Button.SetText("Context0");
	Context0Button.ClickFunc.Assign(this, &Context0Menu::Context0Func);
	y = Context0Button.Anchor.Y.GetMinSize();

	Context1Button.Anchor.X.AnchorBoth(0.0f, 0.0f);
	Context1Button.Anchor.Y.AnchorMin(y);
	Context1Button.SetText("Context1");
	Context1Button.ClickFunc.Assign(this, &Context0Menu::Context1Func);
	y = Context1Button.Anchor.Y.GetMinSize();

	ContextNoisePlaneButton.Anchor.X.AnchorBoth(0.0f, 0.0f);
	ContextNoisePlaneButton.Anchor.Y.AnchorMin(y);
	ContextNoisePlaneButton.SetText("NoisePlane");
	ContextNoisePlaneButton.ClickFunc.Assign(this, &Context0Menu::ContextNoisePlaneFunc);
	y = ContextNoisePlaneButton.Anchor.Y.GetMinSize();

	ContextTestTextAlignmentButton.Anchor.X.AnchorBoth(0.0f, 0.0f);
	ContextTestTextAlignmentButton.Anchor.Y.AnchorMin(y);
	ContextTestTextAlignmentButton.SetText("TestTextAlignment");
	ContextTestTextAlignmentButton.ClickFunc.Assign(this, &Context0Menu::ContextTestTextAlignmentFunc);
	y = ContextTestTextAlignmentButton.Anchor.Y.GetMinSize();

	ChildInsert(TitleText);
	ChildInsert(QuitButton);
	ChildInsert(Context0Button);
	ChildInsert(Context1Button);
	ChildInsert(ContextNoisePlaneButton);
	ChildInsert(ContextTestTextAlignmentButton);
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
void Context0Menu::ContextTestTextAlignmentFunc(ClickArgs args)
{
	if (args.Action == Action::Press)
	{
		ContextBase::ChangeToTestTextAlignment();
	}
}
