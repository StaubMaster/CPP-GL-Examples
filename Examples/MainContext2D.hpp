#ifndef  MAIN_CONTEXT_2D_HPP
# define MAIN_CONTEXT_2D_HPP

# include "DirectoryInfo.hpp"

# include "Window.hpp"
# include "Function/Object.hpp"
# include "UserParameter/KeyBoardInclude.hpp"
# include "UserParameter/MouseInclude.hpp"

# include "FrameTime.hpp"

# include "Graphics/MultiformsInclude.hpp"
# include "Graphics/Multiform/Trans2D.hpp"
# include "Graphics/Multiform/Float.hpp"

# include "ValueType/View2D.hpp"

struct MainContext2D
{
DirectoryInfo MediaDirectory;
DirectoryInfo ImageDir;
DirectoryInfo ShaderDir;
DirectoryInfo PolyHedraDir;
DirectoryInfo TextDir;

Window	window;
Multiform::DisplaySize	Multiform_DisplaySize;

View2D	view;
Multiform::Trans2D		Multiform_View;
Multiform::Float		Multiform_Scale;

virtual ~MainContext2D();
MainContext2D();

virtual void Make() = 0;

virtual void Init() = 0;
virtual void Free() = 0;



// Update View Move Spin
void UpdateView(FrameTime frame_time);
void UpdateViewZoom(ScrollArgs args);
void UpdateViewDrag(DragArgs args);



/* Frame
	Change (Input)
	Update
	Draw (Output)
*/
virtual void Frame(double timeDelta) = 0;

void Resize(const DisplaySize & Size);

//virtual void MouseScroll(UserParameter::Mouse::Scroll params) = 0;
//virtual void MouseClick(UserParameter::Mouse::Click params) = 0;
//virtual void MouseDrag(UserParameter::Mouse::Drag params) = 0;
//virtual void KeyBoardKey(UserParameter::KeyBoard::Key params) = 0;
virtual void MouseScroll(ScrollArgs args) = 0;
virtual void MouseClick(ClickArgs args) = 0;
virtual void MouseDrag(DragArgs args) = 0;
virtual void KeyBoardKey(KeyArgs args) = 0;

int Run();
};

#endif