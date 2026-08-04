#include "TestScroll.hpp"



ScrollBox::~ScrollBox()
{ }
ScrollBox::ScrollBox()
	: UI::Control::Base()
	, ScrollBar()
{
	Depth = 0.8f;
	ColorDefault = ColorF4(0.75f, 0.75f, 0.75f);
	ColorHover = ColorF4(0.75f, 0.75f, 0.75f);

	ScrollBar.Anchor.X.AnchorMax(0, 25);
	ScrollBar.Anchor.Y.AnchorBoth(0, 0);
	ScrollBar.ValueMin.Y = 0.0f;
	ScrollBar.ValueMax.Y = 1.0f;
	ScrollBar.NubSize.X = 25.0f;
	ScrollBar.NubSize.Y = 100.0f;
	ScrollBar.ValueYChangedFunc.Assign(this, &ScrollBox::ScrollFunc);

	ChildInsert(ScrollBar);
}

void ScrollBox::RelayUpdateBox()
{
	CalcScroll();
}

#include <iostream>
void ScrollBox::CalcScroll()
{
	float range = 0.0f;
	for (unsigned int i = 0; i < Children.Count(); i++)
	{
		if (Children[i] == &ScrollBar) { continue; }
		UI::Control::Base & control = *Children[i];
		if (range < control.DisplayBox.Max.Y)
		{
			range = control.DisplayBox.Max.Y;
		}
	}
	range -= ContainerBox.Min.Y;

	// nub size to slider size ratio
	// should be same as content size to area size
	float size = ContainerBox.Max.Y - ContainerBox.Min.Y;

	float ratio = size / range;
	std::cout << "size : " << size << '\n';
	std::cout << "range: " << range << '\n';
	std::cout << "ratio: " << ratio << '\n';
	if (ratio > 1.0f)
	{
		// deactivate Scroll
		ratio = 1.0f;
	}

	ScrollBar.NubSize.Y = (ScrollBar.DisplayBox.Max.Y - ScrollBar.DisplayBox.Min.Y) * ratio;
	ScrollBar.PutSliderNub();
}
void ScrollBox::ScrollFunc(float val)
{
	(void)val;
}





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
		Labels[i].Anchor.X.AnchorBoth(0, 25);
		Labels[i].Anchor.Y.AnchorMin(y);
		y = Labels[i].Anchor.Y.GetMinSize();
		ScrollBox.ChildInsert(Labels[i]);

		std::stringstream ss;
		ss << "idx: " << i;
		Labels[i].SetText(ss.str());
	}

	ScrollBox.CalcScroll();
}
