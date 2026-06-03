#include "Form.hpp"



UI::Control::Form::~Form()
{ }
UI::Control::Form::Form()
	: Base()
	, IsMovable(true)
	, IsResizableX(true)
	, IsResizableY(true)
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

		BoxF2 BoarderMinX_Box(VectorF2(DisplayBox.Min.X, DisplayBox.Min.Y), VectorF2(DisplayBox.Min.X + AnchorBoarder.Min.X, DisplayBox.Max.Y));
		BoxF2 BoarderMaxX_Box(VectorF2(DisplayBox.Max.X - AnchorBoarder.Max.X, DisplayBox.Min.Y), VectorF2(DisplayBox.Max.X, DisplayBox.Max.Y));
		BoxF2 BoarderMinY_Box(VectorF2(DisplayBox.Min.X, DisplayBox.Min.Y), VectorF2(DisplayBox.Max.X, DisplayBox.Min.Y + AnchorBoarder.Min.Y));
		BoxF2 BoarderMaxY_Box(VectorF2(DisplayBox.Min.X, DisplayBox.Max.Y - AnchorBoarder.Max.Y), VectorF2(DisplayBox.Max.X, DisplayBox.Max.Y));

		bool BoarderMinX_Hovering = BoarderMinX_Box.IntersectInclusive(args.Position.Buffer.Corner).All(true);
		bool BoarderMinY_Hovering = BoarderMinY_Box.IntersectInclusive(args.Position.Buffer.Corner).All(true);
		bool BoarderMaxX_Hovering = BoarderMaxX_Box.IntersectInclusive(args.Position.Buffer.Corner).All(true);
		bool BoarderMaxY_Hovering = BoarderMaxY_Box.IntersectInclusive(args.Position.Buffer.Corner).All(true);

		if (IsResizableX && (BoarderMinX_Hovering || BoarderMaxX_Hovering))
		{
			if (BoarderMinX_Hovering) { ChangingBoxType = EChangingBoxType::ResizeMinX; }
			if (BoarderMaxX_Hovering) { ChangingBoxType = EChangingBoxType::ResizeMaxX; }
		}
		else if (IsResizableY && (BoarderMinY_Hovering || BoarderMaxY_Hovering))
		{
			if (BoarderMinY_Hovering) { ChangingBoxType = EChangingBoxType::ResizeMinY; }
			if (BoarderMaxY_Hovering) { ChangingBoxType = EChangingBoxType::ResizeMaxY; }
		}
		else if (IsMovable) { ChangingBoxType = EChangingBoxType::Move; }
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
			ChangeAnchorBox(box);
		}
	}
	else if (args.Action == Action::Release)
	{
		ChangingBoxType = EChangingBoxType::None;
	}
}

void UI::Control::Form::RelayCursorDrag(DragArgs args)
{
	UserChangingBox(args);
}
