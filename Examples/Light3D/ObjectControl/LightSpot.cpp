#include "ObjectControl/LightSpot.hpp"



UI::Control::LightSpot::~LightSpot()
{ }
UI::Control::LightSpot::LightSpot()
	: GroupBox()
	, Base()
	, Pos()
	, Dir()
	, Object(nullptr)
{
	Base.Anchor.X.AnchorBoth(0, 0);
	Pos.Anchor.X.AnchorBoth(0, 0);
	Dir.Anchor.X.AnchorBoth(0, 0);

	Base.Anchor.Y.AnchorMin(0);
	Pos.Anchor.Y.AnchorMin(Base.Anchor.Y.GetMinSize());
	Dir.Anchor.Y.AnchorMin(Pos.Anchor.Y.GetMinSize());

	Anchor.X.AnchorBoth(0, 0);
	Anchor.Y.AnchorMin(0, Dir.Anchor.Y.GetMinSize() + Dir.AnchorMargin.Max.Y + AnchorBoarder.Max.Y + AnchorPadding.Max.Y);

	ChildInsert(Base);
	ChildInsert(Pos);
	ChildInsert(Dir);
}



void UI::Control::LightSpot::Change(::LightSpot * obj)
{
	Object = obj;
	if (Object != nullptr)
	{
		Base.Change(&(Object -> Base));
		Pos.Change(&(Object -> Pos));
		Dir.Change(&(Object -> Dir));
	}
	else
	{
		Base.Change(nullptr);
		Pos.Change(nullptr);
		Dir.Change(nullptr);
	}
}
