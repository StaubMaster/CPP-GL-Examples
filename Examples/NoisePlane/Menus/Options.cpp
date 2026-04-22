#include "Options.hpp"



OptionsMenu::~OptionsMenu() { }
OptionsMenu::OptionsMenu()
	: UI::Control::Form()
{
	MakeTransparent();

	float x;
	float y;



	y = 0.0f;

	x = 0.0f;
	FOV_Name.Anchor.X.AnchorMin(x, 100);
	FOV_Name.Anchor.Y.AnchorMin(y);
	FOV_Name.SetText("FOV");
	x = FOV_Name.Anchor.X.GetMinSize();
	FOV_Slider.Anchor.X.AnchorMin(x, 200);
	FOV_Slider.Anchor.Y.AnchorMin(y);
	FOV_Slider.ValueMin = 20;
	FOV_Slider.ValueMax = 160;
	FOV_Slider.ValueResolution = 1.0f;
	x = FOV_Slider.Anchor.X.GetMinSize();
	FOV_Value.Anchor.X.AnchorMin(x, 100);
	FOV_Value.Anchor.Y.AnchorMin(y);
	y = FOV_Value.Anchor.Y.GetMinSize();



	x = 0.0f;
	Chunk_Insert_Name.Anchor.X.AnchorMin(x, 100);
	Chunk_Insert_Name.Anchor.Y.AnchorMin(y);
	Chunk_Insert_Name.SetText("Insert");
	x = Chunk_Insert_Name.Anchor.X.GetMinSize();
	Chunk_Insert_Slider.Anchor.X.AnchorMin(x, 200);
	Chunk_Insert_Slider.Anchor.Y.AnchorMin(y);
	Chunk_Insert_Slider.ValueMin = 1;
	Chunk_Insert_Slider.ValueMax = 12;
	Chunk_Insert_Slider.ValueResolution = 1.0f;
	x = Chunk_Insert_Slider.Anchor.X.GetMinSize();
	Chunk_Insert_Value.Anchor.X.AnchorMin(x, 100);
	Chunk_Insert_Value.Anchor.Y.AnchorMin(y);
	y = Chunk_Insert_Value.Anchor.Y.GetMinSize();



	x = 0.0f;
	Chunk_Remove_Name.Anchor.X.AnchorMin(x, 100);
	Chunk_Remove_Name.Anchor.Y.AnchorMin(y);
	Chunk_Remove_Name.SetText("Remove");
	x = Chunk_Remove_Name.Anchor.X.GetMinSize();
	Chunk_Remove_Slider.Anchor.X.AnchorMin(x, 200);
	Chunk_Remove_Slider.Anchor.Y.AnchorMin(y);
	Chunk_Remove_Slider.ValueMin = 1;
	Chunk_Remove_Slider.ValueMax = 12;
	Chunk_Remove_Slider.ValueResolution = 1.0f;
	x = Chunk_Remove_Slider.Anchor.X.GetMinSize();
	Chunk_Remove_Value.Anchor.X.AnchorMin(x, 100);
	Chunk_Remove_Value.Anchor.Y.AnchorMin(y);
	y = Chunk_Remove_Value.Anchor.Y.GetMinSize();



	ButtonBack.Anchor.X.AnchorMin(0);
	ButtonBack.Anchor.Y.AnchorMax(0);
	ButtonBack.ClickFunc.Assign(this, &OptionsMenu::BackFunc);



	ChildInsert(FOV_Name);
	ChildInsert(FOV_Slider);
	ChildInsert(FOV_Value);

	ChildInsert(Chunk_Insert_Name);
	ChildInsert(Chunk_Insert_Slider);
	ChildInsert(Chunk_Insert_Value);

	ChildInsert(Chunk_Remove_Name);
	ChildInsert(Chunk_Remove_Slider);
	ChildInsert(Chunk_Remove_Value);

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