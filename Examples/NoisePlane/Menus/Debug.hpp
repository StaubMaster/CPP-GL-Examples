#ifndef  DEBUG_MENU_HPP
# define DEBUG_MENU_HPP

# include "Control/Base/Manager.hpp"
# include "ControlsInclude.hpp"

struct CheckBoxText
{
	UI::Control::TextBox	Text;
	UI::Control::CheckBox	Check;
	float	Place(float y, const char * str);
	void	Insert(UI::Control::Form & form);
};

struct DebugMenu : public UI::Control::Form
{
	CheckBoxText	FPS;

	CheckBoxText	View;
	CheckBoxText	ChunkHere;
	CheckBoxText	VoxelThere;

	CheckBoxText	VoxelChunkMemory;
	CheckBoxText	VoxelChunkBoxes;

	CheckBoxText	ViewCollisionVoxels;

	~DebugMenu();
	DebugMenu();
};

#endif