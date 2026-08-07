#include "Test/List.hpp"

#include <sstream>
#include <iostream>



TestList::~TestList()
{ }
TestList::TestList()
	: UI::Control::Form()
	, List()
{
	List.Anchor.X.AnchorBoth(0, 0);
	List.Anchor.Y.AnchorBoth(0, 0);
//	List.ItemClickFunc.Assign(this, &TestList::ItemFunc);

	ChildInsert(List);

	List.ItemNew("item0", (void*)"Item 0");
	List.ItemNew("item1", (void*)"Item 1");
	List.ItemNew("item2", (void*)"Item 2");
	List.ItemNew("item3", (void*)"Item 3");
	List.ItemNew("item4", (void*)"Item 4");
	List.ItemNew("item5", (void*)"Item 5");
	List.ItemNew("item6", (void*)"Item 6");
	List.ItemNew("item7", (void*)"Item 7");

	List.Content.AutoSizerYType = Base::EAutoSizerType::StackMin;
	List.Content.UpdateAutoSize();
}

void TestList::ItemFunc(void * obj)
{
	std::cout << "Item: " << (const char *)obj << '\n';
}
