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
	//float y = 0.0f;

	//TitleText.Anchor.X.AnchorMarginBoth(0, 0);
	//y = TitleText.Anchor.Y.AnchorMarginMin(y);
	TitleText.Make_Anchor_X_Both(nullptr, nullptr);
	TitleText.Make_Anchor_Y_Min(nullptr);
	TitleText.SetText("User Interface Tests");

	//QuitButton.Anchor.X.AnchorMarginBoth(0, 0);
	//y = QuitButton.Anchor.Y.AnchorMarginMin(y);
	QuitButton.Make_Anchor_X_Both(nullptr, nullptr);
	QuitButton.Make_Anchor_Y_Min(&TitleText);
	QuitButton.SetText("Quit");
	QuitButton.ClickFunc.Assign(this, &TestSelector::QuitFunc);

	//ReButton.Anchor.X.AnchorMarginBoth(0, 0);
	//y = ReButton.Anchor.Y.AnchorMarginMin(y);
	ReButton.Make_Anchor_X_Both(nullptr, nullptr);
	ReButton.Make_Anchor_Y_Min(&QuitButton);
	ReButton.SetText("Re");
	ReButton.ClickFunc.Assign(this, &TestSelector::ReFunc);

	ChildInsert(TitleText);
	ChildInsert(QuitButton);
	ChildInsert(ReButton);



	//TileGridButton.Anchor.X.AnchorMarginBoth(0, 0);
	//y = TileGridButton.Anchor.Y.AnchorMarginMin(y);
	TileGridButton.Make_Anchor_X_Both(nullptr, nullptr);
	TileGridButton.Make_Anchor_Y_Min(&ReButton);
	TileGridButton.SetText("TileGrid");

	//TextButton.Anchor.X.AnchorMarginBoth(0, 0);
	//y = TextButton.Anchor.Y.AnchorMarginMin(y);
	TextButton.Make_Anchor_X_Both(nullptr, nullptr);
	TextButton.Make_Anchor_Y_Min(&TileGridButton);
	TextButton.SetText("Text");

	//GraphButton.Anchor.X.AnchorMarginBoth(0, 0);
	//y = GraphButton.Anchor.Y.AnchorMarginMin(y);
	GraphButton.Make_Anchor_X_Both(nullptr, nullptr);
	GraphButton.Make_Anchor_Y_Min(&TextButton);
	GraphButton.SetText("Graph");

	//TestScrollButton.Anchor.X.AnchorMarginBoth(0, 0);
	//y = TestScrollButton.Anchor.Y.AnchorMarginMin(y);
	TestScrollButton.Make_Anchor_X_Both(nullptr, nullptr);
	TestScrollButton.Make_Anchor_Y_Min(&GraphButton);
	TestScrollButton.SetText("TestScroll");

	//TestListButton.Anchor.X.AnchorMarginBoth(0, 0);
	//y = TestListButton.Anchor.Y.AnchorMarginMin(y);
	TestListButton.Make_Anchor_X_Both(nullptr, nullptr);
	TestListButton.Make_Anchor_Y_Min(&TestScrollButton);
	TestListButton.SetText("TestList");

	//DirectoryNavigatorButton.Anchor.X.AnchorMarginBoth(0, 0);
	//y = DirectoryNavigatorButton.Anchor.Y.AnchorMarginMin(y);
	DirectoryNavigatorButton.Make_Anchor_X_Both(nullptr, nullptr);
	DirectoryNavigatorButton.Make_Anchor_Y_Min(&TestListButton);
	DirectoryNavigatorButton.SetText("DirectoryNavigator");

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
