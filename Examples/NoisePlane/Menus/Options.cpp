#include "Options.hpp"



OptionsMenu::~OptionsMenu() { }
OptionsMenu::OptionsMenu()
	: UI::Control::Form()
{
	MakeTransparent();

	float y = 0.0f;



	FOV_Slider.Anchor.X.AnchorBoth(0.0f, 0.0f);
	FOV_Slider.Anchor.Y.AnchorMin(y);
	FOV_Slider.ValueMin = 20;
	FOV_Slider.ValueMax = 160;
	FOV_Slider.ValueResolution = 1.0f;
	y = FOV_Slider.Anchor.Y.GetMinSize();



	Chunk_Insert_Slider.Anchor.X.AnchorBoth(0.0f, 0.0f);
	Chunk_Insert_Slider.Anchor.Y.AnchorMin(y);
	Chunk_Insert_Slider.ValueMin = 1;
	Chunk_Insert_Slider.ValueMax = 12;
	Chunk_Insert_Slider.ValueResolution = 1.0f;
	y = Chunk_Insert_Slider.Anchor.Y.GetMinSize();



	Chunk_Remove_Slider.Anchor.X.AnchorBoth(0.0f, 0.0f);
	Chunk_Remove_Slider.Anchor.Y.AnchorMin(y);
	Chunk_Remove_Slider.ValueMin = 1;
	Chunk_Remove_Slider.ValueMax = 12;
	Chunk_Remove_Slider.ValueResolution = 1.0f;
	y = Chunk_Remove_Slider.Anchor.Y.GetMinSize();



	ButtonBack.Anchor.X.AnchorMin(0, 200);
	ButtonBack.Anchor.Y.AnchorMax(0);
	ButtonBack.SetText("Back/Exit");
	ButtonBack.ClickFunc.Assign(this, &OptionsMenu::BackFunc);



	ChildInsert(FOV_Slider);
	ChildInsert(Chunk_Insert_Slider);
	ChildInsert(Chunk_Remove_Slider);
	ChildInsert(ButtonBack);
}



#include "../ContextBase.hpp"
void OptionsMenu::BackFunc(ClickArgs args)
{
	if (args.Action == Action::Press)
	{
		ContextBase::ChangeToContext0();
	}
}