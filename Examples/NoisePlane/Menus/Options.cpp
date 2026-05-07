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
	FOV.ValueMin.X = 20;
	FOV.ValueMax.X = 160;
	FOV.ValueResolution.X = 1.0f;
	y = FOV.Anchor.Y.GetMinSize();

	Depth.Anchor.X.AnchorBoth(0.0f, 0.0f);
	Depth.Anchor.Y.AnchorMin(y);
	Depth.ValueMin.X = 10.0f;
	Depth.ValueMax.X = 1000.0f;
	Depth.ValueResolution.X = 10.0f;
	y = Depth.Anchor.Y.GetMinSize();

	DepthRange.Anchor.X.AnchorBoth(0.0f, 0.0f);
	DepthRange.Anchor.Y.AnchorMin(y);
	DepthRange.ValueMin.X = 0.0f;
	DepthRange.ValueMax.X = 1.0f;
	DepthRange.ValueResolution.X = 0.1f;
	y = DepthRange.Anchor.Y.GetMinSize();

	y = 0.0f;

	Back.Anchor.X.AnchorBoth(0.0f, 0.0f);
	Back.Anchor.Y.AnchorMax(y);
	Back.SetText("Back");
	y = Back.Anchor.Y.GetMaxSize();

	ChunkInsert.Anchor.X.AnchorBoth(0.0f, 0.0f);
	ChunkInsert.Anchor.Y.AnchorMax(y);
	ChunkInsert.ValueMin.X = 1;
	ChunkInsert.ValueMax.X = 24;
	ChunkInsert.ValueResolution.X = 1.0f;
	y = ChunkInsert.Anchor.Y.GetMaxSize();

	ChunkRemove.Anchor.X.AnchorBoth(0.0f, 0.0f);
	ChunkRemove.Anchor.Y.AnchorMax(y);
	ChunkRemove.ValueMin.X = 1;
	ChunkRemove.ValueMax.X = 24;
	ChunkRemove.ValueResolution.X = 1.0f;
	y = ChunkRemove.Anchor.Y.GetMaxSize();

	ChildInsert(FOV);
	ChildInsert(Depth);
	ChildInsert(DepthRange);
	ChildInsert(ChunkInsert);
	ChildInsert(ChunkRemove);
	ChildInsert(Back);
}
