#include "Form.hpp"



UI::Control::Form::~Form()
{ }
UI::Control::Form::Form()
	: Base()
	, IsMovable(true)
	, IsResizable(true)
	, ChangingBoxType(EChangingBoxType::None)
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



UI::Control::Form::EChangingBoxType UI::Control::Form::FindChangingArea(VectorF2 mouse) const
{
	BoxF2 BoarderBox;
	BoarderBox.Min = DisplayBox.Min + AnchorBoarder.Min;
	BoarderBox.Max = DisplayBox.Max - AnchorBoarder.Max;

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
		if (MinX_Hovering && !(MinY_Hovering || MaxY_Hovering)) { return EChangingBoxType::ResizeMinX; }
		if (MaxX_Hovering && !(MinY_Hovering || MaxY_Hovering)) { return EChangingBoxType::ResizeMaxX; }
		if (MinY_Hovering && !(MinX_Hovering || MaxX_Hovering)) { return EChangingBoxType::ResizeMinY; }
		if (MaxY_Hovering && !(MinX_Hovering || MaxX_Hovering)) { return EChangingBoxType::ResizeMaxY; }

		if (MinX_Hovering && MinY_Hovering) { return EChangingBoxType::ResizeMinMin; }
		if (MinX_Hovering && MaxY_Hovering) { return EChangingBoxType::ResizeMinMax; }
		if (MaxX_Hovering && MinY_Hovering) { return EChangingBoxType::ResizeMaxMin; }
		if (MaxX_Hovering && MaxY_Hovering) { return EChangingBoxType::ResizeMaxMax; }
	}
	else
	{
		return EChangingBoxType::Move;
	}
	return EChangingBoxType::None;
}
void UI::Control::Form::UserChangingBox(DragArgs args)
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

		if (ChangingBoxType != EChangingBoxType::None)
		{
			BoxF2 box = DisplayBox;
			if (ChangingBoxType == EChangingBoxType::Move)
			{
				box = BoxF2(
					args.Position.Buffer.Corner - ChangingBoxRel.Min,
					args.Position.Buffer.Corner - ChangingBoxRel.Max
				);
			}
			else if (ChangingBoxType == EChangingBoxType::ResizeMinX) { box.Min.X = args.Position.Buffer.Corner.X; }
			else if (ChangingBoxType == EChangingBoxType::ResizeMaxX) { box.Max.X = args.Position.Buffer.Corner.X; }
			else if (ChangingBoxType == EChangingBoxType::ResizeMinY) { box.Min.Y = args.Position.Buffer.Corner.Y; }
			else if (ChangingBoxType == EChangingBoxType::ResizeMaxY) { box.Max.Y = args.Position.Buffer.Corner.Y; }
			else if (ChangingBoxType == EChangingBoxType::ResizeMinMin) { box.Min.X = args.Position.Buffer.Corner.X; box.Min.Y = args.Position.Buffer.Corner.Y; }
			else if (ChangingBoxType == EChangingBoxType::ResizeMinMax) { box.Min.X = args.Position.Buffer.Corner.X; box.Max.Y = args.Position.Buffer.Corner.Y; }
			else if (ChangingBoxType == EChangingBoxType::ResizeMaxMin) { box.Max.X = args.Position.Buffer.Corner.X; box.Min.Y = args.Position.Buffer.Corner.Y; }
			else if (ChangingBoxType == EChangingBoxType::ResizeMaxMax) { box.Max.X = args.Position.Buffer.Corner.X; box.Max.Y = args.Position.Buffer.Corner.Y; }
			ChangeAnchorBox(box);
		}
	}
	else if (args.Action == Action::Release)
	{
		ChangingBoxType = EChangingBoxType::None;
	}
}

#include <iostream>
#include "Base/Manager.hpp"
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
		EChangingBoxType type = FindChangingArea(ControlManager -> CursorPosition);
		if (type == EChangingBoxType::Move) { ControlManager -> CursorsUseDefault(); }
		else if (type == EChangingBoxType::ResizeMinX) { ControlManager -> CursorsUseResizeH(); }
		else if (type == EChangingBoxType::ResizeMaxX) { ControlManager -> CursorsUseResizeH(); }
		else if (type == EChangingBoxType::ResizeMinY) { ControlManager -> CursorsUseResizeV(); }
		else if (type == EChangingBoxType::ResizeMaxY) { ControlManager -> CursorsUseResizeV(); }
		else if (type == EChangingBoxType::ResizeMinMin) { ControlManager -> CursorsUseResizeD0(); }
		else if (type == EChangingBoxType::ResizeMaxMax) { ControlManager -> CursorsUseResizeD0(); }
		else if (type == EChangingBoxType::ResizeMaxMin) { ControlManager -> CursorsUseResizeD1(); }
		else if (type == EChangingBoxType::ResizeMinMax) { ControlManager -> CursorsUseResizeD1(); }
		else { ControlManager -> CursorsUseDefault(); }
	}
}
void UI::Control::Form::RelayCursorDrag(DragArgs args)
{
	UserChangingBox(args);
}
