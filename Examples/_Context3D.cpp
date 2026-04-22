#include "Context3D.hpp"

#include <iostream>
#include <sstream>

#include "ValueType/_Show.hpp"
#include "Debug.hpp"



Context3D::~Context3D() { }
Context3D::Context3D()
	: ContextBase()
	, Multiform_DisplaySize("DisplaySize")
	, view()
{ }



void Context3D::UpdateView(FrameTime frame_time)
{
	if (window.KeyBoardManager[Keys::Tab].State == State::Press) { window.MouseManager.CursorModeToggle(); }
	if (window.MouseManager.CursorModeIsLocked())
	{
		Trans3D trans = window.MoveSpinFromKeysCursor();
		if (window.KeyBoardManager[Keys::LeftControl].State == State::Down) { trans.Position *= 10; }
		trans.Position *= 2;
		trans.Rotation *= view.FOV.ToRadians() * 0.05f;
		view.ChangeFlatX(trans, frame_time.Delta);
	}
}



void Context3D::Resize(DisplaySize display_size)
{
	Multiform_DisplaySize.ChangeData(display_size);
}

/*int Context3D::Run()
{
	window.CallBack_Init.Assign<Context3D>(this, &Context3D::Init);
	window.CallBack_Free.Assign<Context3D>(this, &Context3D::Free);
	window.CallBack_Resize.Assign<Context3D>(this, &Context3D::Resize);
	window.CallBack_Frame.Assign<Context3D>(this, &Context3D::Frame);

	window.MouseManager.Callback_ScrollEvent.Assign(this, &Context3D::MouseScroll);
	window.MouseManager.Callback_ClickEvent.Assign(this, &Context3D::MouseClick);
	window.MouseManager.Callback_DragEvent.Assign(this, &Context3D::MouseDrag);

	window.KeyBoardManager.CallBack_KeyEvent.Assign(this, &Context3D::KeyBoardKey);

	window.Create();
	Debug::Log << "<<<< Run Window" << Debug::Done;
	window.RunLoop();
	Debug::Log << ">>>> Run Window" << Debug::Done;
	window.Delete();

	return 0;
}*/
