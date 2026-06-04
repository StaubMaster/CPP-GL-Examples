#include "Form.hpp"



UI::Control::Form::~Form()
{ }
UI::Control::Form::Form()
	: Base()
	, IsMovable(true)
	, IsResizable(true)
	, ChangingBoxType(EBoxChangeType::None)
{
	// give this stuff to Base ?
	Depth = 0.9f;
	Anchor.X.Anchor = AnchorType::None;
	Anchor.Y.Anchor = AnchorType::None;
	AnchorSize = VectorF2(480, 360);
	AnchorNormal = VectorF2(0.5, 0.5);
	ColorDefault = ColorF4(0.75f, 0.75f, 0.75f);
	ColorHover = ColorF4(0.75f, 0.75f, 0.75f);
}



UI::Control::Form::EBoxChangeType UI::Control::Form::FindChangingArea(VectorF2 mouse) const
{
	BoxF2 BoarderBox;
	BoarderBox.Min = DisplayBox.Min + 10.0f;
	BoarderBox.Max = DisplayBox.Max - 10.0f;

	BoxF2 MinX_Box(VectorF2(DisplayBox.Min.X, DisplayBox.Min.Y), VectorF2(BoarderBox.Min.X, DisplayBox.Max.Y));
	BoxF2 MaxX_Box(VectorF2(BoarderBox.Max.X, DisplayBox.Min.Y), VectorF2(DisplayBox.Max.X, DisplayBox.Max.Y));
	BoxF2 MinY_Box(VectorF2(DisplayBox.Min.X, DisplayBox.Min.Y), VectorF2(DisplayBox.Max.X, BoarderBox.Min.Y));
	BoxF2 MaxY_Box(VectorF2(DisplayBox.Min.X, BoarderBox.Max.Y), VectorF2(DisplayBox.Max.X, DisplayBox.Max.Y));

	bool MinX_Hovering = MinX_Box.IntersectInclusive(mouse).All(true);
	bool MinY_Hovering = MinY_Box.IntersectInclusive(mouse).All(true);
	bool MaxX_Hovering = MaxX_Box.IntersectInclusive(mouse).All(true);
	bool MaxY_Hovering = MaxY_Box.IntersectInclusive(mouse).All(true);

	if (MinX_Hovering || MaxX_Hovering || MinY_Hovering || MaxY_Hovering)
	{
		if (MinX_Hovering && !(MinY_Hovering || MaxY_Hovering)) { return EBoxChangeType::ResizeMinX; }
		if (MaxX_Hovering && !(MinY_Hovering || MaxY_Hovering)) { return EBoxChangeType::ResizeMaxX; }
		if (MinY_Hovering && !(MinX_Hovering || MaxX_Hovering)) { return EBoxChangeType::ResizeMinY; }
		if (MaxY_Hovering && !(MinX_Hovering || MaxX_Hovering)) { return EBoxChangeType::ResizeMaxY; }

		if (MinX_Hovering && MinY_Hovering) { return EBoxChangeType::ResizeMinMin; }
		if (MinX_Hovering && MaxY_Hovering) { return EBoxChangeType::ResizeMinMax; }
		if (MaxX_Hovering && MinY_Hovering) { return EBoxChangeType::ResizeMaxMin; }
		if (MaxX_Hovering && MaxY_Hovering) { return EBoxChangeType::ResizeMaxMax; }
	}
	else
	{
		return EBoxChangeType::Move;
	}
	return EBoxChangeType::None;
}

#include <iostream>
#include "Base/Manager.hpp"
/* put into Manager
	Cursors flicked when moving
	put into Manager, Cursor should stay the same until changing ends
	dont do any Events (drag/move) while changing
*/
void UI::Control::Form::RelayHover(HoverArgs args)
{
	/*if (args == HoverArgs::Enter)
	{
		ControlManager -> CursorsUseResizeH();
	}*/
	if (args == HoverArgs::Leave)
	{
		ControlManager -> CursorsUseDefault();
	}
	if (args == HoverArgs::Move)
	{
		EBoxChangeType type = FindChangingArea(ControlManager -> CursorPosition);
		if (type == EBoxChangeType::Move) { ControlManager -> CursorsUseDefault(); }
		else if (type == EBoxChangeType::ResizeMinX) { ControlManager -> CursorsUseBoxEdge(0); }
		else if (type == EBoxChangeType::ResizeMinY) { ControlManager -> CursorsUseBoxEdge(1); }
		else if (type == EBoxChangeType::ResizeMaxX) { ControlManager -> CursorsUseBoxEdge(2); }
		else if (type == EBoxChangeType::ResizeMaxY) { ControlManager -> CursorsUseBoxEdge(3); }
		else if (type == EBoxChangeType::ResizeMinMin) { ControlManager -> CursorsUseBoxCorn(0); }
		else if (type == EBoxChangeType::ResizeMaxMin) { ControlManager -> CursorsUseBoxCorn(1); }
		else if (type == EBoxChangeType::ResizeMinMax) { ControlManager -> CursorsUseBoxCorn(2); }
		else if (type == EBoxChangeType::ResizeMaxMax) { ControlManager -> CursorsUseBoxCorn(3); }
		else { ControlManager -> CursorsUseDefault(); }
	}
}
void UI::Control::Form::RelayCursorDrag(DragArgs args)
{
	if (args.Action == Action::Press)
	{
		ChangingBoxRel.Min = args.Position.Buffer.Corner - DisplayBox.Min;
		ChangingBoxRel.Max = args.Position.Buffer.Corner - DisplayBox.Max;

		/* Resize area
			in vscode, the cursor needs to be a bit inside of the window to resize
			in firefox, the cursor needs to be a bit outside of the window to resize
		*/

		ChangingBoxType = FindChangingArea(args.Position.Buffer.Corner);
	}
	else if (args.Action == Action::Repeat)
	{
		// when changing would make the Box go outside of the Window
		// keep it inside of the Window (with MBP) and lock it to that Edge
		// when changing makes a Edge of the Box be away from whe Window Boarder
		// make it unlocked from that Edge
		// also make things lock to eachother ?

		if (ChangingBoxType != EBoxChangeType::None)
		{
			const VectorF2 & mouse = args.Position.Buffer.Corner;
			BoxF2 box = DisplayBox;
			if (ChangingBoxType == EBoxChangeType::Move)
			{
				box.Min = mouse - ChangingBoxRel.Min;
				box.Max = mouse - ChangingBoxRel.Max;
			}
			else if (ChangingBoxType == EBoxChangeType::ResizeMinX) { box.Min.X = mouse.X; }
			else if (ChangingBoxType == EBoxChangeType::ResizeMaxX) { box.Max.X = mouse.X; }
			else if (ChangingBoxType == EBoxChangeType::ResizeMinY) { box.Min.Y = mouse.Y; }
			else if (ChangingBoxType == EBoxChangeType::ResizeMaxY) { box.Max.Y = mouse.Y; }
			else if (ChangingBoxType == EBoxChangeType::ResizeMinMin) { box.Min.X = mouse.X; box.Min.Y = mouse.Y; }
			else if (ChangingBoxType == EBoxChangeType::ResizeMinMax) { box.Min.X = mouse.X; box.Max.Y = mouse.Y; }
			else if (ChangingBoxType == EBoxChangeType::ResizeMaxMin) { box.Max.X = mouse.X; box.Min.Y = mouse.Y; }
			else if (ChangingBoxType == EBoxChangeType::ResizeMaxMax) { box.Max.X = mouse.X; box.Max.Y = mouse.Y; }
			ChangeAnchorBox(box, ChangingBoxType);
		}
	}
	else if (args.Action == Action::Release)
	{
		ChangingBoxType = EBoxChangeType::None;
	}
}
