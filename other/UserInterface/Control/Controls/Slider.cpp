#include "Control/Controls/Slider.hpp"
#include "Control/General/Manager.hpp"

#include "User/MouseArgs.hpp"

#include "Text/Manager.hpp"
#include <math.h>



UI::Control::Slider::Slider()
	: BaseText()
{
	Anchor.X.Anchor = AnchorType::Min;
	Anchor.Y.Anchor = AnchorType::Min;
	AnchorSize = VectorF2(75, 10);

	float padding = 0;
	AnchorPadding = BoxF2(VectorF2(padding, padding), VectorF2(padding, padding));

	ColorDefault = ColorF4(0.375f, 0.375f, 0.375f);
	ColorHover = ColorF4(0.25f, 0.25f, 0.25f);

	NubSize = VectorF2(10, 25);

	Value = VectorF2(0.0f, 0.0f);
	ValueResolution = VectorF2(0.01f, 0.01f);
	ValueMin = VectorF2(0.0f, 0.0f);
	ValueMax = VectorF2(1.0f, 1.0f);
}
UI::Control::Slider::~Slider()
{ }



VectorF2 UI::Control::Slider::GetValue() const { return Value; }
float UI::Control::Slider::GetValueX() const { return Value.X; }
float UI::Control::Slider::GetValueY() const { return Value.Y; }

void UI::Control::Slider::SetValue(VectorF2 val)
{
	Value = val;
	ClampValue();
	PutSliderNub();
	ValueXChangedFunc.TryInvoke(Value.X);
	ValueYChangedFunc.TryInvoke(Value.Y);
	ValueChangedFunc.TryInvoke(Value);
}
void UI::Control::Slider::SetValueX(float val)
{
	Value.X = val;
	ClampValue();
	PutSliderNub();
	ValueXChangedFunc.TryInvoke(Value.X);
}
void UI::Control::Slider::SetValueY(float val)
{
	Value.Y = val;
	ClampValue();
	PutSliderNub();
	ValueYChangedFunc.TryInvoke(Value.Y);
}

void UI::Control::Slider::PutSliderNub()
{
	if (SliderObject.Is())
	{
		VectorF2 slider_size_half = NubSize / 2.0f;
		VectorF2 slider_min = BoxDisplay.Min + slider_size_half;
		VectorF2 slider_max = BoxDisplay.Max - slider_size_half;

		VectorF2 slider_normal = Value;
		slider_normal -= ValueMin;
		slider_normal /= (ValueMax - ValueMin);

		VectorF2 slider_value = slider_normal;
		slider_value *= (slider_max - slider_min);
		slider_value += slider_min;

		SliderObject.Box().Min = slider_value - slider_size_half;
		SliderObject.Box().Max = slider_value + slider_size_half;

		//SliderObject.Bound() = Object.Bound();
		//SliderObject.Bound() = ObjectData.Bound;
		if (Parent != nullptr)
		{
			SliderObject.Bound() = Parent -> BoxBoarder;
		}
		else
		{
			SliderObject.Bound() = BoxF2();
		}
	}
}
void UI::Control::Slider::ClampValue()
{
	if (Value.X < ValueMin.X) { Value.X = ValueMin.X; }
	if (Value.X > ValueMax.X) { Value.X = ValueMax.X; }
	if (Value.Y < ValueMin.Y) { Value.Y = ValueMin.Y; }
	if (Value.Y > ValueMax.Y) { Value.Y = ValueMax.Y; }
}

void UI::Control::Slider::ChangeValue(DisplayPosition mouse_pos)
{
	if (!IsInteractible()) { return; }

	VectorF2 slider_size_half = NubSize / 2.0f;
	VectorF2 slider_pos_min = BoxDisplay.Min + slider_size_half;
	VectorF2 slider_pos_max = BoxDisplay.Max - slider_size_half;

	VectorF2 slider_value = mouse_pos.Buffer.Corner;
	slider_value -= slider_pos_min;
	slider_value /= (slider_pos_max - slider_pos_min);
	slider_value *= (ValueMax - ValueMin);
	slider_value += ValueMin;

	slider_value /= ValueResolution;
	slider_value = slider_value.round(); // Vector.round that takes Vector Size
	slider_value *= ValueResolution;

	Value = slider_value;
	ClampValue();
	PutSliderNub();

	ValueXChangedFunc.TryInvoke(Value.X);
	ValueYChangedFunc.TryInvoke(Value.Y);
	ValueChangedFunc.TryInvoke(Value);
}



#include "Control/Window.hpp"
#include "Control/Form.hpp"
void UI::Control::Slider::AssignDepth()
{
	BaseText::AssignDepth();

	if (Window == nullptr) { return; }
	if (Form == nullptr) { return; }

	float size = Window -> DepthSize;
	float offset = Form -> DepthOffset;
	float layer = Layer;

	if (SliderObject.Is())
	{
		SliderObject.Depth() = -(((layer + (1.0f / 3.0f)) * size) + offset);
	}
	if (TextObject.Is())
	{
		TextObject.Depth() = -(((layer + (2.0f / 3.0f)) * size) + offset);
	}
}



void UI::Control::Slider::BoxUpdate()
{
	BaseText::BoxUpdate();
	PutSliderNub();
}
void UI::Control::Slider::DisplayShow()
{
	BaseText::DisplayShow();
	if (!SliderObject.Is() && Manager != NULL)
	{
		SliderObject.Create();
		SliderObject.Color() = ColorF4(0.5f, 0.5f, 0.5f);
		SliderObject.Depth() = Depth - 0.0005f;
		PutSliderNub();
	}
}
void UI::Control::Slider::DisplayHide()
{
	BaseText::DisplayHide();
	if (SliderObject.Is() || Manager == NULL)
	{
		SliderObject.Delete();
	}
}



void UI::Control::Slider::RelayClick(ClickArgs args)
{
	if (args.Action == Action::Press)
	{
		ChangeValue(args.Position);
	}
}
void UI::Control::Slider::RelayDrag(DragArgs args)
{
	ChangeValue(args.Position);
}
void UI::Control::Slider::RelayKey(KeyArgs args)
{
	if (args.Action == Action::Press || args.Action == Action::Repeat)
	{
		if (args.Key == Keys::Left)		{ Value.X -= ValueResolution.X; }
		if (args.Key == Keys::Right)	{ Value.X += ValueResolution.X; }
		if (args.Key == Keys::Up)		{ Value.Y -= ValueResolution.Y; }
		if (args.Key == Keys::Down)		{ Value.Y += ValueResolution.Y; }
		ClampValue();
		PutSliderNub();
		if (args.Key == Keys::Left || args.Key == Keys::Right)
		{
			ValueXChangedFunc.TryInvoke(Value.X);
		}
		if (args.Key == Keys::Up || args.Key == Keys::Down)
		{
			ValueYChangedFunc.TryInvoke(Value.Y);
		}
		ValueChangedFunc.TryInvoke(Value);
	}
}
