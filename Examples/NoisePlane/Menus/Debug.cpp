#include "Debug.hpp"


float CheckBoxText::Place(float y, const char * str)
{
	float x = 0.0f;
	Check.Anchor.X.AnchorMax(0.0f);
	Check.Anchor.Y.AnchorMin(y);
	x = Check.Anchor.X.GetMaxSize();
	Text.Anchor.X.AnchorBoth(0.0f, x);
	Text.Anchor.Y.AnchorMin(y);
	Text.SetText(str);
	return Text.Anchor.Y.GetMinSize();
}
void CheckBoxText::Insert(UI::Control::Form & form)
{
	form.ChildInsert(Text);
	form.ChildInsert(Check);
}



DebugMenu::~DebugMenu() { }
DebugMenu::DebugMenu()
	: UI::Control::Form()
{
	Anchor.X.AnchorMin(0, 360.0f);
	Anchor.Y.AnchorBoth(0, 0);

	float y = 0.0f;
	y = FPS.Place(y, "FPS");
	y = View.Place(y, "View");
	y = ChunkHere.Place(y, "ChunkHere");
	y = VoxelThere.Place(y, "VoxelThere");
	y = VoxelChunkMemory.Place(y, "VoxelChunkMemory");
	y = VoxelChunkBoxes.Place(y, "VoxelChunkBoxes");

	FPS.Insert(*this);
	View.Insert(*this);
	ChunkHere.Insert(*this);
	VoxelThere.Insert(*this);
	VoxelChunkMemory.Insert(*this);
	VoxelChunkBoxes.Insert(*this);
}
