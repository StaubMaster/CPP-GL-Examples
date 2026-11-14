#include "Test/TileGrid.hpp"



#include "User/MouseArgs.hpp"
void TestTileGrid::CheckBoxTile::ClickFunc(ClickArgs args)
{
	if (args.Action == Action::Press)
	{
		Func(Index);
	}
}



TestTileGrid::TestTileGrid()
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
			//CheckBoxGrid[y][x].CheckBox.Anchor.X.SetMarginMinDist(xf);
			//CheckBoxGrid[y][x].CheckBox.Anchor.Y.SetMarginMinDist(yf);
			CheckBoxGrid[y][x].CheckBox.MarginBox_Set_X_Min_Min(xf);
			CheckBoxGrid[y][x].CheckBox.MarginBox_Set_Y_Min_Min(yf);
			//xf = CheckBoxGrid[y][x].CheckBox.Anchor.X.AnchorMarginMin(xf);
			//yfn = CheckBoxGrid[y][x].CheckBox.Anchor.Y.AnchorMarginMin(yf);
			CheckBoxGrid[y][x].Index.X = x;
			CheckBoxGrid[y][x].Index.Y = y;
			CheckBoxGrid[y][x].CheckBox.ClickFunc.Assign(&CheckBoxGrid[y][x], &TestTileGrid::CheckBoxTile::ClickFunc);
			CheckBoxGrid[y][x].Func.Assign(this, &TestTileGrid::Func);
			//xf =  CheckBoxGrid[y][x].CheckBox.Anchor.X.GetMarginMinSize();
			//yfn = CheckBoxGrid[y][x].CheckBox.Anchor.Y.GetMarginMinSize();
			xf =  CheckBoxGrid[y][x].CheckBox.MarginBox_Get_X_Min_Max();
			yfn = CheckBoxGrid[y][x].CheckBox.MarginBox_Get_Y_Min_Max();
			ChildInsert(CheckBoxGrid[y][x].CheckBox);
		}
		yf = yfn;
	}
	AnchorSize.X = (xf + 15);
	AnchorSize.Y = (yf + 15);
}

#include <iostream>
#include "ValueType/_Show.hpp"
void TestTileGrid::Func(VectorU2 idx)
{
	if (idx.X != 0) { CheckBoxGrid[idx.Y][idx.X - 1].CheckBox.Toggle(); }
	if (idx.X != 6) { CheckBoxGrid[idx.Y][idx.X + 1].CheckBox.Toggle(); }
	if (idx.Y != 0) { CheckBoxGrid[idx.Y - 1][idx.X].CheckBox.Toggle(); }
	if (idx.Y != 6) { CheckBoxGrid[idx.Y + 1][idx.X].CheckBox.Toggle(); }
}
