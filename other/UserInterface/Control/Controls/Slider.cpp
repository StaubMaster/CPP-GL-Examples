#include "Control/Controls/Slider.hpp"
#include "Control/General/Manager.hpp"

#include "User/MouseArgs.hpp"

#include "Text/Manager.hpp"
#include <math.h>



void UI::Control::Slider::ClampValue()
{
	if (Value.X < ValueRange.Min.X) { Value.X = ValueRange.Min.X; }
	if (Value.X > ValueRange.Max.X) { Value.X = ValueRange.Max.X; }
	if (Value.Y < ValueRange.Min.Y) { Value.Y = ValueRange.Min.Y; }
	if (Value.Y > ValueRange.Max.Y) { Value.Y = ValueRange.Max.Y; }
}

VectorF2 UI::Control::Slider::GetValue() const { return Value; }
float UI::Control::Slider::GetValueX() const { return Value.X; }
float UI::Control::Slider::GetValueY() const { return Value.Y; }

void UI::Control::Slider::SetValue(VectorF2 val)
{
	Value = val;
	ClampValue();
	NubUpdateRequest();
	ValueXChangedFunc.TryInvoke(Value.X);
	ValueYChangedFunc.TryInvoke(Value.Y);
	ValueChangedFunc.TryInvoke(Value);
}
void UI::Control::Slider::SetValueX(float val)
{
	Value.X = val;
	ClampValue();
	NubUpdateRequest();
	ValueXChangedFunc.TryInvoke(Value.X);
}
void UI::Control::Slider::SetValueY(float val)
{
	Value.Y = val;
	ClampValue();
	NubUpdateRequest();
	ValueYChangedFunc.TryInvoke(Value.Y);
}

void UI::Control::Slider::ChangeValue(DisplayPosition mouse_pos)
{
	if (!IsInteractible()) { return; }

	VectorF2 slider_size_half = NubSize / 2.0f;
	BoxF2 slider_range(
		BoxDisplay().Min + slider_size_half,
		BoxDisplay().Max - slider_size_half
	);

	VectorF2 slider_value = mouse_pos.Buffer.Corner;
	slider_value -= slider_range.Min;
	slider_value /= slider_range.Size();

	slider_value *= ValueRange.Size();
	slider_value += ValueRange.Min;

	slider_value /= ValueResolution;
	slider_value = slider_value.round(); // Vector.round that takes Vector Size
	slider_value *= ValueResolution;

	Value = slider_value;
	ClampValue();
	NubUpdateRequest();

	ValueXChangedFunc.TryInvoke(Value.X);
	ValueYChangedFunc.TryInvoke(Value.Y);
	ValueChangedFunc.TryInvoke(Value);
}



void UI::Control::Slider::NubUpdateRequest()
{
	NubUpdateRequested = true;
}
void UI::Control::Slider::NubUpdate()
{
	VectorF2 slider_size_half = NubSize / 2.0f;
	BoxF2 slider_range(
		BoxDisplay().Min + slider_size_half,
		BoxDisplay().Max - slider_size_half
	);

	VectorF2 slider_normal = Value;
	slider_normal -= ValueRange.Min;
	slider_normal /= ValueRange.Size();

	VectorF2 slider_value = slider_normal;
	slider_value *= slider_range.Size();
	slider_value += slider_range.Min;

	NubBox.Min = slider_value - slider_size_half;
	NubBox.Max = slider_value + slider_size_half;

	NubUpdateRequested = false;
}



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
	ValueRange.Min = VectorF2(0.0f, 0.0f);
	ValueRange.Max = VectorF2(1.0f, 1.0f);
}



void UI::Control::Slider::AnchorUpdate()
{
	BaseText::AnchorUpdate();
	NubUpdateRequest();
}

void UI::Control::Slider::Update()
{
	BaseText::Update();
	if (NubUpdateRequested) { NubUpdate(); }
	TextObjectData.Depth = Depth(2.0f / 3.0f);
}

#include "UIManager.hpp"
void UI::Control::Slider::DisplayPut() const
{
	BaseText::DisplayPut();
	if (_Manager() != nullptr && Parent)
	{
		if (NubObject_Display)
		{
			Inst::Data data;
			data.Layer = Depth(1.0f / 3.0f);
			data.Box = NubBox;
			data.Color = ColorF4(0.5f, 0.5f, 0.5f);
			data.Bound = Parent -> BoxBoarder(); // Bound should be this.BoxDisplay ?
			_Manager() -> ControlManager.InstancePut(data);
		}
	}
}
void UI::Control::Slider::DisplayShow()
{
	BaseText::DisplayShow();
	if (!NubObject_Display)
	{
		NubObject_Display = true;
	}
}
void UI::Control::Slider::DisplayHide()
{
	BaseText::DisplayHide();
	if (NubObject_Display)
	{
		NubObject_Display = false;
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
		NubUpdateRequest();
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
// Scroll
