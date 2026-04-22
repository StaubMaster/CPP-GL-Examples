#ifndef  MAIN_CONTEXT_3D_HPP
# define MAIN_CONTEXT_3D_HPP

# include "DirectoryInfo.hpp"

# include "Window.hpp"
# include "Miscellaneous/Function/Object.hpp"

# include "Graphics/Multiform/_Include.hpp"

# include "ValueType/View3D.hpp"

# include "ContextBase.hpp"

struct Context3D : public ContextBase
{
//DirectoryInfo MediaDirectory;
//Window	window;

Multiform::DisplaySize	Multiform_DisplaySize;

View3D	view;
//Multiform::Trans3D		Multiform_View;
//Multiform::Angle			Multiform_Scale;

virtual ~Context3D();
Context3D();

virtual void Make() = 0;

virtual void Init() = 0;
virtual void Free() = 0;



void UpdateView(FrameTime frame_time);



virtual void Resize(DisplaySize display_size);
virtual void Frame(FrameTime frame_time) = 0;

virtual void MouseScroll(ScrollArgs args) = 0;
virtual void MouseClick(ClickArgs args) = 0;
virtual void MouseDrag(DragArgs args) = 0;
virtual void KeyBoardKey(KeyArgs args) = 0;

//int Run();
};

#endif