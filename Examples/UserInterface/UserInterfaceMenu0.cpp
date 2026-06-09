#include "UserInterfaceMenu0.hpp"
#include "General/ContextBase.hpp"



Context1Menu::~Context1Menu() { }
Context1Menu::Context1Menu()
	: UI::Control::Form()
	, QuitButton()
	, TitleText()
	, Context0Button()
	, Context1Button()
	, Text()
	, SliderGroupBox()
	, SliderHori()
	, SliderVert()
	, SliderArea()
	, CheckGroupBox()
	, Check0()
	, Check1()
	, Check2()
	, Check3()
{
	//float x = 0.0f;
	float y = 0.0f;

	TitleText.Anchor.X.AnchorBoth(0, 0);
	TitleText.Anchor.Y.AnchorMin(y);
	TitleText.SetText("This is Context1");
	y = TitleText.Anchor.Y.GetMinSize();

	Context0Button.Anchor.X.AnchorMin(0, 200);
	Context0Button.Anchor.Y.AnchorMin(y);
	Context0Button.SetText("Context0");
	//x = Context0Button.Anchor.X.GetMinSize();
	y = Context0Button.Anchor.Y.GetMinSize();
	Context0Button.ClickFunc.Assign(this, &Context1Menu::Context0Func);

	Context1Button.Anchor.X.AnchorMin(0, 200);
	Context1Button.Anchor.Y.AnchorMin(y);
	Context1Button.SetText("Context1");
	//x = Context1Button.Anchor.X.GetMinSize();
	y = Context1Button.Anchor.Y.GetMinSize();
	Context1Button.ClickFunc.Assign(this, &Context1Menu::Context1Func);

	Text.Anchor.X.AnchorMin(0, 200);
	Text.Anchor.Y.AnchorMin(y, 100);
	Text.SetText("some Text\n123");

	SliderGroupBox.Anchor.X.AnchorBoth(200, 0);
	SliderGroupBox.Anchor.Y.AnchorMin(TitleText.Anchor.Y.GetMinSize(), 200);
	SliderHori.Anchor.Y.AnchorMin(0, 25);
	SliderVert.Anchor.X.AnchorMin(0, 25);
	SliderHori.Anchor.X.AnchorBoth(SliderVert.Anchor.X.GetMinSize(), 0);
	SliderVert.Anchor.Y.AnchorBoth(SliderHori.Anchor.Y.GetMinSize(), 0);
	SliderArea.Anchor.X.AnchorBoth(SliderVert.Anchor.X.GetMinSize(), 0);
	SliderArea.Anchor.Y.AnchorBoth(SliderHori.Anchor.Y.GetMinSize(), 0);
	SliderHori.NubSize = VectorF2(10, 25);
	SliderVert.NubSize = VectorF2(25, 10);
	SliderArea.NubSize = VectorF2(10, 10);
	SliderHori.ValueChangedFunc.Assign(this, &Context1Menu::SliderHoriChange);
	SliderVert.ValueChangedFunc.Assign(this, &Context1Menu::SliderVertChange);
	SliderArea.ValueChangedFunc.Assign(this, &Context1Menu::SliderAreaChange);

	CheckGroupBox.Anchor.X.AnchorMax(0, 80);
	CheckGroupBox.Anchor.Y.AnchorMax(0, 80);
	Check0.Anchor.X.AnchorMin(0);
	Check0.Anchor.Y.AnchorMin(0);
	Check1.Anchor.X.AnchorMax(0);
	Check1.Anchor.Y.AnchorMin(0);
	Check2.Anchor.X.AnchorMin(0);
	Check2.Anchor.Y.AnchorMax(0);
	Check3.Anchor.X.AnchorMax(0);
	Check3.Anchor.Y.AnchorMax(0);

	QuitButton.Anchor.X.AnchorBoth(0, 100);
	QuitButton.Anchor.Y.AnchorMax(0);
	QuitButton.SetText("Quit");
	QuitButton.ClickFunc.Assign(this, &Context1Menu::QuitFunc);



	ChildInsert(TitleText);
	ChildInsert(Context0Button);
	ChildInsert(Context1Button);
	ChildInsert(Text);
	ChildInsert(SliderGroupBox);
	SliderGroupBox.ChildInsert(SliderHori);
	SliderGroupBox.ChildInsert(SliderVert);
	SliderGroupBox.ChildInsert(SliderArea);
	ChildInsert(CheckGroupBox);
	CheckGroupBox.ChildInsert(Check0);
	CheckGroupBox.ChildInsert(Check1);
	CheckGroupBox.ChildInsert(Check2);
	CheckGroupBox.ChildInsert(Check3);
	ChildInsert(QuitButton);
}

#include "Selector/new.hpp"
#include "UserInterface/new.hpp"

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
		ContextBase::Change(newContext0);
	}
}
void Context1Menu::Context1Func(ClickArgs args)
{
	if (args.Action == Action::Press)
	{
		ContextBase::Change(newContext1);
	}
}

#include <iostream>
#include "ValueType/_Show.hpp"
void Context1Menu::SliderHoriChange(VectorF2 val) { std::cout << "Hori: " << val << '\n'; }
void Context1Menu::SliderVertChange(VectorF2 val) { std::cout << "Vert: " << val << '\n'; }
void Context1Menu::SliderAreaChange(VectorF2 val) { std::cout << "Area: " << val << '\n'; }
