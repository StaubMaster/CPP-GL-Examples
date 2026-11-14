#include "Test/List.hpp"
#include <sstream>
#include <iostream>



TestList::~TestList()
{ }
TestList::TestList()
	: UI::Control::Form()
	, List()
	, ButtonClear()
	, ButtonNew()
{
	//float y = 0.0f;
	//float x = 0.0f;

	//x = ButtonClear.Anchor.X.AnchorMarginMin(x, 120);
	//ButtonClear.Anchor.Y.AnchorMarginMax(y);
	ButtonClear.Make_Anchor_X_Min(nullptr, 120);
	ButtonClear.Make_Anchor_Y_Max(nullptr);
	ButtonClear.SetText("Clear");
	ButtonClear.ClickFunc.Assign(this, &TestList::ItemClear);
	ChildInsert(ButtonClear);

	//ButtonNew.Anchor.X.AnchorMarginMin(x, 80);
	//y = ButtonNew.Anchor.Y.AnchorMarginMax(y);
	ButtonNew.Make_Anchor_X_Min(&ButtonClear, 80);
	ButtonNew.Make_Anchor_Y_Max(nullptr);
	ButtonNew.SetText("New");
	ButtonNew.ClickFunc.Assign(this, &TestList::ItemNew);
	ChildInsert(ButtonNew);

	//List.Anchor.X.AnchorMarginBoth(0, 0);
	//List.Anchor.Y.AnchorMarginBoth(0, y);
	List.Make_Anchor_X_Both(nullptr, nullptr);
	List.Make_Anchor_Y_Both(nullptr, &ButtonNew);
	List.ItemFunc.Assign(this, &TestList::ItemFunc);
	ChildInsert(List);

	List.ItemsClear();
	List.ItemNew("item0", (void*)"Object of Item 0");
	List.ItemNew("item1", (void*)"Object of Item 1");
	List.ItemNew("item2", (void*)"Object of Item 2");
	List.ItemNew("item3", (void*)"Object of Item 3");
	List.ItemNew("item4", (void*)"Object of Item 4");
	List.ItemNew("item5", (void*)"Object of Item 5");
	List.ItemNew("item6", (void*)"Object of Item 6");
	List.ItemNew("item7", (void*)"Object of Item 7");
}



void TestList::ItemFunc(const UI::Control::ListBox::Item & item)
{
	std::cout << "Item: " << '[' << item.Index << ']' << ' ' << '"' << (const char *)item.Object << '"' << '\n';
}



#include "User/MouseArgs.hpp"
void TestList::ItemNew(ClickArgs args)
{
	if (args.Action == Action::Press)
	{
		List.ItemNew("new item", (void*)"New Item");
	}
}

void TestList::ItemClear(ClickArgs args)
{
	if (args.Action == Action::Press)
	{
		List.ItemsClear();
	}
}
