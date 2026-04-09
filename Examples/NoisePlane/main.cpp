
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
#include "Random.hpp"
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

# define PLANE_SCALE 0.125
# define PLANE_CELL_PER_SIDE 8
# define PLANE_CELL_PER_AREA PLANE_CELL_PER_SIDE * PLANE_CELL_PER_SIDE

# define PERLIN_NODES_PER_SIDE 8
# define PERLIN_NODES_PER_AREA PERLIN_NODES_PER_SIDE * PERLIN_NODES_PER_SIDE

Perlin2D				Perlin0;
PolyHedraObjectArray	Perlin0_Nodes;

PolyHedraObjectArray	Plane_Cubes;

PolyHedraObject			Image_Object;

~MainContext()
{ }
MainContext()
	: MainContext3D()
	, PolyHedraManager()
	, Perlin0(Perlin2D::Random(Undex2D(PERLIN_NODES_PER_SIDE, PERLIN_NODES_PER_SIDE)))
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
void CountBits(unsigned int val)
{
	unsigned char bit0 = 0;
	unsigned char bit1 = 0;
	for (unsigned int i = 0; i < 32; i++)
	{
		if ((val >> i) & 1)
		{
			bit1++;
		}
		else
		{
			bit0++;
		}
	}
//	std::cout << ((int)bit0) << ' ' << ((int)bit1) << '\n';

	if (bit0 == 16 && bit1 == 16)
	{
		ShowBase16(val);
		std::cout << '\n';
	}
}
struct Distribution
{
	const unsigned int count = 0x80;
	const unsigned int mask = 0x7F;

	unsigned int Counts[0x80];
	Distribution()
	{
		Clear();
	}
	void Clear()
	{
		for (unsigned int i = 0; i < count; i++)
		{
			Counts[i] = 0;
		}
	}
	void Consider(unsigned int val)
	{
		Counts[val & mask]++;
	}
	void Show(unsigned int check)
	{
		for (unsigned int i = 0; i < count; i++)
		{
			if ((i & 0xF) == 0)
			{
				std::cout << ' ';
			}

			if (Counts[i] > check)
			{
				std::cout << '#';
			}
			else
			{
				std::cout << '|';
			}
		}
	}
};
void TestRandom()
{
	unsigned int val = 0;
	ShowBase16(val);
	std::cout << '\n';

	Distribution Dis;

	for (unsigned int i = 0; i < 100; i++)
	{
		Dis.Consider(val);

		val = Random::Mutilate(val);
		//CountBits(val);
		ShowBase16(val);
		std::cout << '\n';
	}
	std::cout << '\n';

	for (unsigned int j = 16; j <= 16; j--)
	{
		unsigned int comp = (j << 0);
		ShowBase16(comp);
		std::cout << ' ';
		Dis.Show(comp);
		std::cout << '\n';
	}
}


struct Plane
{
	float		Heights[PLANE_CELL_PER_AREA];
	Point2D		Pos;
	Plane()
	{
		for (unsigned int i = 0; i < PLANE_CELL_PER_AREA; i++)
		{
			Heights[i] = 0.0f;
		}
	}

	Point2D Pos2At(Undex2D u)
	{
		return Point2D(
			((Pos.X * PLANE_CELL_PER_SIDE) + u.X) * PLANE_SCALE,
			((Pos.Y * PLANE_CELL_PER_SIDE) + u.Y) * PLANE_SCALE
		);
	}
	Point3D Pos3At(Undex2D u)
	{
		return Point3D(
			((Pos.X * PLANE_CELL_PER_SIDE) + u.X) * PLANE_SCALE,
			Heights[u.X + (u.Y * PLANE_CELL_PER_SIDE)],
			((Pos.Y * PLANE_CELL_PER_SIDE) + u.Y) * PLANE_SCALE
		);
	}

	void Generate(const Perlin2D & noise)
	{
		for (unsigned int i = 0; i < PLANE_CELL_PER_AREA; i++)
		{
			Undex2D u(i % PLANE_CELL_PER_SIDE, i / PLANE_CELL_PER_SIDE);
			Point2D p = Pos2At(u);
			float val = 0.0f;
			val += noise.Calculate(p * 1) / 1;
			//val += noise.Calculate(p * 2) / 2;
			//val += noise.Calculate(p * 4) / 4;
			//val += noise.Calculate(p * 8) / 8;
			Heights[i] = val;
		}
	}
};


void Make() override
{
	window.DefaultColor = ColorF4(0, 0, 0);

	PolyHedra * cone = PolyHedra::Generate::ConeC(4, 0.25f * PLANE_SCALE, 4.0f * PLANE_SCALE);
	PolyHedra * cube = PolyHedra::Generate::HexaHedron(0.5f * PLANE_SCALE);
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
		float size_half = PLANE_CELL_PER_SIDE * PLANE_SCALE;
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
		Plane plane[4 * 4];
		for (unsigned int i = 0; i < 4 * 4; i++)
		{
			Undex2D u(i % 4, i / 4);
			plane[i].Pos = Point2D(u.X, u.Y);
			plane[i].Generate(Perlin0);
		}

		Plane_Cubes.Create(cube, PLANE_CELL_PER_AREA * 4 * 4);
		for (unsigned int p = 0; p < 4 * 4; p++)
		{
			for (unsigned int i = 0; i < PLANE_CELL_PER_AREA; i++)
			{
				Undex2D u(i % PLANE_CELL_PER_SIDE, i / PLANE_CELL_PER_SIDE);
				Plane_Cubes[(p * PLANE_CELL_PER_AREA) + i].Trans().Position = plane[p].Pos3At(u);
				Plane_Cubes[(p * PLANE_CELL_PER_AREA) + i].HideFull();
			}
		}

		float size_half = PERLIN_NODES_PER_SIDE * (PLANE_CELL_PER_SIDE / 2) * PLANE_SCALE;
		Undex2D count(PLANE_CELL_PER_SIDE * PERLIN_NODES_PER_SIDE, PLANE_CELL_PER_SIDE * PERLIN_NODES_PER_SIDE);
		Image img(count);

		for (unsigned int i = 0; i < PLANE_CELL_PER_AREA * PERLIN_NODES_PER_AREA; i++)
		{
			Undex2D u(i % (PLANE_CELL_PER_SIDE * PERLIN_NODES_PER_SIDE), i / (PLANE_CELL_PER_SIDE * PERLIN_NODES_PER_SIDE));
			Point2D p = Point2D(u.X, u.Y) * PLANE_SCALE;

			float val = Perlin0.Calculate(p * 1) / 1;

			ColorU4 col;
			if (val == 0.0f)	{ col = ColorU4(); }
			if (val > 0.0f)		{ col = ColorU4(+val * 255, 0, 0); }
			if (val < 0.0f)		{ col = ColorU4(0, 0, -val * 255); }

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
			p.X = Random::Float01In();
			p.Y = Random::Float01In();
			box.Consider(p);
			p.X = p.X * Perlin0.Count.X;
			p.Y = p.Y * Perlin0.Count.Y;
			Perlin0.Calculate(p);
		}
		std::cout << box << '\n';
		std::cout << '\n';
	}
	Perlin2D::DebugShow();
	//TestRandom();
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

bool ShowPlane = false;
bool ShowArrows = true;

void Frame(double timeDelta) override
{
	FrameTime frame_time(60);
	frame_time.Update(timeDelta);
	UpdateView(frame_time);

	if (window.KeyBoardManager[Keys::D1].State == State::Press) { ShowFull = !ShowFull; }
	if (window.KeyBoardManager[Keys::D2].State == State::Press) { ShowWire = !ShowWire; }
	if (window.KeyBoardManager[Keys::D3].State == State::Press)
	{
		ShowArrows = !ShowArrows;
		for (unsigned int i = 0; i < Perlin0_Nodes.Count; i++)
		{
			if (ShowArrows)
			{
				Perlin0_Nodes[i].ShowFull();
			}
			else
			{
				Perlin0_Nodes[i].HideFull();
			}
		}
	}
	if (window.KeyBoardManager[Keys::D4].State == State::Press)
	{
		ShowPlane = !ShowPlane;
		for (unsigned int i = 0; i < Plane_Cubes.Count; i++)
		{
			if (ShowPlane)
			{
				Plane_Cubes[i].ShowFull();
			}
			else
			{
				Plane_Cubes[i].HideFull();
			}
		}
		if (ShowPlane)
		{
			Image_Object.HideFull();
		}
		else
		{
			Image_Object.ShowFull();
		}
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
