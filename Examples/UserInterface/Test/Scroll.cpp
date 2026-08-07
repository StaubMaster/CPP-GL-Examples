#include "Test/Scroll.hpp"
#include <sstream>



TestScroll::~TestScroll()
{ }
TestScroll::TestScroll()
	: UI::Control::Form()
	, ScrollBox()
	, Labels(nullptr)
{
	ScrollBox.Anchor.X.AnchorBoth(0, 0);
	ScrollBox.Anchor.Y.AnchorBoth(0, 0);

	ChildInsert(ScrollBox);

	unsigned int n = 12;
	Labels = new UI::Control::Label[n];

	float y = 0.0f;
	for (unsigned int i = 0; i < n; i++)
	{
		Labels[i].Anchor.X.AnchorBoth(0, 0);
		Labels[i].Anchor.Y.AnchorMin(y);
		y = Labels[i].Anchor.Y.GetMinSize();
		// this is like AutoSize FitFixed
		ScrollBox.Content.ChildInsert(Labels[i]);

		std::stringstream ss;
		ss << "idx: " << i;
		Labels[i].SetText(ss.str());
	}
}
