#ifndef  OPTIONS_MENU_HPP
# define OPTIONS_MENU_HPP

# include "Control/General/Manager.hpp"
# include "ControlsInclude.hpp"

struct ContextNoisePlane;

struct OptionsMenu : public UI::Control::Form
{
	ContextNoisePlane &		Context;

	UI::Control::Slider		FPS;
	UI::Control::Slider		FOV;
	UI::Control::Slider		Depth;
	UI::Control::Slider		DepthRange;
	UI::Control::Slider		ChunkInsert;
	UI::Control::Slider		ChunkRemove;
	UI::Control::Button		Back;

	~OptionsMenu();
	OptionsMenu(ContextNoisePlane & context);

	void	FPSFunc(float val);
	void	FOVFunc(float val);
	void	DepthFunc(float val);
	void	DepthRangeFunc(float val);
	void	Chunk_InsertFunc(float val);
	void	Chunk_RemoveFunc(float val);
	void	BackFunc(ClickArgs args);
};

#endif