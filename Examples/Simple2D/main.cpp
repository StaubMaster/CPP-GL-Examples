
// main
#include "../main.hpp"
#include "../MainContext2D.hpp"

// Debug
#include "Debug.hpp"
#include "DataShow.hpp"
#include <iostream>

// ValueType
#include "ValueType/Matrix3x3.hpp"

// PolyGon
#include "PolyGon/PolyGon.hpp"
#include "PolyGon/Manager.hpp"
#include "PolyGon/Object.hpp"

struct MainContext : public MainContext2D
{
::PolyGonManager	PolyGonManager;

~MainContext()
{ }
MainContext()
	: MainContext2D()
	, PolyGonManager()
{
	PolyGonManager.MakeCurrent();
}



void Make() override
{
	{
		PolyGon * polygon = new PolyGon();
		polygon -> NewCorner(Point2D(-1.0f, -0.1f), ColorF4(0, 0, 0));
		polygon -> NewCorner(Point2D(+1.0f, -0.1f), ColorF4(0, 0, 0));
		polygon -> NewCorner(Point2D(+1.0f, +0.1f), ColorF4(0, 0, 0));
		polygon -> NewCorner(Point2D(-1.0f, +0.1f), ColorF4(0, 0, 0));
		polygon -> NewFace(0, 1, 2);
		polygon -> NewFace(0, 2, 3);
		unsigned int idx = PolyGonManager.PlacePolyGon(polygon);
		std::cout << "PolyGon Index: " << idx << '\n';
	}
}

void Init() override
{
	Make();

	PolyGonManager.InitExternal(MediaDirectory);
	PolyGonManager.GraphicsCreate();
	PolyGonManager.InitInternal();
}
void Free() override
{
	PolyGonManager.GraphicsDelete();
}



void Frame(double timeDelta) override
{
	FrameTime frame_time(60);
	frame_time.Update(timeDelta);

	UpdateView(frame_time);

	{
		PolyGonObject obj((unsigned int)0);
		obj.Trans() = Trans2D(Point2D(0, 0));
		obj.ShowWire();
		obj.HideFull();
	}
	
	{
		PolyGonObject obj((unsigned int)0);
		obj.Trans() = Trans2D(Point2D(0.5f, 0.5f), Angle::Degrees(45));
		obj.ShowWire();
		obj.HideFull();
	}

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



void MouseScroll(ScrollArgs args) override
{
	UpdateViewZoom(args);
}
void MouseClick(ClickArgs args) override { (void)args; }
void MouseDrag(DragArgs args) override { (void)args; }

void KeyBoardKey(KeyArgs args) override { (void)args; }
};



int run()
{
	MainContext context;
	return context.Run();
}
