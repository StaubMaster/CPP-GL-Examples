#include "Options.hpp"



OptionsMenu::~OptionsMenu() { }
OptionsMenu::OptionsMenu()
	: UI::Control::Form()
{
	MakeTransparent();

	float y;

	y = 0.0f;

	FOV.Anchor.X.AnchorBoth(0.0f, 0.0f);
	FOV.Anchor.Y.AnchorMin(y);
	FOV.ValueMin = 20;
	FOV.ValueMax = 160;
	FOV.ValueResolution = 1.0f;
	y = FOV.Anchor.Y.GetMinSize();

	Depth.Anchor.X.AnchorBoth(0.0f, 0.0f);
	Depth.Anchor.Y.AnchorMin(y);
	Depth.ValueMin = 10.0f;
	Depth.ValueMax = 1000.0f;
	Depth.ValueResolution = 10.0f;
	y = Depth.Anchor.Y.GetMinSize();

	y = 0.0f;

	Back.Anchor.X.AnchorBoth(0.0f, 0.0f);
	Back.Anchor.Y.AnchorMax(y);
	Back.SetText("Back");
	y = Back.Anchor.Y.GetMaxSize();

	ChunkInsert.Anchor.X.AnchorBoth(0.0f, 0.0f);
	ChunkInsert.Anchor.Y.AnchorMax(y);
	ChunkInsert.ValueMin = 1;
	ChunkInsert.ValueMax = 24;
	ChunkInsert.ValueResolution = 1.0f;
	y = ChunkInsert.Anchor.Y.GetMaxSize();

	ChunkRemove.Anchor.X.AnchorBoth(0.0f, 0.0f);
	ChunkRemove.Anchor.Y.AnchorMax(y);
	ChunkRemove.ValueMin = 1;
	ChunkRemove.ValueMax = 24;
	ChunkRemove.ValueResolution = 1.0f;
	y = ChunkRemove.Anchor.Y.GetMaxSize();

	ChildInsert(FOV);
	ChildInsert(Depth);
	ChildInsert(ChunkInsert);
	ChildInsert(ChunkRemove);
	ChildInsert(Back);
}
