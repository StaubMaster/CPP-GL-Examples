#ifndef  CONTEXT_BASE_HPP
# define CONTEXT_BASE_HPP

# include "DirectoryInfo.hpp"

# include "Window.hpp"
# include "Miscellaneous/Function/Object.hpp"

struct ContextBase
{
	::Window & window;
	DirectoryInfo MediaDirectory;

	virtual ~ContextBase();
	ContextBase(::Window & window);

	virtual void Init() = 0;
	virtual void Free() = 0;

	virtual void Resize(DisplaySize display_size) = 0;
	virtual void Frame(FrameTime frame_time) = 0;

	virtual void MouseScroll(ScrollArgs args) = 0;
	virtual void MouseClick(ClickArgs args) = 0;
	virtual void MouseDrag(DragArgs args) = 0;
	virtual void KeyBoardKey(KeyArgs args) = 0;
};

#endif