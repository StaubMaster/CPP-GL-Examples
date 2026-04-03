#ifndef  MAIN_CONTEXT_3D_HPP
# define MAIN_CONTEXT_3D_HPP

# include "DirectoryInfo.hpp"

# include "Window.hpp"
# include "Miscellaneous/Function/Object.hpp"

# include "FrameTime.hpp"

# include "Graphics/MultiformsInclude.hpp"
//# include "Graphics/Multiform/Trans3D.hpp"
//# include "Graphics/Multiform/Angle.hpp"

# include "ValueType/View3D.hpp"

struct MainContext3D
{
DirectoryInfo MediaDirectory;

Window	window;
Multiform::DisplaySize	Multiform_DisplaySize;

View3D	view;
//Multiform::Trans3D		Multiform_View;
//Multiform::Angle			Multiform_Scale;

virtual ~MainContext3D();
MainContext3D();

virtual void Make() = 0;

virtual void Init() = 0;
virtual void Free() = 0;



void UpdateView(FrameTime frame_time);



virtual void Frame(double timeDelta) = 0;

virtual void Resize(const DisplaySize & Size);

virtual void MouseScroll(ScrollArgs args) = 0;
virtual void MouseClick(ClickArgs args) = 0;
virtual void MouseDrag(DragArgs args) = 0;
virtual void KeyBoardKey(KeyArgs args) = 0;

int Run();
};

#endif