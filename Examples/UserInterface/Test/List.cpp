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
	float y = 0.0f;
	float x = 0.0f;

	ButtonClear.Anchor.X.AnchorMin(x, 120);
	ButtonClear.Anchor.Y.AnchorMax(y);
	x = ButtonClear.Anchor.X.GetMinSize();
	ButtonClear.SetText("Clear");
	ButtonClear.ClickFunc.Assign(this, &TestList::ItemClear);
	ChildInsert(ButtonClear);

	ButtonNew.Anchor.X.AnchorMin(x, 80);
	ButtonNew.Anchor.Y.AnchorMax(y);
	y = ButtonNew.Anchor.Y.GetMaxSize();
	ButtonNew.SetText("New");
	ButtonNew.ClickFunc.Assign(this, &TestList::ItemNew);
	ChildInsert(ButtonNew);

	List.Anchor.X.AnchorBoth(0, 0);
	List.Anchor.Y.AnchorBoth(0, y);
	List.Content.AutoAnchorYType = Base::EAutoAnchorType::StackMin;
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



void TestList::ItemFunc(const UI::Control::List::Item & item)
{
	std::cout << "Item: " << '[' << item.Index << ']' << ' ' << '"' << (const char *)item.Object << '"' << '\n';
}



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
