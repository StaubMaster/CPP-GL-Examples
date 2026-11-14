#include "Test/Scroll.hpp"
#include <sstream>



TestScroll::~TestScroll()
{
	delete[] Labels;
}
TestScroll::TestScroll()
	: UI::Control::Form()
	, ScrollBox()
	, Labels(nullptr)
{
	//ScrollBox.Anchor.X.AnchorMarginBoth(0, 0);
	//ScrollBox.Anchor.Y.AnchorMarginBoth(0, 0);
	ScrollBox.Make_Anchor_X_Both(nullptr, nullptr);
	ScrollBox.Make_Anchor_Y_Both(nullptr, nullptr);

	ChildInsert(ScrollBox);

	unsigned int n = 12;
	Labels = new UI::Control::Label[n];

	//float y = 0.0f;
	UI::Control::Base * control = nullptr;
	for (unsigned int i = 0; i < n; i++)
	{
		//Labels[i].Anchor.X.AnchorMarginBoth(0, 0);
		//y = Labels[i].Anchor.Y.AnchorMarginMin(y);
		Labels[i].Make_Anchor_X_Both(nullptr, nullptr);
		Labels[i].Make_Anchor_Y_Min(control);
		// this is like AutoSize FitFixed
		ScrollBox.ChildInsert(Labels[i]);

		std::stringstream ss;
		ss << "idx: " << i;
		Labels[i].SetText(ss.str());

		control = &Labels[i];
	}
}
