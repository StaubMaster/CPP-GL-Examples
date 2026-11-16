#include "UI/ListForm.hpp"



ListForm::~ListForm()
{ }
ListForm::ListForm()
	: UI::Control_::Form()
	, List()
{
	//List.Anchor.X.AnchorBoth(0, 0);
	//List.Anchor.Y.AnchorBoth(0, 0);
	List.Make_Anchor_X_Both(nullptr, nullptr);
	List.Make_Anchor_Y_Both(nullptr, nullptr);
	List.ItemFunc.Assign(this, &ListForm::ItemFunc);
	ChildInsert(List);
}



void ListForm::ItemFunc(const UI::Control_::ListBox::Item & item)
{
	Object = item.Object;
	Hide();
}
