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

	IsResizableX = false;
	IsResizableY = false;
}



#include <iostream>
#include "ValueType/_Show.hpp"
void UI::Control::Form::UpdateMoving(DragArgs args)
{
	
	if (args.Action == Action::Press)
	{
		if (IsMovable)
		{
			MovingRel.Min = args.Position.Buffer.Corner - DisplayBox.Min;
			MovingRel.Max = args.Position.Buffer.Corner - DisplayBox.Max;
			IsMoving = true;
		}
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

void UI::Control::Form::RelayCursorDrag(DragArgs args)
{
	UpdateMoving(args);
}
