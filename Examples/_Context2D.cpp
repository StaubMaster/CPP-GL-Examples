#include "Context2D.hpp"
#include "Miscellaneous/Function/Object.hpp"

#include <iostream>
#include <sstream>

#include "ValueType/_Show.hpp"
#include "Debug.hpp"

#include "ValueType/Matrix3x3.hpp"
#include "ValueType/Point3D.hpp"



Context2D::~Context2D() { }
Context2D::Context2D()
	: MediaDirectory("../../media/")
	, window()
	, Multiform_DisplaySize("DisplaySize")
	, view(View2D::Default())
	, Multiform_View("View")
	, Multiform_Scale("Scale")
	, PolyGonManager()
{
	PolyGonManager.MakeCurrent();
}

void Context2D::mMake()
{
	GL::Disable(GL::Capability::DepthTest);
	GL::Disable(GL::Capability::CullFace);
	Make();
}
void Context2D::mInit()
{
	mMake();
	PolyGonManager.InitExternal(MediaDirectory);
	PolyGonManager.GraphicsCreate();
	PolyGonManager.InitInternal();
	Init();
}
void Context2D::mFree()
{
	Free();
	PolyGonManager.GraphicsDelete();
}

// Update View Move Spin
void Context2D::UpdateView(FrameTime frame_time)
{
	{
		Trans2D trans;
		Point3D move3D = window.MoveFromKeys();
		trans.Pos = Point2D(move3D.X, move3D.Z) * 2.0f * view.Scale;
		if (window.KeyBoardManager[Keys::Q].State == State::Down) { trans.Rot += Angle::Degrees(45); }
		if (window.KeyBoardManager[Keys::E].State == State::Down) { trans.Rot -= Angle::Degrees(45); }
		view.Change(trans, frame_time.Delta);
	}
	Multiform_View.ChangeData(view.Trans);
	Multiform_Scale.ChangeData(view.Scale);
}
void Context2D::UpdateViewZoom(ScrollArgs args)
{
	Point2D cursor_rel = window.Size.Convert(window.MouseManager.CursorPosition());
	Point2D cursor_abs = view.forward(cursor_rel);

	if (args.Y < 0.0f) { while (args.Y < 0.0f) { view.Scale *= 2; args.Y++; } }
	if (args.Y > 0.0f) { while (args.Y > 0.0f) { view.Scale /= 2; args.Y--; } }

	#define ZOOM_MIN 1.0 / (1 << 6)
	#define ZOOM_MAX 1.0 * (1 << 6)

	if (view.Scale <= ZOOM_MIN) { view.Scale = ZOOM_MIN; }
	if (view.Scale >= ZOOM_MAX) { view.Scale = ZOOM_MAX; }

	view.Trans.Pos = cursor_abs - (view.Trans.Rot.forward(cursor_rel * view.Scale));
}

Point2D DragAnchorRelative;
Point2D DragAnchorAbsolute;
void Context2D::UpdateViewDrag(DragArgs args)
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
			view.Trans.Pos = DragAnchorAbsolute - (view.Trans.Rot.forward(target_rel * view.Scale));
		}
	}
}



void Context2D::mDraw()
{
	PolyGonManager.ClearInstances();
	PolyGonManager.Update();
	{
		PolyGonManager.ShaderFullDefault.Bind();
		PolyGonManager.ShaderFullDefault.DisplaySize.Put(window.Size);
		PolyGonManager.ShaderFullDefault.View.Put(Matrix3x3::TransformReverse(view.Trans));
		PolyGonManager.ShaderFullDefault.Scale.Put(view.Scale);
		PolyGonManager.DrawFull();
	}
	{
		PolyGonManager.ShaderWireDefault.Bind();
		PolyGonManager.ShaderWireDefault.DisplaySize.Put(window.Size);
		PolyGonManager.ShaderWireDefault.View.Put(Matrix3x3::TransformReverse(view.Trans));
		PolyGonManager.ShaderWireDefault.Scale.Put(view.Scale);
		PolyGonManager.DrawWire();
	}
}
void Context2D::mFrame(double timeDelta)
{
	FrameTime frame_time(60);
	frame_time.Update(timeDelta);

	UpdateView(frame_time);

	Frame(frame_time);
}



void Context2D::Resize(const DisplaySize & Size)
{
	Multiform_DisplaySize.ChangeData(Size);
}

int Context2D::Run()
{
	window.InitCallBack.Assign<Context2D>(this, &Context2D::mInit);
	window.FreeCallBack.Assign<Context2D>(this, &Context2D::mFree);
	window.FrameCallBack.Assign<Context2D>(this, &Context2D::mFrame);
	window.ResizeCallBack.Assign<Context2D>(this, &Context2D::Resize);

	window.MouseManager.Callback_ScrollEvent.Assign(this, &Context2D::MouseScroll);
	window.MouseManager.Callback_ClickEvent.Assign(this, &Context2D::MouseClick);
	window.MouseManager.Callback_DragEvent.Assign(this, &Context2D::MouseDrag);

	window.KeyBoardManager.CallBack_KeyEvent.Assign(this, &Context2D::KeyBoardKey);

	window.Create();
	Debug::Log << "<<<< Run Window" << Debug::Done;
	window.Run();
	Debug::Log << ">>>> Run Window" << Debug::Done;
	window.Delete();

	return 0;
}
