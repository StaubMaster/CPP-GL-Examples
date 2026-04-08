
// main
#include "../main.hpp"
#include "../MainContext3D.hpp"

// Debug
#include <iostream>
#include "Debug.hpp"
#include "ValueType/_Show.hpp"
#include "ValueType/_Include.hpp"

// PolyHedra
#include "PolyHedra/PolyHedra.hpp"
#include "PolyHedra/Generate.hpp"
#include "PolyHedra/Manager.hpp"
#include "PolyHedra/Object.hpp"

#include "Image.hpp"
#include "PolyHedra/Data.hpp"

// Perlin
#include "Perlin2D.hpp"



struct PolyHedraObjectArray
{
	unsigned int		Count;
	PolyHedraObject *	Array;

	PolyHedraObject &	operator[](unsigned int i)
	{
		return Array[i];
	}

	~PolyHedraObjectArray()
	{
		delete[] Array;
	}
	PolyHedraObjectArray()
		: Count(0)
		, Array(nullptr)
	{ }
	PolyHedraObjectArray(const PolyHedraObjectArray & other) = delete;
	PolyHedraObjectArray & operator=(const PolyHedraObjectArray & other) = delete;

	void Create(PolyHedra * polyhedra, unsigned int count)
	{
		Count = count;
		Array = new PolyHedraObject[Count];
		for (unsigned int i = 0; i < Count; i++)
		{
			Array[i].Create(polyhedra);
		}
	}
	void Create(unsigned int polyhedra, unsigned int count)
	{
		Count = count;
		Array = new PolyHedraObject[Count];
		for (unsigned int i = 0; i < Count; i++)
		{
			Array[i].Create(polyhedra);
		}
	}

	void Delete()
	{
		delete[] Array;
		Array = nullptr;
		Count = 0;
	}
};

struct MainContext : public MainContext3D
{
::PolyHedraManager		PolyHedraManager;

unsigned int			CellCount;
unsigned int			SegmentCount;
float					Plane_Scale;

Perlin2D				Perlin0;
PolyHedraObjectArray	Perlin0_Nodes;

PolyHedraObjectArray	Plane_Cubes;

PolyHedraObject			Image_Object;

~MainContext()
{ }
MainContext()
	: MainContext3D()
	, PolyHedraManager()
	, CellCount(16)
	, SegmentCount(16)
	, Plane_Scale(0.125f)
	, Perlin0(Perlin2D::Random(Undex2D(CellCount, CellCount)))
	, Perlin0_Nodes()
	, Plane_Cubes()
{
	PolyHedraManager.MakeCurrent();
}



void ShowBase16(unsigned int val)
{
	const char * hex = "0123456789ABCDEF";
	char c[9];
	c[0] = hex[(val >> 28) & 0xF];
	c[1] = hex[(val >> 24) & 0xF];
	c[2] = hex[(val >> 20) & 0xF];
	c[3] = hex[(val >> 16) & 0xF];
	c[4] = hex[(val >> 12) & 0xF];
	c[5] = hex[(val >> 8) & 0xF];
	c[6] = hex[(val >> 4) & 0xF];
	c[7] = hex[(val) & 0xF];
	c[8] = '\0';
	std::cout << c;
}
#include <cstdlib>

void Make() override
{
	window.DefaultColor = ColorF4(0, 0, 0);

	PolyHedra * cone = PolyHedra::Generate::ConeC(4, 0.25f * Plane_Scale, 4.0f * Plane_Scale);
	PolyHedra * cube = PolyHedra::Generate::HexaHedron(0.5f);
	{
		for (unsigned int i = 0; i < cube -> Corners.Count(); i++)
		{
			cube -> Corners[i].Position.Y = 0.0f;
		}
	}
	{
		PolyHedraManager.PlacePolyHedra(cone);
		PolyHedraManager.PlacePolyHedra(cube);
	}
	{
		float size_half = SegmentCount * Plane_Scale;
		unsigned int c = Perlin0.Count.X * Perlin0.Count.Y;

		Perlin0_Nodes.Create(cone, c);
		for (unsigned int i = 0; i < c; i++)
		{
			Undex2D u(i % Perlin0.Count.X, i / Perlin0.Count.X);
			Point2D p2 = Perlin0.Data[i];
			Point3D p3(p2.X, 0, p2.Y);
			Perlin0_Nodes[i].Trans().Position = Point3D(u.X * size_half, 0.0f, u.Y * size_half);
			Perlin0_Nodes[i].Trans().Rotation = EulerAngle3D::PointToZ(p3);
		}
	}
	{
		Undex2D count(CellCount * SegmentCount, CellCount * SegmentCount);
		Image img(count);

		float size_half = SegmentCount * (CellCount / 2) * Plane_Scale;
		unsigned int c = count.X * count.Y;

		//Plane_Cubes.Create(cube, c);
		for (unsigned int i = 0; i < c; i++)
		{
			Undex2D u(i % count.X, i / count.X);
			Point2D p(u.X, u.Y);
			float f = Perlin0.Calculate(p / SegmentCount) * 1;

			//Plane_Cubes[i].Trans().Position = Point3D(p.X, f, p.Y);

			ColorU4 col;
			if (f == 0.0f)	{ col = ColorU4(); }
			if (f > 0.0f)	{ col = ColorU4(+f * 255, 0, 0); }
			if (f < 0.0f)	{ col = ColorU4(0, 0, -f * 255); }

			u.Y = (count.Y - u.Y) - 1;
			img.Pixel(u) = col;
		}

		PolyHedra * picture = PolyHedra::Generate::DuoHedra(img, size_half);
		PolyHedraManager.PlacePolyHedra(picture);
		Image_Object.Create(picture);
		Image_Object.Trans().Position = Point3D(size_half, 0, size_half);
		Image_Object.Trans().Rotation = EulerAngle3D::Degrees(0, 90, 0);
	}
	Perlin2D::DebugShow();
	{
		Point2D p;
		AxisBox2D box;
		for (unsigned int i = 0; i < 100000; i++)
		{
			p.X = Perlin2D::RandomFloat01();
			p.Y = Perlin2D::RandomFloat01();
			box.Consider(p);
			p.X = p.X * Perlin0.Count.X;
			p.Y = p.Y * Perlin0.Count.Y;
			Perlin0.Calculate(p);
		}
		std::cout << box << '\n';
		std::cout << '\n';
	}
	Perlin2D::DebugShow();
}

void Init() override
{
	Make();

	PolyHedraManager.InitExternal(MediaDirectory); // do this outside ? so in MainContext ?
	PolyHedraManager.GraphicsCreate();
	PolyHedraManager.InitInternal(); // do this in GraphicsCreate ?
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

	PolyHedraManager.ClearInstances();
	PolyHedraManager.UpdateInstances();
	{
		//std::cout << "PolyHedraManager.ObjectDatas.Count(): " << PolyHedraManager.ObjectDatas.Count() << '\n';
	}
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
