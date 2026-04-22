#ifndef  CONTEXT_BASE_HPP
# define CONTEXT_BASE_HPP

# include "DirectoryInfo.hpp"

# include "Window.hpp"
# include "Miscellaneous/Function/Object.hpp"

// should Context to use and such be here ?
// as statics
// should window and MediaDirectory be Static ?

struct ContextBase
{
	static ::Window *		WindowPointer;
	static ::ContextBase *	ContextToUse;

	static void		Quit();
	static void		Change(ContextBase * context);

	static void		ChangeToContext0();
	static void		ChangeToContext1();
	static void		ChangeToNoisePlane();



	::Window &		window;
	DirectoryInfo	MediaDirectory;

	virtual ~ContextBase();
	ContextBase();

	virtual void	Init() = 0;
	virtual void	Free() = 0;

	virtual void	Resize(DisplaySize display_size) = 0;
	virtual void	Frame(FrameTime frame_time) = 0;

	virtual void	MouseScroll(ScrollArgs args) = 0;
	virtual void	MouseClick(ClickArgs args) = 0;
	virtual void	MouseDrag(DragArgs args) = 0;
	virtual void	KeyBoardKey(KeyArgs args) = 0;

	void	Run();
};

#endif