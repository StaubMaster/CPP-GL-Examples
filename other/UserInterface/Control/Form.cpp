#include "Form.hpp"



UI::Control::Form::~Form()
{ }
UI::Control::Form::Form()
{
	Depth = 0.9f;
	Anchor.X.Anchor = AnchorType::None;
	Anchor.Y.Anchor = AnchorType::None;
	AnchorSize = VectorF2(480, 360);
	AnchorNormal = VectorF2(0.5, 0.5);
	ColorDefault = ColorF4(0.75f, 0.75f, 0.75f);
	ColorHover = ColorF4(0.75f, 0.75f, 0.75f);

	IsMovable = true;
	IsMoving = false;

	IsResizableX = true;
	IsResizableY = true;
	IsResizing = false;
}



void UI::Control::Form::UserMoving(DragArgs args)
{
	if (args.Action == Action::Press)
	{
		MovingRel.Min = args.Position.Buffer.Corner - DisplayBox.Min;
		MovingRel.Max = args.Position.Buffer.Corner - DisplayBox.Max;

		if (IsMovable) { IsMoving = true; }
	}
	else if (args.Action == Action::Repeat)
	{
		if (IsMoving)
		{
			ChangeAnchorBox(BoxF2(
				args.Position.Buffer.Corner - MovingRel.Min,
				args.Position.Buffer.Corner - MovingRel.Max
			));
		}
	}
	else if (args.Action == Action::Release)
	{
		IsMoving = false;
	}
}
void UI::Control::Form::UserResize(DragArgs args)
{
	if (args.Action == Action::Press)
	{
		BoarderRel.Min = args.Position.Buffer.Corner - DisplayBox.Min;
		BoarderRel.Max = args.Position.Buffer.Corner - DisplayBox.Max;

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
			if (BoarderMinX_Hovering) { Boarder = 0b00; IsResizing = true; }
			if (BoarderMaxX_Hovering) { Boarder = 0b01; IsResizing = true; }
		}
		else if (IsResizableY && (BoarderMinY_Hovering || BoarderMaxY_Hovering))
		{
			if (BoarderMinY_Hovering) { Boarder = 0b10; IsResizing = true; }
			if (BoarderMaxY_Hovering) { Boarder = 0b11; IsResizing = true; }
		}
	}
	else if (args.Action == Action::Repeat)
	{
		if (IsResizing)
		{
			BoxF2 box = DisplayBox;
			if (Boarder == 0b00) { box.Min.X = args.Position.Buffer.Corner.X; }
			if (Boarder == 0b01) { box.Max.X = args.Position.Buffer.Corner.X; }
			if (Boarder == 0b10) { box.Min.Y = args.Position.Buffer.Corner.Y; }
			if (Boarder == 0b11) { box.Max.Y = args.Position.Buffer.Corner.Y; }
			ChangeAnchorBox(box);
		}
	}
	else if (args.Action == Action::Release)
	{
		IsResizing = false;
	}
}

void UI::Control::Form::RelayCursorDrag(DragArgs args)
{
	//UpdateMoving(args);
	UserResize(args);
}
