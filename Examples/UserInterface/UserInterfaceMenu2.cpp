#include "UserInterfaceMenu2.hpp"

void UserInterfaceMenu2::CheckBoxTile::ClickFunc(ClickArgs args)
{
	if (args.Action == Action::Press)
	{
		Func(Index);
	}
}

UserInterfaceMenu2::~UserInterfaceMenu2() { }
UserInterfaceMenu2::UserInterfaceMenu2()
	: UI::Control::Form()
{
	float yf = 0;
	float xf = 0;
	for (unsigned int y = 0; y < 7; y++)
	{
		xf = 0;
		float yfn;
		for (unsigned int x = 0; x < 7; x++)
		{
			CheckBoxGrid[y][x].CheckBox.Anchor.X.AnchorMin(xf);
			CheckBoxGrid[y][x].CheckBox.Anchor.Y.AnchorMin(yf);
			CheckBoxGrid[y][x].Index.X = x;
			CheckBoxGrid[y][x].Index.Y = y;
			CheckBoxGrid[y][x].CheckBox.ClickFunc.Assign(&CheckBoxGrid[y][x], &UserInterfaceMenu2::CheckBoxTile::ClickFunc);
			CheckBoxGrid[y][x].Func.Assign(this, &UserInterfaceMenu2::Func);
			xf = CheckBoxGrid[y][x].CheckBox.Anchor.X.GetMinSize();
			yfn = CheckBoxGrid[y][x].CheckBox.Anchor.Y.GetMinSize();
			ChildInsert(CheckBoxGrid[y][x].CheckBox);
		}
		yf = yfn;
	}
	Anchor.X.SetSize(xf + 15);
	Anchor.Y.SetSize(yf + 15);
}

#include <iostream>
#include "ValueType/_Show.hpp"
void UserInterfaceMenu2::Func(VectorU2 idx)
{
	if (idx.X != 0) { CheckBoxGrid[idx.Y][idx.X - 1].CheckBox.Toggle(); }
	if (idx.X != 6) { CheckBoxGrid[idx.Y][idx.X + 1].CheckBox.Toggle(); }
	if (idx.Y != 0) { CheckBoxGrid[idx.Y - 1][idx.X].CheckBox.Toggle(); }
	if (idx.Y != 6) { CheckBoxGrid[idx.Y + 1][idx.X].CheckBox.Toggle(); }
}
