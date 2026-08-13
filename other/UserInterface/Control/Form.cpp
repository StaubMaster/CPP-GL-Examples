#include "Control/Form.hpp"
#include "UIManager.hpp"



UI::Control::Form::~Form()
{ }
UI::Control::Form::Form()
	: Base()
	, IsMovable(true)
	, IsResizable(true)
	, ChangingBoxType(EBoxChangeType::None)
{
	// give this stuff to Base ?
	Anchor.X.Anchor = AnchorType::None;
	Anchor.Y.Anchor = AnchorType::None;
	AnchorSize = VectorF2(480, 360);
	AnchorNormal = VectorF2(0.5, 0.5);
	ColorDefault = ColorF4(0.75f, 0.75f, 0.75f);
	ColorHover = ColorF4(0.75f, 0.75f, 0.75f);
}



UI::Control::Form::EBoxChangeType UI::Control::Form::FindChangingArea(VectorF2 mouse) const
{
	BoxF2 BoxBoarder;
	BoxBoarder.Min = BoxDisplay.Min + 10.0f;
	BoxBoarder.Max = BoxDisplay.Max - 10.0f;

	BoxF2 MinX_Box(VectorF2(BoxDisplay.Min.X, BoxDisplay.Min.Y), VectorF2(BoxBoarder.Min.X, BoxDisplay.Max.Y));
	BoxF2 MaxX_Box(VectorF2(BoxBoarder.Max.X, BoxDisplay.Min.Y), VectorF2(BoxDisplay.Max.X, BoxDisplay.Max.Y));
	BoxF2 MinY_Box(VectorF2(BoxDisplay.Min.X, BoxDisplay.Min.Y), VectorF2(BoxDisplay.Max.X, BoxBoarder.Min.Y));
	BoxF2 MaxY_Box(VectorF2(BoxDisplay.Min.X, BoxBoarder.Max.Y), VectorF2(BoxDisplay.Max.X, BoxDisplay.Max.Y));

	bool MinX_Hovering = MinX_Box.IntersectInclusive(mouse).All(true);
	bool MinY_Hovering = MinY_Box.IntersectInclusive(mouse).All(true);
	bool MaxX_Hovering = MaxX_Box.IntersectInclusive(mouse).All(true);
	bool MaxY_Hovering = MaxY_Box.IntersectInclusive(mouse).All(true);

	if (MinX_Hovering || MaxX_Hovering || MinY_Hovering || MaxY_Hovering)
	{
		if (IsResizable)
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
	}
	else
	{
		if (IsMovable)
		{
			return EBoxChangeType::Move;
		}
	}
	return EBoxChangeType::None;
}

void UI::Control::Form::ChangeAnchorBox(BoxF2 box, EBoxChangeType type)
{
	if (type == EBoxChangeType::None) { return; }
	if (Parent != nullptr)
	{
		// when moving, keep size
		// when resizing, keep other side

		BoxF2 other_box;
		other_box.Min = (Parent -> BoxContent.Min) + AnchorMargin.Min;
		other_box.Max = (Parent -> BoxContent.Max) - AnchorMargin.Max;

		Bool2 limit_min = box.Min <= other_box.Min;
		Bool2 limit_max = box.Max >= other_box.Max;

		AnchorType anchor_type_x = Anchor.X.Anchor;
		AnchorType anchor_type_y = Anchor.Y.Anchor;

		if (type != EBoxChangeType::Move)
		{
			if      ( limit_min.GetX() &&  limit_max.GetX()) { anchor_type_x = AnchorType::Both; box.Min.X = other_box.Min.X; box.Max.X = other_box.Max.X; }
			else if ( limit_min.GetX() && !limit_max.GetX()) { anchor_type_x = AnchorType::Min;  box.Min.X = other_box.Min.X;                              }
			else if (!limit_min.GetX() &&  limit_max.GetX()) { anchor_type_x = AnchorType::Max;  box.Max.X = other_box.Max.X;                              }

			if      ( limit_min.GetY() &&  limit_max.GetY()) { anchor_type_y = AnchorType::Both; box.Min.Y = other_box.Min.Y; box.Max.Y = other_box.Max.Y; }
			else if ( limit_min.GetY() && !limit_max.GetY()) { anchor_type_y = AnchorType::Min;  box.Min.Y = other_box.Min.Y;                              }
			else if (!limit_min.GetY() &&  limit_max.GetY()) { anchor_type_y = AnchorType::Max;  box.Max.Y = other_box.Max.Y;                              }
		}
		else
		{
			VectorF2 size = box.Max - box.Min;

			if      ( limit_min.GetX() &&  limit_max.GetX()) { anchor_type_x = AnchorType::Both; box.Min.X = other_box.Min.X; box.Max.X = other_box.Max.X;    }
			else if ( limit_min.GetX() && !limit_max.GetX()) { anchor_type_x = AnchorType::Min;  box.Min.X = other_box.Min.X; box.Max.X = box.Min.X + size.X; }
			else if (!limit_min.GetX() &&  limit_max.GetX()) { anchor_type_x = AnchorType::Max;  box.Max.X = other_box.Max.X; box.Min.X = box.Max.X - size.X; }

			if      ( limit_min.GetY() &&  limit_max.GetY()) { anchor_type_y = AnchorType::Both; box.Min.Y = other_box.Min.Y; box.Max.Y = other_box.Max.Y;    }
			else if ( limit_min.GetY() && !limit_max.GetY()) { anchor_type_y = AnchorType::Min;  box.Min.Y = other_box.Min.Y; box.Max.Y = box.Min.Y + size.Y; }
			else if (!limit_min.GetY() &&  limit_max.GetY()) { anchor_type_y = AnchorType::Max;  box.Max.Y = other_box.Max.Y; box.Min.Y = box.Max.Y - size.Y; }
		}

		Anchor.X.Anchor = anchor_type_x;
		Anchor.Y.Anchor = anchor_type_y;
		Anchor.Calculate(Parent -> BoxContent, box);
		BoxUpdateRequest();
	}
}



#include "Control/General/Manager.hpp"
/* put into Manager
	Cursors flicked when moving
	put into Manager, Cursor should stay the same until changing ends
	dont do any Events (drag/move) while changing
*/
void UI::Control::Form::RelayHover(HoverArgs args)
{
	/*if (args == HoverArgs::Enter)
	{
		Manager -> CursorsUseResizeH();
	}*/
	if (args.Type == HoverType::Leave)
	{
		Manager -> CursorsUseDefault();
	}
	if (args.Type == HoverType::Move)
	{
		EBoxChangeType type = FindChangingArea(Manager -> CursorPosition);
		if (type == EBoxChangeType::Move) { Manager -> CursorsUseDefault(); }
		else if (type == EBoxChangeType::ResizeMinX) { Manager -> CursorsUseBoxEdge(0); }
		else if (type == EBoxChangeType::ResizeMinY) { Manager -> CursorsUseBoxEdge(1); }
		else if (type == EBoxChangeType::ResizeMaxX) { Manager -> CursorsUseBoxEdge(2); }
		else if (type == EBoxChangeType::ResizeMaxY) { Manager -> CursorsUseBoxEdge(3); }
		else if (type == EBoxChangeType::ResizeMinMin) { Manager -> CursorsUseBoxCorn(0); }
		else if (type == EBoxChangeType::ResizeMaxMin) { Manager -> CursorsUseBoxCorn(1); }
		else if (type == EBoxChangeType::ResizeMinMax) { Manager -> CursorsUseBoxCorn(2); }
		else if (type == EBoxChangeType::ResizeMaxMax) { Manager -> CursorsUseBoxCorn(3); }
		else { Manager -> CursorsUseDefault(); }
	}
}
void UI::Control::Form::RelayDrag(DragArgs args)
{
	if (args.Action == Action::Press)
	{
		ChangingBoxRel.Min = args.Position.Buffer.Corner - BoxDisplay.Min;
		ChangingBoxRel.Max = args.Position.Buffer.Corner - BoxDisplay.Max;

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
			BoxF2 box = BoxDisplay;
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
