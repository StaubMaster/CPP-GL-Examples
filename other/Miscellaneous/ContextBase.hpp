#ifndef  CONTEXT_BASE_HPP
# define CONTEXT_BASE_HPP

# include "DirectoryInfo.hpp"

# include "Window.hpp"
# include "Generics/Function/Object.hpp"

# include "Generics/Function/Static.hpp"

struct ContextBase
{
	static ::Window *							WindowPointer;
	static ::StaticFunction<::ContextBase*>		NewContext;

	static void		Quit();
	static void		Change(StaticFunction<ContextBase*>::FunctionType new_context);



	::Window &		window;
	DirectoryInfo	MediaDirectory;

	virtual ~ContextBase();
	ContextBase();

	virtual void	Init() = 0;
	virtual void	Free() = 0;

	virtual void	Resize(DisplaySize display_size) = 0;
	virtual void	Frame(FrameTime frame_time) = 0;

	virtual void	MouseMove(MoveArgs args) = 0;
	virtual void	MouseClick(ClickArgs args) = 0;
	virtual void	MouseScroll(ScrollArgs args) = 0;
	virtual void	MouseDrag(DragArgs args) = 0;
	virtual void	KeyBoardKey(KeyArgs args) = 0;
	virtual void	KeyBoardText(TextArgs args) = 0;

	void	Run();
};

#endif