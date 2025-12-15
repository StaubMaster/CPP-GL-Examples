#include "Slider.hpp"
#include "Base/Manager.hpp"



UI::Control::Slider::Slider() : Base()
{
	Layer = 0.1f;
	Anchor.X.Anchor = ANCHOR_MIN;
	Anchor.Y.Anchor = ANCHOR_MIN;
	AnchorSize = Point2D(75, 25);
	ColorDefault = Color(0.375f, 0.375f, 0.375f);
	ColorHover = Color(0.25f, 0.25f, 0.25f);

	SliderChanged = true;
	SliderSize = 10.0f;

	SliderValue = 0.0f;
	SliderMin = 0.0f;
	SliderMax = 1.0f;

	ValueChangedFunc = NULL;
}
UI::Control::Slider::~Slider()
{ }



float UI::Control::Slider::GetValue()
{
	return SliderValue;
}
void UI::Control::Slider::SetValue(float val)
{
	SliderValue = val;
	SliderChanged = true;
	if (ValueChangedFunc != NULL) { ValueChangedFunc(SliderValue); }
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

			float slider_normal = (SliderValue - SliderMin) / (SliderMax - SliderMin);
			float slider_value = (slider_normal * (slider_max - slider_min)) + slider_min;
			
			(*SliderEntry).Min.X = slider_value - slider_size_half;
			(*SliderEntry).Max.X = slider_value + slider_size_half;
			
			SliderChanged = false;
		}
	}
}
void UI::Control::Slider::InsertDrawingEntryRelay()
{
	if (!SliderEntry.Is())
	{
		SliderEntry.Allocate(ControlManager -> Inst_Data_Container, 1);
		(*SliderEntry).Col = Color(0.5f, 0.5f, 0.5f);
		(*SliderEntry).Layer = Layer - 0.01f;
		SliderChanged = true;
	}
}
void UI::Control::Slider::RemoveDrawingEntryRelay()
{
	if (SliderEntry.Is())
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
	if (!Enabled || !Visible || !Drawable) { return; }

	float slider_size_half = SliderSize / 2;
	float slider_min = AnchorBox.Min.X + slider_size_half;
	float slider_max = AnchorBox.Max.X - slider_size_half;

	float slider_value = params.Position.Absolute.X;
	slider_value -= slider_min;
	slider_value /= (slider_max - slider_min);
	slider_value *= (SliderMax - SliderMin);
	slider_value += SliderMin;

	if (slider_value < SliderMin) { slider_value = SliderMin; }
	if (slider_value > SliderMax) { slider_value = SliderMax; }

	SliderValue = slider_value;
	SliderChanged = true;

	if (ValueChangedFunc != NULL) { ValueChangedFunc(SliderValue); }
}
void UI::Control::Slider::RelayCursorDrag(UserParameter::Mouse::Drag params)
{
	if (!Enabled || !Visible || !Drawable) { return; }

	float slider_size_half = SliderSize / 2;
	float slider_min = AnchorBox.Min.X + slider_size_half;
	float slider_max = AnchorBox.Max.X - slider_size_half;

	float slider_value = params.Position.Absolute.X;
	slider_value -= slider_min;
	slider_value /= (slider_max - slider_min);
	slider_value *= (SliderMax - SliderMin);
	slider_value += SliderMin;

	if (slider_value < SliderMin) { slider_value = SliderMin; }
	if (slider_value > SliderMax) { slider_value = SliderMax; }

	SliderValue = slider_value;
	SliderChanged = true;

	if (ValueChangedFunc != NULL) { ValueChangedFunc(SliderValue); }
}
