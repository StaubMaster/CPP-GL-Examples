#include "Slider.hpp"
#include "Base/Manager.hpp"

#include "User/MouseArgs.hpp"

#include "Text/Manager.hpp"
#include <math.h>



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
void UI::Control::Slider::ChangeValue(DisplayPosition mouse_pos)
{
	if (!_Interactible) { return; }

	float slider_size_half = SliderSize / 2;
	float slider_pos_min = AnchorBox.Min.X + slider_size_half;
	float slider_pos_max = AnchorBox.Max.X - slider_size_half;

	//float slider_value = mouse_pos.Absolute.X;
	float slider_value = mouse_pos.Buffer.Corner.X;
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



void UI::Control::Slider::CalcCharacterCount()
{
	CharacterCountLimit2D = AnchorSize / CharacterSize;
	unsigned int count = 0;
	count += ceil(CharacterCountLimit2D.X);
	count += ceil(CharacterCountLimit2D.Y);
	if (CharacterCountLimit != count)
	{
		CharacterCountLimit = count;
		CharacterCountLimitChanged = true;
	}
}
void UI::Control::Slider::PutCharactersEntrys()
{
	Point2D min = AnchorBox.Min;
	Point2D max = AnchorBox.Max;
	Point2D center = (max + min) / 2.0f;

	if (TextObject.Is())
	{
		TextObject.String() = Text;
		TextObject.TextAlignmentX() = Text::Alignment::Mid;
		TextObject.TextAlignmentY() = Text::Alignment::Mid;
		TextObject.CharacterAlignmentX() = Text::Alignment::Mid;
		TextObject.CharacterAlignmentY() = Text::Alignment::Mid;
		TextObject.TextPosition() = center;
		TextObject.Bound() = AnchorBox;
	}
}



std::string UI::Control::Slider::GetText() const
{
	return Text;
}
void UI::Control::Slider::SetText(std::string text)
{
	Text = text;
	TextChanged = true;
}



void UI::Control::Slider::UpdateEntrysRelay()
{
	if (SliderObject.Is())
	{
		if (SliderChanged)
		{
			SliderObject.Box().Min.Y = AnchorBox.Min.Y;
			SliderObject.Box().Max.Y = AnchorBox.Max.Y;

			float slider_size_half = SliderSize / 2;
			float slider_min = AnchorBox.Min.X + slider_size_half;
			float slider_max = AnchorBox.Max.X - slider_size_half;

			float slider_normal = (Value - ValueMin) / (ValueMax - ValueMin);
			float slider_value = (slider_normal * (slider_max - slider_min)) + slider_min;
			
			SliderObject.Box().Min.X = slider_value - slider_size_half;
			SliderObject.Box().Max.X = slider_value + slider_size_half;
			
			SliderChanged = false;
		}
	}
	if (TextObject.Is() && TextManager != NULL)
	{
		if (CharacterCountLimitChanged)
		{
			//TextObject.Delete();
			////TextManager -> Inst_Data_Container.CompactHere();
			////TextEntry.Allocate(TextManager -> Inst_Data_Container, CharacterCountLimit);
			//TextObject.Create();

			TextChanged = true;
			CharacterCountLimitChanged = false;
		}
		if (TextChanged)
		{
			PutCharactersEntrys();
			TextChanged = false;
		}
	}
}
void UI::Control::Slider::InsertDrawingEntryRelay()
{
	if (!SliderObject.Is() && ControlManager != NULL)
	{
		SliderObject.Create();
		SliderObject.Color() = ColorF4(0.5f, 0.5f, 0.5f);
		SliderObject.Layer() = Layer - 0.01f;
		SliderChanged = true;
	}
	if (!TextObject.Is() && TextManager != NULL)
	{
		CalcCharacterCount();
		TextObject.Create();
		//TextEntry.Allocate(TextManager -> Inst_Data_Container, CharacterCountLimit);
	}
}
void UI::Control::Slider::RemoveDrawingEntryRelay()
{
	if (SliderObject.Is() || ControlManager == NULL)
	{
		SliderObject.Delete();
	}
	if (TextObject.Is() || TextManager == NULL)
	{
		TextObject.Delete();
	}
}
void UI::Control::Slider::UpdateBoxRelay()
{
	SliderChanged = true;
	if (TextObject.Is())
	{
		CalcCharacterCount();
		TextChanged = true;
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
