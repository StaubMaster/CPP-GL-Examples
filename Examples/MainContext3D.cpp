#include "MainContext3D.hpp"

#include <iostream>
#include <sstream>

#include "DataShow.hpp"
#include "Debug.hpp"



MainContext3D::~MainContext3D() { }
MainContext3D::MainContext3D()
	: MediaDirectory("../../media/")
	, ImageDir(MediaDirectory.Child("Images"))
	, ShaderDir(MediaDirectory.Child("Shaders"))
	, PolyHedraDir(MediaDirectory.Child("YMT"))
	, TextDir(MediaDirectory.Child("Text"))
	, window()
	, Multiform_DisplaySize("DisplaySize")
	//, view(View3D::Default())
	, view()
{ }



// Update View Move Spin
//void MainContext3D::UpdateView(FrameTime frame_time)



void MainContext3D::Resize(const DisplaySize & Size)
{
	Multiform_DisplaySize.ChangeData(Size);
}

int MainContext3D::Run()
{
	window.InitCallBack.Change<MainContext3D>(this, &MainContext3D::Init);
	window.FreeCallBack.Change<MainContext3D>(this, &MainContext3D::Free);
	window.FrameCallBack.Change<MainContext3D>(this, &MainContext3D::Frame);
	window.ResizeCallBack.Change<MainContext3D>(this, &MainContext3D::Resize);

	window.MouseManager.Callback_ScrollEvent.Change(this, &MainContext3D::MouseScroll);
	window.MouseManager.Callback_ClickEvent.Change(this, &MainContext3D::MouseClick);
	window.MouseManager.Callback_DragEvent.Change(this, &MainContext3D::MouseDrag);

	window.KeyBoardManager.CallBack_KeyEvent.Change(this, &MainContext3D::KeyBoardKey);

	window.Create();
	Debug::Log << "<<<< Run Window" << Debug::Done;
	window.Run();
	Debug::Log << ">>>> Run Window" << Debug::Done;
	window.Delete();

	return 0;
}
