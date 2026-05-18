#include "Options.hpp"
#include "ContextNoisePlane.hpp"



OptionsMenu::~OptionsMenu() { }
OptionsMenu::OptionsMenu(ContextNoisePlane & context)
	: UI::Control::Form()
	, Context(context)
{
	MakeTransparent();

	float y;

	y = 0.0f;

	FPS.Anchor.X.AnchorBoth(0.0f, 0.0f);
	FPS.Anchor.Y.AnchorMin(y);
	FPS.ValueMin.X = 32;
	FPS.ValueMax.X = 1024;
	FPS.ValueResolution.X = 32.0f;
	y = FPS.Anchor.Y.GetMinSize();

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

	ChildInsert(FPS);
	ChildInsert(FOV);
	ChildInsert(Depth);
	ChildInsert(DepthRange);
	ChildInsert(ChunkInsert);
	ChildInsert(ChunkRemove);
	ChildInsert(Back);
}

void OptionsMenu::FPSFunc(float val)
{
	//window.FrameTime.Change(val);
	Context.window.FrameTime = FrameTime(val, 1.0f / 0.0f);

	unsigned int v = val;
	Context.OptionsMenu.FPS.SetText("FPS:" + std::to_string(v));
}
void OptionsMenu::FOVFunc(float val)
{
	Context.view.FOV = Angle::Degrees(val);
	Context.Multiform_FOV.ChangeData(Context.view.FOV);

	unsigned int v = val;
	Context.OptionsMenu.FOV.SetText("FOV:" + std::to_string(v));
}
void OptionsMenu::DepthFunc(float val)
{
	Context.view.Depth.Factors.ChangeFar(val);
	Context.Multiform_Depth.ChangeData(Context.view.Depth);

	unsigned int v = val;
	Context.OptionsMenu.Depth.SetText("Depth:" + std::to_string(v));
}
void OptionsMenu::DepthRangeFunc(float val)
{
	Context.view.Depth.Range.ChangeMin(val);
	Context.Multiform_Depth.ChangeData(Context.view.Depth);
	Context.OptionsMenu.DepthRange.SetText("DepthRange:" + std::to_string(val));
}
void OptionsMenu::Chunk_InsertFunc(float val)
{
	Context.OptionsMenu.ChunkInsert.SetText("Insert:" + std::to_string(val));
}
void OptionsMenu::Chunk_RemoveFunc(float val)
{
	Context.OptionsMenu.ChunkRemove.SetText("Remove:" + std::to_string(val));
}
void OptionsMenu::BackFunc(ClickArgs args)
{
	if (args.Action != Action::Press) { return; }
	if (Context.OptionsMenu.IsVisible())
	{
		Context.OptionsMenu.Hide();
	}
	if (!Context.PauseMenu.IsVisible())
	{
		Context.PauseMenu.Show();
	}
}
