#include "Control/Controls/ScrollBox.hpp"
#include "ValueType/Box/F1.hpp"

// Debug
#include <iostream>
#include <ValueType/_Show.hpp>



float UI::Control::ScrollContent::CalcRatio(float & control_range_size, float & content_size)
{
	// calculating ContentSize and Ratio should be done in Content
	std::cout << "ContentChildren: " << Children.Count() << '\n';

	BoxF1 control_range;
	for (unsigned int i = 0; i < Children.Count(); i++)
	{
		UI::Control::Base & control = *Children[i];

		BoxF1 control_box(control.BoxDisplay.Min.Y, control.BoxDisplay.Max.Y);
		std::cout << "control_box: " << control_box << '\n';

		control_range.Consider(control_box.Min);
		control_range.Consider(control_box.Max);
		//control_range.Consider(control_box); // make this
	}
	control_range_size = control_range.Size();
	std::cout << "ContentControlRange: " << control_range << '\n';
	std::cout << "ContentControlSize:  " << control_range_size << '\n';

	BoxF1 content_range(BoxContent.Min.Y, BoxContent.Max.Y);
	content_size = content_range.Size();

	return content_size / control_range_size;
}



UI::Control::ScrollContent::~ScrollContent()
{ }
UI::Control::ScrollContent::ScrollContent(ScrollBox & box)
	: Base()
	, Box(box)
{ }

void UI::Control::ScrollContent::BoxUpdate()
{
	Base::BoxUpdate();
}

void UI::Control::ScrollContent::AutoAnchorUpdate()
{
	std::cout << "==== AutoAnchorUpdate base\n";
	Base::AutoAnchorUpdate();
	std::cout << "==== AutoAnchorUpdate ....\n";
	Box.ScrollCalc();
	std::cout << "==== AutoAnchorUpdate done\n";
}



UI::Control::ScrollBox::~ScrollBox()
{ }
UI::Control::ScrollBox::ScrollBox()
	: Base()
	, Content(*this)
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
	Content.AutoAnchorYType = Base::EAutoAnchorType::StackMin;

	Base::ChildInsert(Content);
	Base::ChildInsert(ScrollBar);
}



#include "UIManager.hpp"
void UI::Control::ScrollBox::ChildInsert(Base & control)
{
	Content.ChildInsert(control);
	Content.AutoAnchorUpdateRequest();
	//Content.AutoAnchorUpdate();
	if (Window != nullptr)
	{
		Window -> DepthUpdateRequest();
	}
}
void UI::Control::ScrollBox::ChildRemove(Base & control)
{
	Content.ChildRemove(control);
	Content.AutoAnchorUpdateRequest();
	//Content.AutoAnchorUpdate();
	if (Window != nullptr)
	{
		Window -> DepthUpdateRequest();
	}
}
void UI::Control::ScrollBox::ChildClear()
{
	Content.ChildClear();
	//Content.AutoAnchorUpdateRequest();
	Content.AutoAnchorUpdate();
}



void UI::Control::ScrollBox::BoxUpdate()
{
	Base::BoxUpdate();
	//std::cout << "BoxUpdate ....\n";
	//ScrollCalc();
	//std::cout << "BoxUpdate done\n";
}

/*void UI::Control::ScrollBox::AutoAnchorUpdate()
{
	Base::AutoAnchorUpdate();
	std::cout << "AutoAnchorUpdate ....\n";
	ScrollCalc();
	std::cout << "AutoAnchorUpdate done\n";
}*/

/*void UI::Control::ScrollBox::Update()
{
	Base::Update();
	//ScrollBar.Update();
}*/



void UI::Control::ScrollBox::ScrollNone()
{
	ScrollBar.NubSize.Y = (ScrollBar.BoxDisplay.Max.Y - ScrollBar.BoxDisplay.Min.Y) / 2.0f;
	ScrollBar.ValueMin.Y = 0.0f;
	ScrollBar.ValueMax.Y = 1.0f;
	ScrollBar.SetValueY(0.5f);
	ScrollBar.MakeDisabled();
}
void UI::Control::ScrollBox::ScrollCalc()
{
	if (Content.Children.Count() == 0)
	{
		ScrollNone();
		return;
	}

	float control_range_size;
	float content_size;
	float ratio = Content.CalcRatio(control_range_size, content_size);

	if (ratio < 1.0f)
	{
		ScrollBar.NubSize.Y = (ScrollBar.BoxDisplay.Max.Y - ScrollBar.BoxDisplay.Min.Y) * ratio;
		ScrollBar.ValueMin.Y = 0.0f;
		ScrollBar.ValueMax.Y = control_range_size - content_size;
		ScrollBar.MakeEnabled();
	}
	else
	{
		ScrollNone();
	}

	ScrollBar.PutSliderNub();
}
void UI::Control::ScrollBox::ScrollFunc(float val)
{
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
