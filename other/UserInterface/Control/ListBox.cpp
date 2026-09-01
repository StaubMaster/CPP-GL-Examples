#include "ListBox.hpp"



UI::Control::ListBox::Item::~Item()
{ }

UI::Control::ListBox::Item::Item(UI::Control::ListBox & listBox, unsigned int idx, const char * name, void * obj)
	: BaseText()
	, ListBox(listBox)
	, Index(idx)
	, Object(obj)
{
	Anchor.X.Anchor = AnchorType::Min;
	Anchor.Y.Anchor = AnchorType::Min;
	AnchorSize = VectorF2(75, 25);



//	ColorDefault = ColorF4(0.125f * 5, 0.125f * 5, 0.125f * 5);
//	ColorHover   = ColorF4(0.125f * 4, 0.125f * 4, 0.125f * 4);

	ColorDefault = ColorF4(0.125f * 6, 0.125f * 6, 0.125f * 6);
	ColorHover   = ColorF4(0.125f * 5, 0.125f * 5, 0.125f * 5);
//	ColorHover   = ColorF4(0.125f * 4, 0.125f * 4, 0.125f * 8);



//	AnchorMargin = BoxF2(VectorF2(0.0f), VectorF2(0.0f));
	Anchor.X.AnchorBoth(0, 0);

	SetText(name);
}

void UI::Control::ListBox::Item::RelayClick(ClickArgs args)
{
	ListBox.ItemClickFunc(args, *this);
}





UI::Control::ListBox::~ListBox()
{
	for (unsigned int i = 0; i < Items.Count(); i++)
	{
		delete Items[i];
	}
}
UI::Control::ListBox::ListBox()
	: UI::Control::ScrollBox()
{ }



void UI::Control::ListBox::ItemsClear()
{
	ChildClear();
	for (unsigned int i = 0; i < Items.Count(); i++)
	{
		delete Items[i];
	}
	Items.Clear();
	ClickedObject = nullptr;

	CalcScroll();
}
void UI::Control::ListBox::ItemNew(const char * name, void * obj)
{
	Item * item = new Item(*this, Items.Count(), name, obj);
	Items.Insert(item);
	ChildInsert(*item);

	CalcScroll();
}



void UI::Control::ListBox::ItemClickFunc(ClickArgs args, const Item & item)
{
	if (args.Action == Action::Press)
	{
		ClickedObject = item.Object;
		ItemFunc.TryInvoke(item);
	}
}
