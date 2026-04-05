
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
~MainContext()
{ }
MainContext()
	: MainContext2D()
{ }



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

void Init() override { }
void Free() override { }



void Frame(FrameTime frame_time) override
{
	(void)frame_time;

	{
		PolyGonObject obj((unsigned int)0);
		obj.Trans() = Trans2D(Point2D(0, 0));
		obj.ShowWire();
	}

	{
		PolyGonObject obj((unsigned int)0);
		obj.Trans() = Trans2D(Point2D(0.5f, 0.5f), Angle::Degrees(45));
		obj.ShowWire();
		obj.HideFull();
	}

	mDraw();
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
