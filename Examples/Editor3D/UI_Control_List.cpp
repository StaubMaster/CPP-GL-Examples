#include "UI_Control_List.hpp"



UI::Control::List::Item::Item(UI::Control::List & list, const char * name, void * obj)
	: UI::Control::Button()
	, List(list)
	, Object(obj)
{
	AnchorMargin = BoxF2(VectorF2(0.0f), VectorF2(0.0f));
	Anchor.X.AnchorBoth(0, 0);
	SetText(name);
	ClickFunc.Assign(this, &UI::Control::List::Item::Func);
}
void UI::Control::List::Item::Func(ClickArgs args)
{
	List.Func(args, Object);
}



UI::Control::List::List()
	: UI::Control::Form()
{
	AnchorPadding = BoxF2(VectorF2(0.0f), VectorF2(0.0f));
}
void UI::Control::List::Clear()
{
	Children.Clear();
	for (unsigned int i = 0; i < Items.Count(); i++)
	{
		delete Items[i];
	}
	Items.Clear();
	Object = nullptr;
}
void UI::Control::List::Func(ClickArgs args, void * obj)
{
	if (args.Action == Action::Press)
	{
		Object = obj;
		Hide();
	}
}
