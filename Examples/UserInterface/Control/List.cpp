#include "Control/List.hpp"



UI::Control::List::Item::Item(UI::Control::List & list, const char * name, void * obj)
	: BaseText()
	, List(list)
	, Object(obj)
{
	Depth = 0.1f;
	Anchor.X.Anchor = AnchorType::Min;
	Anchor.Y.Anchor = AnchorType::Min;
	AnchorSize = VectorF2(75, 25);

	ColorDefault = ColorF4(0.625f, 0.625f, 0.625f);
	ColorHover = ColorF4(0.5f, 0.5f, 0.5f);



//	AnchorMargin = BoxF2(VectorF2(0.0f), VectorF2(0.0f));
	Anchor.X.AnchorBoth(0, 0);

	SetText(name);
}

void UI::Control::List::Item::RelayClick(ClickArgs args)
{
	List.ClickFunc(args, Object);
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
}
void UI::Control::List::ItemNew(const char * name, void * obj)
{
	Item * item = new Item(*this, name, obj);
	Items.Insert(item);
	Content.ChildInsert(item);
}
void UI::Control::List::ClickFunc(ClickArgs args, void * obj)
{
	if (args.Action == Action::Press)
	{
		ClickedObject = obj;
		ItemClickFunc.TryInvoke(obj);
	}
}
