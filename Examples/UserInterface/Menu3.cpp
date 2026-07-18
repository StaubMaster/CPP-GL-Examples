#include "Menu3.hpp"



UserInterfaceMenu3::~UserInterfaceMenu3() { }
UserInterfaceMenu3::UserInterfaceMenu3()
	: UI::Control::Form()
	, Align()
	, Text()
{
	Align.Anchor.X.AnchorMin(0, 50);
	Align.Anchor.Y.AnchorMin(0, 50);
	Align.NubSize = VectorF2(20.0f);
	Align.ValueMin = VectorF2(0.0f);
	Align.ValueMax = VectorF2(2.0f);
	Align.ValueResolution = VectorF2(1.0f);
	Align.ValueChangedFunc.Assign(this, &UserInterfaceMenu3::AlignFunc);

	Text.Anchor.X.AnchorBoth(Align.Anchor.X.GetMinSize(), 0);
	Text.Anchor.Y.AnchorBoth(0, 0);

	ChildInsert(Align);
	ChildInsert(Text);
}

void UserInterfaceMenu3::AlignFunc(VectorF2 val)
{
	if (val.X == 0.0f) { Text.AlignmentX = UI::Text::Alignment::Min; }
	if (val.X == 1.0f) { Text.AlignmentX = UI::Text::Alignment::Mid; }
	if (val.X == 2.0f) { Text.AlignmentX = UI::Text::Alignment::Max; }

	if (val.Y == 0.0f) { Text.AlignmentY = UI::Text::Alignment::Min; }
	if (val.Y == 1.0f) { Text.AlignmentY = UI::Text::Alignment::Mid; }
	if (val.Y == 2.0f) { Text.AlignmentY = UI::Text::Alignment::Max; }

	Text.PutAlignment();
}
