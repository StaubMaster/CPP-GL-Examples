#ifndef  USER_INTERFACE_MENU_2_HPP
# define USER_INTERFACE_MENU_2_HPP

# include "ControlsInclude.hpp"

struct UserInterfaceMenu2 : public UI::Control::Form
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
		FunctionPointer<VectorU2>	Func;
		void	ClickFunc(ClickArgs args);
	};
	CheckBoxTile	CheckBoxGrid[7][7];

	~UserInterfaceMenu2();
	UserInterfaceMenu2();

	void	Func(VectorU2 idx);
};

#endif