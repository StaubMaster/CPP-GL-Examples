#include "Slider.hpp"
#include "Base/Manager.hpp"
#include "UserParameter/MouseInclude.hpp"



UI::Control::Slider::Slider() : Base()
{
	Layer = 0.1f;
	Anchor.X.Anchor = AnchorType::Min;
	Anchor.Y.Anchor = AnchorType::Min;
	AnchorSize = Point2D(75, 25);
	ColorDefault = ColorF4(0.375f, 0.375f, 0.375f);
	ColorHover = ColorF4(0.25f, 0.25f, 0.25f);

	SliderChanged = true;
	SliderSize = 10.0f;

	Value = 0.0f;
	ValueResolution = 0.01f;
	ValueMin = 0.0f;
	ValueMax = 1.0f;

	ValueChangedFunc = NULL;
}
UI::Control::Slider::~Slider()
{ }



float UI::Control::Slider::GetValue()
{
	return Value;
}
void UI::Control::Slider::SetValue(float val)
{
	Value = val;
	SliderChanged = true;
	ValueChangedFunc(Value);
}
void UI::Control::Slider::ChangeValue(UserParameter::Mouse::Position mouse_pos)
{
	if (!_Interactible) { return; }

	float slider_size_half = SliderSize / 2;
	float slider_pos_min = AnchorBox.Min.X + slider_size_half;
	float slider_pos_max = AnchorBox.Max.X - slider_size_half;

	float slider_value = mouse_pos.Absolute.X;
	slider_value -= slider_pos_min;
	slider_value /= (slider_pos_max - slider_pos_min);
	slider_value *= (ValueMax - ValueMin);
	slider_value += ValueMin;

	slider_value /= ValueResolution;
	slider_value = (int)slider_value;
	slider_value *= ValueResolution;

	if (slider_value < ValueMin) { slider_value = ValueMin; }
	if (slider_value > ValueMax) { slider_value = ValueMax; }

	Value = slider_value;
	SliderChanged = true;

	ValueChangedFunc(Value);
}


void UI::Control::Slider::UpdateEntrysRelay()
{
	if (SliderEntry.Is())
	{
		if (SliderChanged)
		{
			(*SliderEntry).Min.Y = AnchorBox.Min.Y;
			(*SliderEntry).Max.Y = AnchorBox.Max.Y;

			float slider_size_half = SliderSize / 2;
			float slider_min = AnchorBox.Min.X + slider_size_half;
			float slider_max = AnchorBox.Max.X - slider_size_half;

			float slider_normal = (Value - ValueMin) / (ValueMax - ValueMin);
			float slider_value = (slider_normal * (slider_max - slider_min)) + slider_min;
			
			(*SliderEntry).Min.X = slider_value - slider_size_half;
			(*SliderEntry).Max.X = slider_value + slider_size_half;
			
			SliderChanged = false;
		}
	}
}
void UI::Control::Slider::InsertDrawingEntryRelay()
{
	if (!SliderEntry.Is() && ControlManager != NULL)
	{
		SliderEntry.Allocate(ControlManager -> Inst_Data_Container, 1);
		(*SliderEntry).Col = ColorF4(0.5f, 0.5f, 0.5f);
		(*SliderEntry).Layer = Layer - 0.01f;
		SliderChanged = true;
	}
}
void UI::Control::Slider::RemoveDrawingEntryRelay()
{
	if (SliderEntry.Is() || ControlManager == NULL)
	{
		SliderEntry.Dispose();
	}
}
void UI::Control::Slider::UpdateBoxRelay()
{
	SliderChanged = true;
}



void UI::Control::Slider::RelayClick(UserParameter::Mouse::Click params)
{
	if (params.Action.IsPress())
	{
		ChangeValue(params.Position);
	}
}
void UI::Control::Slider::RelayCursorDrag(UserParameter::Mouse::Drag params)
{
	ChangeValue(params.Position);
}
