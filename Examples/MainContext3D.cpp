#include "MainContext3D.hpp"

#include <iostream>
#include <sstream>

#include "ValueType/_Show.hpp"
#include "Debug.hpp"



MainContext3D::~MainContext3D() { }
MainContext3D::MainContext3D()
	: MediaDirectory("../../media/")
	, window()
	, Multiform_DisplaySize("DisplaySize")
	, view()
{ }



void MainContext3D::UpdateView(FrameTime frame_time)
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



void MainContext3D::Resize(DisplaySize display_size)
{
	Multiform_DisplaySize.ChangeData(display_size);
}

int MainContext3D::Run()
{
	window.CallBack_Init.Assign<MainContext3D>(this, &MainContext3D::Init);
	window.CallBack_Free.Assign<MainContext3D>(this, &MainContext3D::Free);
	window.CallBack_Resize.Assign<MainContext3D>(this, &MainContext3D::Resize);
	window.CallBack_Frame.Assign<MainContext3D>(this, &MainContext3D::Frame);

	window.MouseManager.Callback_ScrollEvent.Assign(this, &MainContext3D::MouseScroll);
	window.MouseManager.Callback_ClickEvent.Assign(this, &MainContext3D::MouseClick);
	window.MouseManager.Callback_DragEvent.Assign(this, &MainContext3D::MouseDrag);

	window.KeyBoardManager.CallBack_KeyEvent.Assign(this, &MainContext3D::KeyBoardKey);

	window.Create();
	Debug::Log << "<<<< Run Window" << Debug::Done;
	window.RunLoop();
	Debug::Log << ">>>> Run Window" << Debug::Done;
	window.Delete();

	return 0;
}
