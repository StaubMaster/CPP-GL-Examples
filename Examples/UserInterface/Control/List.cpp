#include "List.hpp"



UI::Control::List::Item::~Item()
{ }

UI::Control::List::Item::Item(UI::Control::List & list, unsigned int idx, const char * name, void * obj)
	: BaseText()
	, List(list)
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

void UI::Control::List::Item::RelayClick(ClickArgs args)
{
	List.ItemClickFunc(args, *this);
}



UI::Control::List::~List()
{
	for (unsigned int i = 0; i < Items.Count(); i++)
	{
		delete Items[i];
	}
}
UI::Control::List::List()
	: UI::Control::ScrollBox()
{ }



void UI::Control::List::ItemsClear()
{
	Content.Children.Clear();
	for (unsigned int i = 0; i < Items.Count(); i++)
	{
		delete Items[i];
	}
	Items.Clear();
	ClickedObject = nullptr;

	Content.UpdateAutoAnchor();
	CalcScroll();
}
void UI::Control::List::ItemNew(const char * name, void * obj)
{
	Item * item = new Item(*this, Items.Count(), name, obj);
	Items.Insert(item);
	Content.ChildInsert(item);

	Content.UpdateAutoAnchor();
	item -> BoxUpdate();
	CalcScroll();
}



void UI::Control::List::ItemClickFunc(ClickArgs args, const Item & item)
{
	if (args.Action == Action::Press)
	{
		ClickedObject = item.Object;
		ItemFunc.TryInvoke(item);
	}
}
