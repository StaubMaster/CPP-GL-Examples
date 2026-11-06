#ifndef  USER_INTERFACE_TEST_TILE_GRID_HPP
# define USER_INTERFACE_TEST_TILE_GRID_HPP

# include "Control/_Include.hpp"

struct TestTileGrid : public UI::Control::Form
{
	//UI::Control::CheckBox		CheckBoxGrid[7][7];

	// this is a workaround
	// Callback Functions should get a Pointer/Referance to the Control/Invoker
	// put inside args or have it as a seperate Peremeter ?
	// C# has it as a seperate Parameter
	struct	CheckBoxTile
	{
		UI::Control::CheckBox		CheckBox;
		VectorU2					Index;
		Function::Pointer<VectorU2>	Func;
		void	ClickFunc(ClickArgs args);
	};
	CheckBoxTile	CheckBoxGrid[7][7];

	TestTileGrid();

	void	Func(VectorU2 idx);
};

#endif