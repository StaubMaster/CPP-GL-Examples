#include "MainContext2D.hpp"

#include <iostream>
#include <sstream>

#include "DataShow.hpp"
#include "Debug.hpp"

#include "Arrow2D/Object.hpp"



MainContext2D::~MainContext2D() { }
MainContext2D::MainContext2D()
	: MediaDirectory("../../media/")
	, ImageDir(MediaDirectory.Child("Images"))
	, ShaderDir(MediaDirectory.Child("Shaders"))
	, PolyHedraDir(MediaDirectory.Child("YMT"))
	, TextDir(MediaDirectory.Child("Text"))
	, window()
	, Multiform_DisplaySize("DisplaySize")
	, view(View2D::Default())
	, Multiform_View("View")
	, Multiform_Scale("Scale")
{ }



// Update View Move Spin
void MainContext2D::UpdateView(FrameTime frame_time)
{
	{
		Trans2D trans;
		Point3D move3D = window.MoveFromKeys();
		trans.Pos = Point2D(move3D.X, move3D.Z) * 2.0f * view.Scale;
		if (window.KeyBoardManager.Keys[UserParameter::KeyBoard::Keys::Q.Flags].IsDown()) { trans.Rot.Ang += Angle::Degrees(45); }
		if (window.KeyBoardManager.Keys[UserParameter::KeyBoard::Keys::E.Flags].IsDown()) { trans.Rot.Ang -= Angle::Degrees(45); }
		view.Change(trans, frame_time.Delta);
	}
	Multiform_View.ChangeData(view.Trans);
	Multiform_Scale.ChangeData(view.Scale);
}
void MainContext2D::UpdateViewZoom(UserParameter::Mouse::Scroll params)
{
	Point2D cursor_rel = window.Size.Convert(window.MouseManager.CursorPosition());
	Point2D cursor_abs = view * cursor_rel;

	if (params.Y < 0.0f) { while (params.Y < 0.0f) { view.Scale *= 2; params.Y++; } }
	if (params.Y > 0.0f) { while (params.Y > 0.0f) { view.Scale /= 2; params.Y--; } }

	#define ZOOM_MIN 1.0 / (1 << 6)
	#define ZOOM_MAX 1.0 * (1 << 6)

	if (view.Scale <= ZOOM_MIN) { view.Scale = ZOOM_MIN; }
	if (view.Scale >= ZOOM_MAX) { view.Scale = ZOOM_MAX; }

	view.Trans.Pos = cursor_abs - (view.Trans.Rot * (cursor_rel * view.Scale));
}

Point2D DragAnchorRelative;
Point2D DragAnchorAbsolute;
void MainContext2D::UpdateViewDrag(UserParameter::Mouse::Click params)
{
	if (params.Code == UserParameter::Mouse::Button::MouseL)
	{
		if (params.Action.IsPress())
		{
			DragAnchorRelative = window.Size.Convert(params.Position);
			DragAnchorAbsolute = view * DragAnchorRelative;
		}
	}
}
void MainContext2D::UpdateViewDrag(UserParameter::Mouse::Drag params)
{
	std::cout << "param: " << params.Code.Flags << '\n';
	std::cout << "param: " << UserParameter::Mouse::Button::MouseL.Flags << '\n';
	std::cout << "param: " << UserParameter::Mouse::Button::MouseR.Flags << '\n';
	std::cout << "param: " << UserParameter::Mouse::Button::MouseM.Flags << '\n';
	std::cout << '\n';

	if (params.Code == UserParameter::Mouse::Button::MouseL)
	{
		Point2D target_rel = window.Size.Convert(params.Position);
		view.Trans.Pos = DragAnchorAbsolute - (view.Trans.Rot * (target_rel * view.Scale));
	}
}



void MainContext2D::Resize(const DisplaySize & Size)
{
	Multiform_DisplaySize.ChangeData(Size);
}

int MainContext2D::Run()
{
	window.InitCallBack.Change<MainContext2D>(this, &MainContext2D::Init);
	window.FreeCallBack.Change<MainContext2D>(this, &MainContext2D::Free);
	window.FrameCallBack.Change<MainContext2D>(this, &MainContext2D::Frame);
	window.ResizeCallBack.Change<MainContext2D>(this, &MainContext2D::Resize);

	window.MouseManager.CallbackScroll.Change(this, &MainContext2D::MouseScroll);
	window.MouseManager.CallbackClick.Change(this, &MainContext2D::MouseClick);
	window.MouseManager.CallbackDrag.Change(this, &MainContext2D::MouseDrag);

	window.KeyBoardManager.KeyCallBack.Change(this, &MainContext2D::KeyBoardKey);

	view.Scale = 1.0f;

	window.Create();
	Debug::Log << "<<<< Run Window" << Debug::Done;
	window.Run();
	Debug::Log << ">>>> Run Window" << Debug::Done;
	window.Delete();

	return 0;
}
