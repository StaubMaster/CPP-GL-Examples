#include "UserInterfaceMenu0.hpp"
#include "General/ContextBase.hpp"



UserInterfaceMenu0::~UserInterfaceMenu0() { }
UserInterfaceMenu0::UserInterfaceMenu0()
	: UI::Control::Form()
	, TitleText()
	, QuitButton()
	, ReButton()
	, BackButton()
{
	//float x = 0.0f;
	float y = 0.0f;

	TitleText.Anchor.X.AnchorBoth(0, 0);
	TitleText.Anchor.Y.AnchorMin(y);
	TitleText.SetText("User Interface Example");
	y = TitleText.Anchor.Y.GetMinSize();

	QuitButton.Anchor.X.AnchorBoth(0, 0);
	QuitButton.Anchor.Y.AnchorMin(y);
	QuitButton.SetText("Quit");
	QuitButton.ClickFunc.Assign(this, &UserInterfaceMenu0::QuitFunc);
	y = QuitButton.Anchor.Y.GetMinSize();

	ReButton.Anchor.X.AnchorBoth(0, 0);
	ReButton.Anchor.Y.AnchorMin(y);
	ReButton.SetText("Re");
	ReButton.ClickFunc.Assign(this, &UserInterfaceMenu0::ReFunc);
	y = ReButton.Anchor.Y.GetMinSize();

	BackButton.Anchor.X.AnchorBoth(0, 0);
	BackButton.Anchor.Y.AnchorMin(y);
	BackButton.SetText("Back");
	BackButton.ClickFunc.Assign(this, &UserInterfaceMenu0::BackFunc);
	y = BackButton.Anchor.Y.GetMinSize();

	Menu1Button.Anchor.X.AnchorBoth(0, 0);
	Menu1Button.Anchor.Y.AnchorMin(y);
	Menu1Button.SetText("Menu1");
	y = Menu1Button.Anchor.Y.GetMinSize();

	Menu2Button.Anchor.X.AnchorBoth(0, 0);
	Menu2Button.Anchor.Y.AnchorMin(y);
	Menu2Button.SetText("Menu2");
	y = Menu2Button.Anchor.Y.GetMinSize();

	Menu3Button.Anchor.X.AnchorBoth(0, 0);
	Menu3Button.Anchor.Y.AnchorMin(y);
	Menu3Button.SetText("Menu3");
	y = Menu3Button.Anchor.Y.GetMinSize();



	ChildInsert(TitleText);
	ChildInsert(QuitButton);
	ChildInsert(ReButton);
	ChildInsert(BackButton);

	ChildInsert(Menu1Button);
	ChildInsert(Menu2Button);
	ChildInsert(Menu3Button);
}

#include "Selector/new.hpp"
#include "UserInterface/new.hpp"

void UserInterfaceMenu0::QuitFunc(ClickArgs args)
{
	if (args.Action == Action::Press)
	{
		ContextBase::Quit();
	}
}
void UserInterfaceMenu0::ReFunc(ClickArgs args)
{
	if (args.Action == Action::Press)
	{
		ContextBase::Change(newUserInterfaceContext);
	}
}
void UserInterfaceMenu0::BackFunc(ClickArgs args)
{
	if (args.Action == Action::Press)
	{
		ContextBase::Change(newContext0);
	}
}

//#include <iostream>
//#include "ValueType/_Show.hpp"
//void UserInterfaceMenu0::SliderHoriChange(VectorF2 val) { std::cout << "Hori: " << val << '\n'; }
//void UserInterfaceMenu0::SliderVertChange(VectorF2 val) { std::cout << "Vert: " << val << '\n'; }
//void UserInterfaceMenu0::SliderAreaChange(VectorF2 val) { std::cout << "Area: " << val << '\n'; }
