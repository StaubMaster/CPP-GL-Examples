#include "Test/Text.hpp"



TestText::TestText()
	: UI::Control::Form()
	, Align()
	, Text()
{
	//float x;

	//x = Align.Anchor.X.AnchorMarginMin(0, 50);
	//Align.Anchor.Y.AnchorMarginMin(0, 50);
	Align.Make_Anchor_X_Min(nullptr, 50);
	Align.Make_Anchor_Y_Min(nullptr, 50);
	Align.NubSize = VectorF2(20.0f);
	Align.ValueRange.Min = VectorF2(0.0f);
	Align.ValueRange.Max = VectorF2(2.0f);
	Align.ValueResolution = VectorF2(1.0f);
	Align.ValueChangedFunc.Assign(this, &TestText::AlignFunc);

	//Text.Anchor.X.AnchorMarginBoth(x, 0);
	//Text.Anchor.Y.AnchorMarginBoth(0, 0);
	Text.Make_Anchor_X_Both(&Align, nullptr);
	Text.Make_Anchor_Y_Both(nullptr, nullptr);

	ChildInsert(Align);
	ChildInsert(Text);
}

void TestText::AlignFunc(VectorF2 val)
{
	if (val.X == 0.0f) { Text.AlignmentChangeX(UI::Text::Alignment::Min); }
	if (val.X == 1.0f) { Text.AlignmentChangeX(UI::Text::Alignment::Mid); }
	if (val.X == 2.0f) { Text.AlignmentChangeX(UI::Text::Alignment::Max); }

	if (val.Y == 0.0f) { Text.AlignmentChangeY(UI::Text::Alignment::Min); }
	if (val.Y == 1.0f) { Text.AlignmentChangeY(UI::Text::Alignment::Mid); }
	if (val.Y == 2.0f) { Text.AlignmentChangeY(UI::Text::Alignment::Max); }
}
