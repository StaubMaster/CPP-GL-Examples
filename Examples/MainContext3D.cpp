#include "MainContext3D.hpp"

#include <iostream>
#include <sstream>

#include "ValueTypeShow.hpp"
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



void MainContext3D::Resize(const DisplaySize & Size)
{
	Multiform_DisplaySize.ChangeData(Size);
}

int MainContext3D::Run()
{
	window.InitCallBack.Assign<MainContext3D>(this, &MainContext3D::Init);
	window.FreeCallBack.Assign<MainContext3D>(this, &MainContext3D::Free);
	window.FrameCallBack.Assign<MainContext3D>(this, &MainContext3D::Frame);
	window.ResizeCallBack.Assign<MainContext3D>(this, &MainContext3D::Resize);

	window.MouseManager.Callback_ScrollEvent.Assign(this, &MainContext3D::MouseScroll);
	window.MouseManager.Callback_ClickEvent.Assign(this, &MainContext3D::MouseClick);
	window.MouseManager.Callback_DragEvent.Assign(this, &MainContext3D::MouseDrag);

	window.KeyBoardManager.CallBack_KeyEvent.Assign(this, &MainContext3D::KeyBoardKey);

	window.Create();
	Debug::Log << "<<<< Run Window" << Debug::Done;
	window.Run();
	Debug::Log << ">>>> Run Window" << Debug::Done;
	window.Delete();

	return 0;
}
