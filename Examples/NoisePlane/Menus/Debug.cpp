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

	Generation3DFactor.Anchor.X.AnchorBoth(0, 0);
	Generation3DFactor.Anchor.Y.AnchorMin(y);
	Generation3DFactor.ValueMin = 0.0f;
	Generation3DFactor.SetValue(4.0f);
	Generation3DFactor.ValueMax = 8.0f;
	Generation3DFactor.ValueResolution = 1.0f;
	y = Generation3DFactor.Anchor.Y.GetMinSize();

	Generation3DComparison.Anchor.X.AnchorBoth(0, 0);
	Generation3DComparison.Anchor.Y.AnchorMin(y);
	Generation3DComparison.ValueMin = 0.0f;
	Generation3DComparison.SetValue(0.0f);
	Generation3DComparison.ValueMax = 1.0f;
	Generation3DComparison.ValueResolution = 0.01f;
	y = Generation3DComparison.Anchor.Y.GetMinSize();

	FPS.Insert(*this);
	View.Insert(*this);
	ChunkHere.Insert(*this);
	VoxelThere.Insert(*this);
	VoxelChunkMemory.Insert(*this);
	VoxelChunkBoxes.Insert(*this);
	ChildInsert(Generation3DFactor);
	ChildInsert(Generation3DComparison);
}
