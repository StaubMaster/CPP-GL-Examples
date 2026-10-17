#include "Debug.hpp"
#include "ContextNoisePlane.hpp"



float CheckBoxText::Place(float y, const char * str)
{
	float x = 0.0f;
	Check.Anchor.X.AnchorMax(0.0f);
	Check.Anchor.Y.AnchorMin(y);
	x = Check.Anchor.X.GetMaxSize();
	Label.Anchor.X.AnchorBoth(0.0f, x);
	Label.Anchor.Y.AnchorMin(y);
	Label.SetText(str);
	return Label.Anchor.Y.GetMinSize();
}
void CheckBoxText::Insert(UI::Control::Form & form)
{
	form.ChildInsert(Label);
	form.ChildInsert(Check);
}



DebugMenu::~DebugMenu() { }
DebugMenu::DebugMenu(ContextNoisePlane & context)
	: UI::Control::Form()
	, Context(context)
{
	Anchor.X.AnchorMin(0, 360.0f);
	Anchor.Y.AnchorBoth(0, 0);

	float y = 0.0f;

	y = FPS.Place(y, "FPS");

	y = TimeThreads.Place(y, "TimeThreads");
	y = TimeWaitDo.Place(y, "TimeWaitDo");

	y = AuxThread0Idle.Place(y, "AuxThread0Idle");
	y = AuxThread1Idle.Place(y, "AuxThread1Idle");
	y = AuxThread2Idle.Place(y, "AuxThread2Idle");

	y = View.Place(y, "View");
	y = ChunkHere.Place(y, "ChunkHere");
	y = VoxelThere.Place(y, "VoxelThere");

	y = ChunkRange.Place(y, "ChunkRange");
	y = ChunkRangeCenter.Place(y, "ChunkRangeCenter");

	y = VoxelChunkMemory.Place(y, "VoxelChunkMemory");
	y = VoxelChunkBoxes.Place(y, "VoxelChunkBoxes");

	FPS.Insert(*this);
	TimeThreads.Insert(*this);
	TimeWaitDo.Insert(*this);
	AuxThread0Idle.Insert(*this);
	AuxThread1Idle.Insert(*this);
	AuxThread2Idle.Insert(*this);
	View.Insert(*this);
	ChunkHere.Insert(*this);
	VoxelThere.Insert(*this);
	ChunkRange.Insert(*this);
	ChunkRangeCenter.Insert(*this);
	VoxelChunkMemory.Insert(*this);
	VoxelChunkBoxes.Insert(*this);
}
