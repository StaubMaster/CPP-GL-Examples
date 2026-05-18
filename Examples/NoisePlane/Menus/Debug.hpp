#ifndef  DEBUG_MENU_HPP
# define DEBUG_MENU_HPP

# include "Control/Base/Manager.hpp"
# include "ControlsInclude.hpp"

struct ContextNoisePlane;

struct CheckBoxText
{
	UI::Control::Label		Label;
	UI::Control::CheckBox	Check;
	float	Place(float y, const char * str);
	void	Insert(UI::Control::Form & form);
};

struct DebugMenu : public UI::Control::Form
{
	ContextNoisePlane &		Context;

	CheckBoxText	FPS;

	CheckBoxText	TimeThreads;
	CheckBoxText	TimeWaitDo;

	CheckBoxText	AuxThread0Idle;
	CheckBoxText	AuxThread1Idle;
	CheckBoxText	AuxThread2Idle;

	CheckBoxText	View;
	CheckBoxText	ChunkHere;
	CheckBoxText	VoxelThere;

	CheckBoxText	ChunkRange;
	CheckBoxText	ChunkRangeCenter;

	CheckBoxText	VoxelChunkMemory;
	CheckBoxText	VoxelChunkBoxes;

	CheckBoxText	ViewCollisionVoxels;

	UI::Control::Slider		Generation3DFactor;
	UI::Control::Slider		Generation3DComparison;

	~DebugMenu();
	DebugMenu(ContextNoisePlane & context);
};

#endif