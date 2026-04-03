#include "MainContext2D.hpp"

#include <iostream>
#include <sstream>

#include "DataShow.hpp"
#include "Debug.hpp"



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
		if (window.KeyBoardManager[Keys::Q].State == State::Down) { trans.Rot.Ang += Angle::Degrees(45); }
		if (window.KeyBoardManager[Keys::E].State == State::Down) { trans.Rot.Ang -= Angle::Degrees(45); }
		view.Change(trans, frame_time.Delta);
	}
	Multiform_View.ChangeData(view.Trans);
	Multiform_Scale.ChangeData(view.Scale);
}
void MainContext2D::UpdateViewZoom(ScrollArgs args)
{
	Point2D cursor_rel = window.Size.Convert(window.MouseManager.CursorPosition());
	Point2D cursor_abs = view.forward(cursor_rel);

	if (args.Y < 0.0f) { while (args.Y < 0.0f) { view.Scale *= 2; args.Y++; } }
	if (args.Y > 0.0f) { while (args.Y > 0.0f) { view.Scale /= 2; args.Y--; } }

	#define ZOOM_MIN 1.0 / (1 << 6)
	#define ZOOM_MAX 1.0 * (1 << 6)

	if (view.Scale <= ZOOM_MIN) { view.Scale = ZOOM_MIN; }
	if (view.Scale >= ZOOM_MAX) { view.Scale = ZOOM_MAX; }

	view.Trans.Pos = cursor_abs - (view.Trans.Rot * (cursor_rel * view.Scale));
}

Point2D DragAnchorRelative;
Point2D DragAnchorAbsolute;
void MainContext2D::UpdateViewDrag(DragArgs args)
{	
	if (args.Button == MouseButtons::MouseM)
	{
		if (args.Action == Action::Press)
		{
			DragAnchorRelative = window.Size.Convert(args.Position);
			DragAnchorAbsolute = view.forward(DragAnchorRelative);
		}

		if (args.Action == Action::Repeat)
		{
			Point2D target_rel = window.Size.Convert(args.Position);
			view.Trans.Pos = DragAnchorAbsolute - (view.Trans.Rot * (target_rel * view.Scale));
		}
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

	window.MouseManager.Callback_ScrollEvent.Change(this, &MainContext2D::MouseScroll);
	window.MouseManager.Callback_ClickEvent.Change(this, &MainContext2D::MouseClick);
	window.MouseManager.Callback_DragEvent.Change(this, &MainContext2D::MouseDrag);

	window.KeyBoardManager.CallBack_KeyEvent.Change(this, &MainContext2D::KeyBoardKey);

	window.Create();
	Debug::Log << "<<<< Run Window" << Debug::Done;
	window.Run();
	Debug::Log << ">>>> Run Window" << Debug::Done;
	window.Delete();

	return 0;
}
