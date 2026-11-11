#include "Test/Selector.hpp"
#include "ContextBase.hpp"



TestSelector::TestSelector()
	: UI::Control::Form()
	, TitleText()
	, QuitButton()
	, ReButton()
	, TileGridButton()
	, TextButton()
	, GraphButton()
	, TestScrollButton()
	, TestListButton()
	, DirectoryNavigatorButton()
{
	//float x = 0.0f;
	float y = 0.0f;

	TitleText.Anchor.X.AnchorBoth(0, 0);
	TitleText.Anchor.Y.AnchorMin(y);
	TitleText.SetText("User Interface Tests");
	y = TitleText.Anchor.Y.GetMinSize();

	QuitButton.Anchor.X.AnchorBoth(0, 0);
	QuitButton.Anchor.Y.AnchorMin(y);
	QuitButton.SetText("Quit");
	QuitButton.ClickFunc.Assign(this, &TestSelector::QuitFunc);
	y = QuitButton.Anchor.Y.GetMinSize();

	ReButton.Anchor.X.AnchorBoth(0, 0);
	ReButton.Anchor.Y.AnchorMin(y);
	ReButton.SetText("Re");
	ReButton.ClickFunc.Assign(this, &TestSelector::ReFunc);
	y = ReButton.Anchor.Y.GetMinSize();

	ChildInsert(TitleText);
	ChildInsert(QuitButton);
	ChildInsert(ReButton);



	TileGridButton.Anchor.X.AnchorBoth(0, 0);
	TileGridButton.Anchor.Y.AnchorMin(y);
	TileGridButton.SetText("TileGrid");
	y = TileGridButton.Anchor.Y.GetMinSize();

	TextButton.Anchor.X.AnchorBoth(0, 0);
	TextButton.Anchor.Y.AnchorMin(y);
	TextButton.SetText("Text");
	y = TextButton.Anchor.Y.GetMinSize();

	GraphButton.Anchor.X.AnchorBoth(0, 0);
	GraphButton.Anchor.Y.AnchorMin(y);
	GraphButton.SetText("Graph");
	y = GraphButton.Anchor.Y.GetMinSize();

	TestScrollButton.Anchor.X.AnchorBoth(0, 0);
	TestScrollButton.Anchor.Y.AnchorMin(y);
	TestScrollButton.SetText("TestScroll");
	y = TestScrollButton.Anchor.Y.GetMinSize();

	TestListButton.Anchor.X.AnchorBoth(0, 0);
	TestListButton.Anchor.Y.AnchorMin(y);
	TestListButton.SetText("TestList");
	y = TestListButton.Anchor.Y.GetMinSize();

	DirectoryNavigatorButton.Anchor.X.AnchorBoth(0, 0);
	DirectoryNavigatorButton.Anchor.Y.AnchorMin(y);
	DirectoryNavigatorButton.SetText("DirectoryNavigator");
	y = DirectoryNavigatorButton.Anchor.Y.GetMinSize();

	ChildInsert(TileGridButton);
	ChildInsert(TextButton);
	ChildInsert(GraphButton);
	ChildInsert(TestScrollButton);
	ChildInsert(TestListButton);
	ChildInsert(DirectoryNavigatorButton);

	//AutoAnchorYType = EAutoAnchorType::StackMinFit;
	AutoAnchorYType = EAutoAnchorType::StackMin;
}

#include "new.hpp"

void TestSelector::QuitFunc(ClickArgs args)
{
	if (args.Action == Action::Press)
	{
		ContextBase::Quit();
	}
}
void TestSelector::ReFunc(ClickArgs args)
{
	if (args.Action == Action::Press)
	{
		ContextBase::Change(newUserInterfaceContext);
	}
}
