#include "SelectorMenu.hpp"
#include "ContextBase.hpp"



SelectorMenu::~SelectorMenu() { }
SelectorMenu::SelectorMenu()
	: UI::Control::Form()
	, QuitButton()
	, TitleText()
	, SelectorButton()
	, UserInterfaceButton()
	, NoisePlaneButton()
	, Light3D()
{
	QuitButton.Anchor.X.AnchorBoth(0.0f, 0.0f);
	QuitButton.Anchor.Y.AnchorMax(0.0f);
	QuitButton.ClickFunc.Assign(this, &SelectorMenu::QuitFunc);
	QuitButton.SetText("Quit");

	float y = 0.0f;

	TitleText.Anchor.X.AnchorBoth(0.0f, 0.0f);
	TitleText.Anchor.Y.AnchorMin(y);
	TitleText.SetText("This is Context0");
	y = TitleText.Anchor.Y.GetMinSize();

	SelectorButton.Anchor.X.AnchorBoth(0.0f, 0.0f);
	SelectorButton.Anchor.Y.AnchorMin(y);
	SelectorButton.SetText("Selector");
	SelectorButton.ClickFunc.Assign(this, &SelectorMenu::SelectorFunc);
	y = SelectorButton.Anchor.Y.GetMinSize();

	UserInterfaceButton.Anchor.X.AnchorBoth(0.0f, 0.0f);
	UserInterfaceButton.Anchor.Y.AnchorMin(y);
	UserInterfaceButton.SetText("UserInterface");
	UserInterfaceButton.ClickFunc.Assign(this, &SelectorMenu::UserInterfaceFunc);
	y = UserInterfaceButton.Anchor.Y.GetMinSize();

	NoisePlaneButton.Anchor.X.AnchorBoth(0.0f, 0.0f);
	NoisePlaneButton.Anchor.Y.AnchorMin(y);
	NoisePlaneButton.SetText("NoisePlane");
	NoisePlaneButton.ClickFunc.Assign(this, &SelectorMenu::NoisePlaneFunc);
	y = NoisePlaneButton.Anchor.Y.GetMinSize();

	Light3D.Anchor.X.AnchorBoth(0.0f, 0.0f);
	Light3D.Anchor.Y.AnchorMin(y);
	Light3D.SetText("Light3D");
	Light3D.ClickFunc.Assign(this, &SelectorMenu::Light3DFunc);
	y = Light3D.Anchor.Y.GetMinSize();

	TEST_GRAPH.Anchor.X.AnchorBoth(0.0f, 0.0f);
	TEST_GRAPH.Anchor.Y.AnchorBoth(y, QuitButton.Anchor.Y.GetMaxSize());

	ChildInsert(TitleText);
	ChildInsert(QuitButton);
	ChildInsert(SelectorButton);
	ChildInsert(UserInterfaceButton);
	ChildInsert(NoisePlaneButton);
	ChildInsert(Light3D);
	ChildInsert(TEST_GRAPH);
}

#include "Selector/new.hpp"
#include "UserInterface/new.hpp"
#include "NoisePlane/new.hpp"
#include "Light3D/new.hpp"

void SelectorMenu::QuitFunc(ClickArgs args)
{
	if (args.Action == Action::Press)
	{
		ContextBase::Quit();
	}
}
void SelectorMenu::SelectorFunc(ClickArgs args)
{
	if (args.Action == Action::Press)
	{
		ContextBase::Change(newSelectorContext);
	}
}
void SelectorMenu::UserInterfaceFunc(ClickArgs args)
{
	if (args.Action == Action::Press)
	{
		ContextBase::Change(newUserInterfaceContext);
	}
}
void SelectorMenu::NoisePlaneFunc(ClickArgs args)
{
	if (args.Action == Action::Press)
	{
		ContextBase::Change(newContextNoisePlane);
	}
}
void SelectorMenu::Light3DFunc(ClickArgs args)
{
	if (args.Action == Action::Press)
	{
		ContextBase::Change(newLight3D);
	}
}
