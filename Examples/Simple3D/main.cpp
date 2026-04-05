
// main
#include "../main.hpp"
#include "../MainContext3D.hpp"

// Debug
#include "Debug.hpp"
#include "ValueTypeShow.hpp"
#include <iostream>

// ValueType
#include "ValueType/Trans3D.hpp"
#include "ValueType/Matrix4x4.hpp"

// PolyHedra
#include "PolyHedra/PolyHedra.hpp"
#include "PolyHedra/Manager.hpp"
#include "PolyHedra/Object.hpp"

struct MainContext : public MainContext3D
{
::PolyHedraManager		PolyHedraManager;

~MainContext()
{ }
MainContext()
	: MainContext3D()
	, PolyHedraManager()
{
	PolyHedraManager.MakeCurrent();
}



void Make() override
{
	{
		PolyHedra * polyhedra = PolyHedra::Load(MediaDirectory.File("YMT/Light/Chair.polyhedra"));
		unsigned int idx = PolyHedraManager.PlacePolyHedra(polyhedra);
		std::cout << "PolyHedra Index: " << idx << '\n';
	}
}

void Init() override
{
	Make();
	PolyHedraManager.InitExternal(MediaDirectory);
	PolyHedraManager.GraphicsCreate();
	PolyHedraManager.InitInternal();
}
void Free() override
{
	PolyHedraManager.GraphicsDelete();
}



bool ShowFull = true;
bool ShowWire = false;

void Frame(double timeDelta) override
{
	FrameTime frame_time(60);
	frame_time.Update(timeDelta);
	UpdateView(frame_time);

	if (window.KeyBoardManager[Keys::D1].State == State::Press) { ShowFull = !ShowFull; }
	if (window.KeyBoardManager[Keys::D2].State == State::Press) { ShowWire = !ShowWire; }
	if (window.KeyBoardManager[Keys::D3].State == State::Press)
	{
		PolyHedra * polyhedra = PolyHedraManager.InstanceManagers[0].PolyHedra;
		delete polyhedra;

		polyhedra = PolyHedra::Load(MediaDirectory.File("YMT/Light/Chair.polyhedra"));;
		PolyHedraManager.InstanceManagers[0].Change(polyhedra);
	}

	{
		PolyHedraObject obj((unsigned int)0);
		obj.Trans() = Trans3D(Point3D(0, 0, 0));
		obj.ShowWire();
	}

	PolyHedraManager.ClearInstances();
	PolyHedraManager.Update();
	if (ShowFull)
	{
		PolyHedraManager.ShaderFullDefault.Bind();
		PolyHedraManager.ShaderFullDefault.DisplaySize.Put(window.Size);
		PolyHedraManager.ShaderFullDefault.Depth.Put(view.Depth);
		PolyHedraManager.ShaderFullDefault.View.Put(Matrix4x4::TransformReverse(view.Trans));
		PolyHedraManager.ShaderFullDefault.FOV.Put(view.FOV);
		PolyHedraManager.DrawFull();
	}
	if (ShowWire)
	{
		PolyHedraManager.ShaderWireDefault.Bind();
		PolyHedraManager.ShaderWireDefault.DisplaySize.Put(window.Size);
		PolyHedraManager.ShaderWireDefault.Depth.Put(view.Depth);
		PolyHedraManager.ShaderWireDefault.View.Put(Matrix4x4::TransformReverse(view.Trans));
		PolyHedraManager.ShaderWireDefault.FOV.Put(view.FOV);
		PolyHedraManager.DrawWire();
	}
}



void MouseScroll(ScrollArgs args) override { (void)args; }
void MouseClick(ClickArgs args) override { (void)args; }
void MouseDrag(DragArgs args) override { (void)args; }

void KeyBoardKey(KeyArgs args) override { (void)args; }
};



int run()
{
	MainContext context;
	return context.Run();
}
