
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

// Graphics
#include "Graphics/Shader/Code.hpp"
#include "Miscellaneous/Container/Array.hpp"

// Perlin
#include "Random.hpp"
#include "Perlin2D.hpp"
#include "Plane.hpp"
#include "PlaneGraphics.hpp"



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

Perlin2D				Perlin0;
PolyHedraObjectArray	Perlin0_Nodes;

PolyHedraObject			Image_Object;

//# define PLANES_PER_SIDE 8
# define PLANES_PER_SIDE 32
# define PLANES_PER_AREA PLANES_PER_SIDE * PLANES_PER_SIDE
Plane					Planes[PLANES_PER_AREA];

PlaneGraphics::Shader	Plane_Shader;
PlaneGraphics::Buffer	Plane_Buffers[PLANES_PER_AREA];

~MainContext()
{ }
MainContext()
	: MainContext3D()
	, PolyHedraManager()
	, Perlin0(Perlin2D::Random(Undex2D(8, 8)))
	, Perlin0_Nodes()
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



struct PlaneValue
{
	bool	Known;
	float	Value;
	PlaneValue()
		: Known(false)
		, Value(0.0f)
	{ }
	ColorF4 ToColor() const
	{
		if (Value > 0.0f) { return ColorF4(+Value, 0, 0); }
		if (Value < 0.0f) { return ColorF4(0, 0, -Value); }
		return ColorF4(0, 0, 0);
	}
};
struct PlaneNeighbours
{
	Plane * plane00;
	Plane * plane01;
	Plane * plane10;
	Plane * plane11;

	PlaneValue FromPlane00(unsigned int udx) const
	{
		PlaneValue val;
		if (plane00 != nullptr)
		{
			val.Value = (*plane00).Heights[udx];
			val.Known = true;
		}
		return val;
	}
	PlaneValue FromPlane01(unsigned int udx) const
	{
		PlaneValue val;
		if (plane01 != nullptr)
		{
			val.Value = (*plane01).Heights[udx];
			val.Known = true;
		}
		return val;
	}
	PlaneValue FromPlane10(unsigned int udx) const
	{
		PlaneValue val;
		if (plane10 != nullptr)
		{
			val.Value = (*plane10).Heights[udx];
			val.Known = true;
		}
		return val;
	}
	PlaneValue FromPlane11(unsigned int udx) const
	{
		PlaneValue val;
		if (plane11 != nullptr)
		{
			val.Value = (*plane11).Heights[udx];
			val.Known = true;
		}
		return val;
	}
};

void PlaneToBuffer(const PlaneNeighbours & planes, PlaneGraphics::Buffer & buffer)
{
	{
		Container::Binary<PlaneGraphics::MainData> data;
		Undex2D size(PLANE_CELL_PER_SIDE, PLANE_CELL_PER_SIDE);
		for (unsigned int i = 0; i < PLANE_CELL_PER_AREA ; i++)
		{
			Undex2D u = size.ConvertX(i);
			Undex2D u0 = Undex2D(u.X + 0, u.Y + 0) % size;
			Undex2D u1 = Undex2D(u.X + 1, u.Y + 1) % size;
			Bool2D comp = u0 < u1;

			unsigned int udxs[4];
			udxs[0b00] = size.ConvertX(Undex2D(u0.X, u0.Y));
			udxs[0b01] = size.ConvertX(Undex2D(u1.X, u0.Y));
			udxs[0b10] = size.ConvertX(Undex2D(u0.X, u1.Y));
			udxs[0b11] = size.ConvertX(Undex2D(u1.X, u1.Y));

			PlaneValue vals[4];

			if (comp.GetX() && comp.GetY())
			{
				vals[0b00] = planes.FromPlane00(udxs[0b00]);
				vals[0b01] = planes.FromPlane00(udxs[0b01]);
				vals[0b10] = planes.FromPlane00(udxs[0b10]);
				vals[0b11] = planes.FromPlane00(udxs[0b11]);
			}

			if (!comp.GetX() && comp.GetY())
			{
				vals[0b00] = planes.FromPlane00(udxs[0b00]);
				vals[0b01] = planes.FromPlane01(udxs[0b01]);
				vals[0b10] = planes.FromPlane00(udxs[0b10]);
				vals[0b11] = planes.FromPlane01(udxs[0b11]);
			}

			if (comp.GetX() && !comp.GetY())
			{
				vals[0b00] = planes.FromPlane00(udxs[0b00]);
				vals[0b01] = planes.FromPlane00(udxs[0b01]);
				vals[0b10] = planes.FromPlane10(udxs[0b10]);
				vals[0b11] = planes.FromPlane10(udxs[0b11]);
			}

			if (!comp.GetX() && !comp.GetY())
			{
				vals[0b00] = planes.FromPlane00(udxs[0b00]);
				vals[0b01] = planes.FromPlane01(udxs[0b01]);
				vals[0b10] = planes.FromPlane10(udxs[0b10]);
				vals[0b11] = planes.FromPlane11(udxs[0b11]);
			}

			PlaneGraphics::MainData temp[4];

			temp[0b00].Pos = Point3D((u.X + 0) * PLANE_SCALE, vals[0b00].Value, (u.Y + 0) * PLANE_SCALE);
			temp[0b01].Pos = Point3D((u.X + 1) * PLANE_SCALE, vals[0b01].Value, (u.Y + 0) * PLANE_SCALE);
			temp[0b10].Pos = Point3D((u.X + 0) * PLANE_SCALE, vals[0b10].Value, (u.Y + 1) * PLANE_SCALE);
			temp[0b11].Pos = Point3D((u.X + 1) * PLANE_SCALE, vals[0b11].Value, (u.Y + 1) * PLANE_SCALE);

			temp[0b00].Col = vals[0b00].ToColor();
			temp[0b01].Col = vals[0b01].ToColor();
			temp[0b10].Col = vals[0b10].ToColor();
			temp[0b11].Col = vals[0b11].ToColor();

			if (vals[0b00].Known && vals[0b01].Known && vals[0b10].Known) { data.Insert(temp[0b00]); data.Insert(temp[0b10]); data.Insert(temp[0b01]); }
			if (vals[0b10].Known && vals[0b01].Known && vals[0b11].Known) { data.Insert(temp[0b01]); data.Insert(temp[0b10]); data.Insert(temp[0b11]); }
		}
		buffer.Main.Change(data);
	}
	{
		Container::Binary<PlaneGraphics::InstData> data;
		PlaneGraphics::InstData temp;
		temp.Pos.X = (*planes.plane00).Pos.X * PLANE_CELL_PER_SIDE * PLANE_SCALE;
		temp.Pos.Y = 0;
		temp.Pos.Z = (*planes.plane00).Pos.Y * PLANE_CELL_PER_SIDE * PLANE_SCALE;
		data.Insert(temp);
		buffer.Inst.Change(data);
	}
}

void PlanesGraphicsCreate()
{
	{
		Container::Array<::Shader::Code> code({
			Shader::Code(MediaDirectory.File("Shaders/Plane/Plane.vert")),
			Shader::Code(MediaDirectory.File("Shaders/Plane/Plane.frag")),
		});
		Plane_Shader.Change(code);
		Plane_Shader.Create();
	}
	for (unsigned int i = 0; i < PLANES_PER_AREA; i++)
	{
		Plane_Buffers[i].Main.Pos.Change(0);
		Plane_Buffers[i].Main.Col.Change(1);
		Plane_Buffers[i].Inst.Pos.Change(2);
		Plane_Buffers[i].Create();
		Plane_Buffers[i].Main.Init();
		Plane_Buffers[i].Inst.Init();
	}

	Undex2D size(PLANES_PER_SIDE, PLANES_PER_SIDE);
	for (unsigned int i = 0; i < PLANES_PER_AREA; i++)
	{
		Undex2D u = size.ConvertX(i);
		PlaneNeighbours planes;
		planes.plane00 = &Planes[i];
		if (u.X != (PLANES_PER_SIDE - 1)) { planes.plane01 = &Planes[(u.X + 1) + ((u.Y + 0) * PLANES_PER_SIDE)]; } else { planes.plane01 = nullptr; }
		if (u.Y != (PLANES_PER_SIDE - 1)) { planes.plane10 = &Planes[(u.X + 0) + ((u.Y + 1) * PLANES_PER_SIDE)]; } else { planes.plane10 = nullptr; }
		if (u.X != (PLANES_PER_SIDE - 1) && u.Y != (PLANES_PER_SIDE - 1)) { planes.plane11 = &Planes[(u.X + 1) + ((u.Y + 1) * PLANES_PER_SIDE)]; } else { planes.plane11 = nullptr; }
		PlaneToBuffer(planes, Plane_Buffers[i]);
	}
}
void PlanesGraphicsDelete()
{
	Plane_Shader.Delete();
	for (unsigned int i = 0; i < PLANES_PER_AREA; i++)
	{
		Plane_Buffers[i].Delete();
	}
}
void PlanesDraw()
{
	Plane_Shader.Bind();
	Plane_Shader.DisplaySize.Put(window.Size);
	Plane_Shader.Depth.Put(view.Depth);
	Plane_Shader.View.Put(Matrix4x4::TransformReverse(view.Trans));
	Plane_Shader.FOV.Put(view.FOV);
	for (unsigned int i = 0; i < PLANES_PER_AREA; i++)
	{
		Plane_Buffers[i].Draw();
	}
}



void Make() override
{
	window.DefaultColor = ColorF4(1, 1, 1);

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
			Undex2D u = Perlin0.Count.ConvertX(i);
			Point2D p2 = Perlin0.Data[i];
			Point3D p3(p2.X, 0, p2.Y);
			Perlin0_Nodes[i].Trans().Position = Point3D(u.X * size_half, 0.0f, u.Y * size_half);
			Perlin0_Nodes[i].Trans().Rotation = EulerAngle3D::PointToZ(p3);
		}
	}
	{
		Undex2D size(PLANES_PER_SIDE, PLANES_PER_SIDE);
		for (unsigned int i = 0; i < PLANES_PER_AREA; i++)
		{
			Undex2D u = size.ConvertX(i);
			Planes[i].Pos = Point2D(u.X, u.Y);
			Planes[i].Generate(Perlin0);
		}

		float size_half = Perlin0.Count.X * (PLANE_CELL_PER_SIDE / 2) * PLANE_SCALE;

		Undex2D count(PLANE_CELL_PER_SIDE * Perlin0.Count.X, PLANE_CELL_PER_SIDE * Perlin0.Count.Y);
		Image img(count);

		for (unsigned int i = 0; i < PLANE_CELL_PER_AREA * Perlin0.Count.X * Perlin0.Count.Y; i++)
		{
			Undex2D u = count.ConvertX(i);
			Point2D p = Point2D(u.X, u.Y) * PLANE_SCALE;

			float val = 0.0f;
			val += Perlin0.Calculate(p * 1) / 1;
			val += Perlin0.Calculate(p * 2) / 2;
			val += Perlin0.Calculate(p * 4) / 4;
			val += Perlin0.Calculate(p * 8) / 8;

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
		std::cout << "range: " << box << '\n';
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

	PlanesGraphicsCreate();
}
void Free() override
{
	PlanesGraphicsDelete();

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

	if (ShowPlane)
	{
		PlanesDraw();
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
