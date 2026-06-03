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

		BoxF2 MinX_Box(VectorF2(DisplayBox.Min.X, DisplayBox.Min.Y), VectorF2(DisplayBox.Min.X + AnchorBoarder.Min.X, DisplayBox.Max.Y));
		BoxF2 MaxX_Box(VectorF2(DisplayBox.Max.X - AnchorBoarder.Max.X, DisplayBox.Min.Y), VectorF2(DisplayBox.Max.X, DisplayBox.Max.Y));
		BoxF2 MinY_Box(VectorF2(DisplayBox.Min.X, DisplayBox.Min.Y), VectorF2(DisplayBox.Max.X, DisplayBox.Min.Y + AnchorBoarder.Min.Y));
		BoxF2 MaxY_Box(VectorF2(DisplayBox.Min.X, DisplayBox.Max.Y - AnchorBoarder.Max.Y), VectorF2(DisplayBox.Max.X, DisplayBox.Max.Y));

		bool MinX_Hovering = MinX_Box.IntersectInclusive(args.Position.Buffer.Corner).All(true);
		bool MinY_Hovering = MinY_Box.IntersectInclusive(args.Position.Buffer.Corner).All(true);
		bool MaxX_Hovering = MaxX_Box.IntersectInclusive(args.Position.Buffer.Corner).All(true);
		bool MaxY_Hovering = MaxY_Box.IntersectInclusive(args.Position.Buffer.Corner).All(true);

		if (MinX_Hovering || MaxX_Hovering || MinY_Hovering || MaxY_Hovering)
		{
			if (IsResizable)
			{
				if (MinX_Hovering && !(MinY_Hovering || MaxY_Hovering)) { ChangingBoxType = EChangingBoxType::ResizeMinX; }
				if (MaxX_Hovering && !(MinY_Hovering || MaxY_Hovering)) { ChangingBoxType = EChangingBoxType::ResizeMaxX; }
				if (MinY_Hovering && !(MinX_Hovering || MaxX_Hovering)) { ChangingBoxType = EChangingBoxType::ResizeMinY; }
				if (MaxY_Hovering && !(MinX_Hovering || MaxX_Hovering)) { ChangingBoxType = EChangingBoxType::ResizeMaxY; }
				if (MinX_Hovering && MinY_Hovering) { ChangingBoxType = EChangingBoxType::ResizeMinMin; }
				if (MinX_Hovering && MaxY_Hovering) { ChangingBoxType = EChangingBoxType::ResizeMinMax; }
				if (MaxX_Hovering && MinY_Hovering) { ChangingBoxType = EChangingBoxType::ResizeMaxMin; }
				if (MaxX_Hovering && MaxY_Hovering) { ChangingBoxType = EChangingBoxType::ResizeMaxMax; }
			}
		}
		else
		{
			if (IsMovable) { ChangingBoxType = EChangingBoxType::Move; }
		}
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
		BoxF2 MinX_Box(VectorF2(DisplayBox.Min.X, DisplayBox.Min.Y), VectorF2(DisplayBox.Min.X + AnchorBoarder.Min.X, DisplayBox.Max.Y));
		BoxF2 MaxX_Box(VectorF2(DisplayBox.Max.X - AnchorBoarder.Max.X, DisplayBox.Min.Y), VectorF2(DisplayBox.Max.X, DisplayBox.Max.Y));
		BoxF2 MinY_Box(VectorF2(DisplayBox.Min.X, DisplayBox.Min.Y), VectorF2(DisplayBox.Max.X, DisplayBox.Min.Y + AnchorBoarder.Min.Y));
		BoxF2 MaxY_Box(VectorF2(DisplayBox.Min.X, DisplayBox.Max.Y - AnchorBoarder.Max.Y), VectorF2(DisplayBox.Max.X, DisplayBox.Max.Y));

		bool MinX_Hovering = MinX_Box.IntersectInclusive(ControlManager -> CursorPosition).All(true);
		bool MinY_Hovering = MinY_Box.IntersectInclusive(ControlManager -> CursorPosition).All(true);
		bool MaxX_Hovering = MaxX_Box.IntersectInclusive(ControlManager -> CursorPosition).All(true);
		bool MaxY_Hovering = MaxY_Box.IntersectInclusive(ControlManager -> CursorPosition).All(true);

		bool none = true;
		if (MinX_Hovering || MaxX_Hovering || MinY_Hovering || MaxY_Hovering)
		{
			if (IsResizable)
			{
				if (MinX_Hovering && !(MinY_Hovering || MaxY_Hovering)) { ControlManager -> CursorsUseResizeH(); none = false; }
				if (MaxX_Hovering && !(MinY_Hovering || MaxY_Hovering)) { ControlManager -> CursorsUseResizeH(); none = false; }
				if (MinY_Hovering && !(MinX_Hovering || MaxX_Hovering)) { ControlManager -> CursorsUseResizeV(); none = false; }
				if (MaxY_Hovering && !(MinX_Hovering || MaxX_Hovering)) { ControlManager -> CursorsUseResizeV(); none = false; }
				if ((MinX_Hovering && MinY_Hovering) || (MaxX_Hovering && MaxY_Hovering)) { ControlManager -> CursorsUseResizeD0(); none = false; }
				if ((MaxX_Hovering && MinY_Hovering) || (MinX_Hovering && MaxY_Hovering)) { ControlManager -> CursorsUseResizeD1(); none = false; }
			}
		}
		/*else
		{
			if (IsMovable) { ControlManager -> CursorsUseCross(); none = false; }
		}*/
		if (none)
		{
			ControlManager -> CursorsUseDefault();
		}
	}
}
void UI::Control::Form::RelayCursorDrag(DragArgs args)
{
	UserChangingBox(args);
}
