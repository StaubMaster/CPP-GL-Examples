#include "ScrollBox.hpp"
#include "ValueType/Box/F1.hpp"



UI::Control::ScrollBox::~ScrollBox()
{ }
UI::Control::ScrollBox::ScrollBox()
	: Base()
	, Content()
	, ScrollBar()
{
	ColorDefault = ColorF4(0.75f, 0.75f, 0.75f);
	ColorHover = ColorF4(0.75f, 0.75f, 0.75f);

	Content.ColorDefault = ColorF4(0.75f, 0.75f, 0.75f);
	Content.ColorHover = ColorF4(0.75f, 0.75f, 0.75f);

	ScrollBar.Anchor.X.AnchorMax(0, 25);
	ScrollBar.Anchor.Y.AnchorBoth(0, 0);
	ScrollBar.ValueMin.Y = 0.0f;
	ScrollBar.ValueMax.Y = 1.0f;
	ScrollBar.NubSize.X = 25.0f;
	ScrollBar.NubSize.Y = 100.0f;
	ScrollBar.ValueYChangedFunc.Assign(this, &ScrollBox::ScrollFunc);

	Content.Anchor.X.AnchorBoth(0, ScrollBar.Anchor.X.GetMaxSize());
	Content.Anchor.Y.AnchorBoth(0, 0); // Content Y is not determined by Anchor ?

	ChildInsert(Content);
	ChildInsert(ScrollBar);
}

void UI::Control::ScrollBox::BoxUpdate()
{
	Base::BoxUpdate();
	CalcScroll();
}

void UI::Control::ScrollBox::CalcScroll()
{
	if (Content.Children.Count() == 0)
	{
		ScrollBar.NubSize.Y = (ScrollBar.BoxDisplay.Max.Y - ScrollBar.BoxDisplay.Min.Y) / 2.0f;
		ScrollBar.ValueMin.Y = 0.0f;
		ScrollBar.ValueMax.Y = 1.0f;
		ScrollBar.SetValueY(0.5f);
		ScrollBar.MakeDisabled();
		return;
	}

	BoxF1 content_range;
	for (unsigned int i = 0; i < Content.Children.Count(); i++)
	{
		UI::Control::Base & control = *Content.Children[i];
		content_range.Consider(control.BoxDisplay.Min.Y);
		content_range.Consider(control.BoxDisplay.Max.Y);
	}
	ContentSize = content_range.Size();

	float size = Content.BoxContent.Max.Y - Content.BoxContent.Min.Y;
	float ratio = size / ContentSize;

	if (ratio < 1.0f)
	{
		ScrollBar.NubSize.Y = (ScrollBar.BoxDisplay.Max.Y - ScrollBar.BoxDisplay.Min.Y) * ratio;
		ScrollBar.ValueMin.Y = 0.0f;
		ScrollBar.ValueMax.Y = ContentSize - size;
		ScrollBar.MakeEnabled();
	}
	else
	{
		ScrollBar.NubSize.Y = (ScrollBar.BoxDisplay.Max.Y - ScrollBar.BoxDisplay.Min.Y) / 2.0f;
		ScrollBar.ValueMin.Y = 0.0f;
		ScrollBar.ValueMax.Y = 1.0f;
		ScrollBar.SetValueY(0.5f);
		ScrollBar.MakeDisabled();
	}

	ScrollBar.PutSliderNub();
}
void UI::Control::ScrollBox::ScrollFunc(float val)
{
	// child Bound dosnt update properly ?

	Content.AnchorPadding.Min.Y = 5.0f - val;
	Content.AnchorPadding.Max.Y = 5.0f + val;
	Content.BoxUpdateRequest();
}

void UI::Control::ScrollBox::RelayScroll(ScrollArgs args)
{
	if (ScrollBar.IsEnabled())
	{
		float val = ScrollBar.GetValueY();
		val -= args.Y * 5;
		ScrollBar.SetValueY(val);
	}
}
