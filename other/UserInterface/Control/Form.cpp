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
		std::cout << "Moving Press\n";
		std::cout << "Pos " << args.Position.Buffer.Corner << '\n';
		MovingRel.Min = args.Position.Buffer.Corner - DisplayBox.Min;
		MovingRel.Max = args.Position.Buffer.Corner - DisplayBox.Max;
		std::cout << "Rel " << MovingRel << '\n';
	}
	else if (args.Action == Action::Repeat)
	{
		std::cout << "Moving Repeat\n";
		std::cout << "Pos " << args.Position.Buffer.Corner << '\n';
		std::cout << "Rel " << MovingRel << '\n';
		DisplayBox.Min = MovingRel.Min + args.Position.Buffer.Corner;
		DisplayBox.Max = MovingRel.Max + args.Position.Buffer.Corner;
		ContainerBox.Min = DisplayBox.Min + AnchorBoarder.Min + AnchorPadding.Min;
		ContainerBox.Max = DisplayBox.Max - AnchorBoarder.Max - AnchorPadding.Max;
		ObjectBoxNeedAssign = true;
	}
	else if (args.Action == Action::Release)
	{
		std::cout << "Moving Release\n";
	}
}

void UI::Control::Form::RelayCursorDrag(DragArgs args)
{
	UpdateMoving(args);
}
