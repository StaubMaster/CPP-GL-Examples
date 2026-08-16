#include "UI/ListForm.hpp"



ListForm::~ListForm()
{ }
ListForm::ListForm()
	: UI::Control::Form()
	, List()
{
	List.Anchor.X.AnchorBoth(0, 0);
	List.Anchor.Y.AnchorBoth(0, 0);
	List.ItemFunc.Assign(this, &ListForm::ItemFunc);
	ChildInsert(List);
}



void ListForm::ItemFunc(const UI::Control::ListBox::Item & item)
{
	Object = item.Object;
	Hide();
}
