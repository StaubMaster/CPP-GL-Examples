#include "Slider.hpp"
#include "Base/Manager.hpp"

#include "User/MouseArgs.hpp"

#include "Text/Manager.hpp"
#include <math.h>



UI::Control::Slider::Slider() : Base()
{
	Depth = 0.1f;
	Anchor.X.Anchor = AnchorType::Min;
	Anchor.Y.Anchor = AnchorType::Min;
	AnchorSize = VectorF2(75, 25);

	float padding = 0;
	AnchorPadding = BoxF2(VectorF2(padding, padding), VectorF2(padding, padding));

	ColorDefault = ColorF4(0.375f, 0.375f, 0.375f);
	ColorHover = ColorF4(0.25f, 0.25f, 0.25f);

//	SliderChanged = true;
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
	Value = val; /*SliderChanged = true;*/ ValueChangedFunc(Value); ValueXChangedFunc(Value.X); ValueYChangedFunc(Value.Y);
	if (SliderObject.Is())
		{
			VectorF2 slider_size_half = NubSize / 2.0f;
			VectorF2 slider_min = DisplayBox.Min + slider_size_half;
			VectorF2 slider_max = DisplayBox.Max - slider_size_half;

			VectorF2 slider_normal = Value;
			slider_normal -= ValueMin;
			slider_normal /= (ValueMax - ValueMin);

			VectorF2 slider_value = slider_normal;
			slider_value *= (slider_max - slider_min);
			slider_value += slider_min;

			SliderObject.Box().Min = slider_value - slider_size_half;
			SliderObject.Box().Max = slider_value + slider_size_half;
		}
}
void UI::Control::Slider::SetValueX(float val)
{
	Value.X = val; /*SliderChanged = true;*/ ValueXChangedFunc(Value.X);
	if (SliderObject.Is())
		{
			VectorF2 slider_size_half = NubSize / 2.0f;
			VectorF2 slider_min = DisplayBox.Min + slider_size_half;
			VectorF2 slider_max = DisplayBox.Max - slider_size_half;

			VectorF2 slider_normal = Value;
			slider_normal -= ValueMin;
			slider_normal /= (ValueMax - ValueMin);

			VectorF2 slider_value = slider_normal;
			slider_value *= (slider_max - slider_min);
			slider_value += slider_min;

			SliderObject.Box().Min = slider_value - slider_size_half;
			SliderObject.Box().Max = slider_value + slider_size_half;
		}
}
void UI::Control::Slider::SetValueY(float val)
{
	Value.Y = val; /*SliderChanged = true;*/ ValueYChangedFunc(Value.Y);
	if (SliderObject.Is())
		{
			VectorF2 slider_size_half = NubSize / 2.0f;
			VectorF2 slider_min = DisplayBox.Min + slider_size_half;
			VectorF2 slider_max = DisplayBox.Max - slider_size_half;

			VectorF2 slider_normal = Value;
			slider_normal -= ValueMin;
			slider_normal /= (ValueMax - ValueMin);

			VectorF2 slider_value = slider_normal;
			slider_value *= (slider_max - slider_min);
			slider_value += slider_min;

			SliderObject.Box().Min = slider_value - slider_size_half;
			SliderObject.Box().Max = slider_value + slider_size_half;
		}
}

void UI::Control::Slider::ChangeValue(DisplayPosition mouse_pos)
{
	if (!IsInteractible()) { return; }

	VectorF2 slider_size_half = NubSize / 2.0f;
	VectorF2 slider_pos_min = DisplayBox.Min + slider_size_half;
	VectorF2 slider_pos_max = DisplayBox.Max - slider_size_half;

	VectorF2 slider_value = mouse_pos.Buffer.Corner;
	slider_value -= slider_pos_min;
	slider_value /= (slider_pos_max - slider_pos_min);
	slider_value *= (ValueMax - ValueMin);
	slider_value += ValueMin;

	slider_value /= ValueResolution;
	slider_value = slider_value.round(); // Vector.round that takes Vector Size
	slider_value *= ValueResolution;

	// Min/Max Functions
	if (slider_value.X < ValueMin.X) { slider_value.X = ValueMin.X; }
	if (slider_value.Y < ValueMin.Y) { slider_value.Y = ValueMin.Y; }

	if (slider_value.X > ValueMax.X) { slider_value.X = ValueMax.X; }
	if (slider_value.Y > ValueMax.Y) { slider_value.Y = ValueMax.Y; }

	Value = slider_value;
//	SliderChanged = true;
	if (SliderObject.Is())
		{
			VectorF2 slider_size_half = NubSize / 2.0f;
			VectorF2 slider_min = DisplayBox.Min + slider_size_half;
			VectorF2 slider_max = DisplayBox.Max - slider_size_half;

			VectorF2 slider_normal = Value;
			slider_normal -= ValueMin;
			slider_normal /= (ValueMax - ValueMin);

			VectorF2 slider_value = slider_normal;
			slider_value *= (slider_max - slider_min);
			slider_value += slider_min;

			SliderObject.Box().Min = slider_value - slider_size_half;
			SliderObject.Box().Max = slider_value + slider_size_half;
		}

	ValueXChangedFunc(Value.X);
	ValueYChangedFunc(Value.Y);
	ValueChangedFunc(Value);
}



void UI::Control::Slider::PutCharactersEntrys()
{
	VectorF2 min = ContainerBox.Min;
	VectorF2 max = ContainerBox.Max;
	VectorF2 center = (max + min) / 2.0f;

	if (TextObject.Is())
	{
		TextObject.Text() = Text;
		TextObject.TextAlignmentX() = Text::Alignment::Mid;
		TextObject.TextAlignmentY() = Text::Alignment::Mid;
		TextObject.CharacterAlignmentX() = Text::Alignment::Mid;
		TextObject.CharacterAlignmentY() = Text::Alignment::Mid;
		TextObject.TextPosition() = center;
		TextObject.Bound() = ContainerBox;
	}
}



std::string UI::Control::Slider::GetText() const
{
	return Text;
}
void UI::Control::Slider::SetText(std::string text)
{
	Text = text;
	PutCharactersEntrys();
}



void UI::Control::Slider::RelayUpdateBox()
{
	//SliderChanged = true;
	if (SliderObject.Is())
	{
		VectorF2 slider_size_half = NubSize / 2.0f;
		VectorF2 slider_min = DisplayBox.Min + slider_size_half;
		VectorF2 slider_max = DisplayBox.Max - slider_size_half;

		VectorF2 slider_normal = Value;
		slider_normal -= ValueMin;
		slider_normal /= (ValueMax - ValueMin);

		VectorF2 slider_value = slider_normal;
		slider_value *= (slider_max - slider_min);
		slider_value += slider_min;

		SliderObject.Box().Min = slider_value - slider_size_half;
		SliderObject.Box().Max = slider_value + slider_size_half;
	}
	if (TextObject.Is())
	{
		PutCharactersEntrys();
	}
}
void UI::Control::Slider::RelayInsertObject()
{
	if (!SliderObject.Is() && Manager != NULL)
	{
		SliderObject.Create();
		SliderObject.Color() = ColorF4(0.5f, 0.5f, 0.5f);
		SliderObject.Layer() = Depth - 0.01f;
		//SliderChanged = true;
	if (SliderObject.Is())
		{
			VectorF2 slider_size_half = NubSize / 2.0f;
			VectorF2 slider_min = DisplayBox.Min + slider_size_half;
			VectorF2 slider_max = DisplayBox.Max - slider_size_half;

			VectorF2 slider_normal = Value;
			slider_normal -= ValueMin;
			slider_normal /= (ValueMax - ValueMin);

			VectorF2 slider_value = slider_normal;
			slider_value *= (slider_max - slider_min);
			slider_value += slider_min;

			SliderObject.Box().Min = slider_value - slider_size_half;
			SliderObject.Box().Max = slider_value + slider_size_half;
		}
	}
	if (!TextObject.Is() && Manager != NULL)
	{
		TextObject.Create();
	}
}
void UI::Control::Slider::RelayRemoveObject()
{
	if (SliderObject.Is() || Manager == NULL)
	{
		SliderObject.Delete();
	}
	if (TextObject.Is() || Manager == NULL)
	{
		TextObject.Delete();
	}
}



void UI::Control::Slider::RelayClick(ClickArgs params)
{
	if (params.Action == Action::Press)
	{
		ChangeValue(params.Position);
	}
}
void UI::Control::Slider::RelayCursorDrag(DragArgs params)
{
	ChangeValue(params.Position);
}
