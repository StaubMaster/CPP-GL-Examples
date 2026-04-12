
// main
#include "../main.hpp"
#include "../MainContext3D.hpp"

// Debug
#include <iostream>
#include <sstream>
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

// Random
#include "Random.hpp"

// Perlin
#include "Perlin2D.hpp"

// Plane
#include "Plane.hpp"
#include "PlaneGraphics.hpp"
#include "PlaneManager.hpp"

// Text
#include "Text/Manager.hpp"
#include "Text/Object.hpp"



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
UI::Text::Manager		TextManager;
::PlaneManager			PlaneManager;

Perlin2D				Perlin0;
PolyHedraObject			CubeObject;

PolyHedraObjectArray	Perlin0_Nodes;
PolyHedraObject			Image_Object;

~MainContext()
{ }
MainContext()
	: MainContext3D()
	, PolyHedraManager()
	, TextManager()
	, PlaneManager()
	, Perlin0(Perlin2D::Random(Undex2D(8, 8)))
	, Perlin0_Nodes()
{
	PolyHedraManager.MakeCurrent();
	TextManager.MakeCurrent();
}



void TextMake()
{
	{
		Container::Array<Shader::Code> code({
			Shader::Code(MediaDirectory.File("Shaders/UI/Text.vert")),
			Shader::Code(MediaDirectory.File("Shaders/UI/Text.frag")),
		});
		TextManager.Shader.Change(code);
	}
	{
		TextManager.Buffer.Main.Pos.Change(0);
		TextManager.Buffer.Inst.Pos.Change(1);
		TextManager.Buffer.Inst.PalletMin.Change(2);
		TextManager.Buffer.Inst.PalletMax.Change(3);
		TextManager.Buffer.Inst.BoundMin.Change(4);
		TextManager.Buffer.Inst.BoundMax.Change(5);
	}
	{
		TextManager.TextFont = UI::Text::Font::Parse(
			MediaDirectory.File("Text/Font0.atlas")
		);
	}
}
void TextDraw()
{
	TextManager.Shader.DisplaySize.Put(window.Size);
	TextManager.Draw();
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



void PlanesGraphicsCreate()
{
	{
		Container::Array<::Shader::Code> code({
			Shader::Code(MediaDirectory.File("Shaders/Plane/Plane.vert")),
			Shader::Code(MediaDirectory.File("Shaders/Plane/Plane.frag")),
		});
		PlaneManager.Shader.Change(code);
	}

	PlaneManager.GraphicsCreate();
}
void PlanesGraphicsDelete()
{
	PlaneManager.GraphicsDelete();
}
void PlanesDraw()
{
	PlaneManager.Shader.Bind();
	PlaneManager.Shader.DisplaySize.Put(window.Size);
	PlaneManager.Shader.Depth.Put(view.Depth);
	PlaneManager.Shader.View.Put(Matrix4x4::TransformReverse(view.Trans));
	PlaneManager.Shader.FOV.Put(view.FOV);
	PlaneManager.Draw();
}



void MakePerlinNoiseArrows()
{
	PolyHedra * cone = PolyHedra::Generate::ConeC(4, 0.25f * PLANE_SCALE, 4.0f * PLANE_SCALE);
	PolyHedraManager.PlacePolyHedra(cone);

	float size_half = PLANE_VALUES_PER_SIDE * PLANE_SCALE;
	unsigned int c = Perlin0.Count.X * Perlin0.Count.Y;

	Perlin0_Nodes.Create(cone, c);
	for (unsigned int i = 0; i < c; i++)
	{
		Undex2D u = Perlin0.Count.Convert(i);
		Point2D p2 = Perlin0.Data[i];
		Point3D p3(p2.X, 0, p2.Y);
		Perlin0_Nodes[i].Trans().Position = Point3D(u.X * size_half, 0.0f, u.Y * size_half);
		Perlin0_Nodes[i].Trans().Rotation = EulerAngle3D::PointToZ(p3);
	}
}
void MakeNoiseImage()
{
	float size_half = Perlin0.Count.X * (PLANE_VALUES_PER_SIDE / 2) * PLANE_SCALE;

	Undex2D count(PLANE_VALUES_PER_SIDE * Perlin0.Count.X, PLANE_VALUES_PER_SIDE * Perlin0.Count.Y);
	Image img(count);

	for (unsigned int i = 0; i < PLANE_VALUES_PER_AREA * Perlin0.Count.X * Perlin0.Count.Y; i++)
	{
		Undex2D u = count.Convert(i);
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

void Make() override
{
	window.DefaultColor = ColorF4(1, 1, 1);
//	view.Trans.Position = Point3D(1, 0, 1);

	{
		PolyHedra * cube = PolyHedra::Generate::HexaHedron(1 / 16.0f);
		PolyHedraManager.PlacePolyHedra(cube);
		CubeObject.Create(cube);
	}
	//MakePerlinNoiseArrows();
	//MakeNoiseImage();
	{
		// this is needed to prevent compiler from complaining about multiple definitions of Bool2D
		Image img(Undex2D(1, 1));
		PolyHedra * picture = PolyHedra::Generate::DuoHedra(img);
		delete picture;
	}
	//Perlin2D::DebugShow();
	//TestRandom();
}

void Init() override
{
	Make();

	TextMake();

	PolyHedraManager.InitExternal(MediaDirectory); // do this outside ? so in MainContext ?
	PolyHedraManager.GraphicsCreate();
	PolyHedraManager.InitInternal(); // do this in GraphicsCreate ?

	TextManager.GraphicsCreate();

	PlanesGraphicsCreate();
}
void Free() override
{
	PolyHedraManager.GraphicsDelete();
	TextManager.GraphicsDelete();
	PlanesGraphicsDelete();
}



bool ShowFull = true;
bool ShowWire = false;

bool ShowPlane = true;
bool ShowArrows = false;

void Frame(double timeDelta) override
{
	FrameTime frame_time(64);
	frame_time.Update(timeDelta);
	UpdateView(frame_time);

	PlaneManager.UpdateAround(Perlin0, Point2D(view.Trans.Position.X, view.Trans.Position.Z));

	if (window.KeyBoardManager[Keys::D1].State == State::Press) { ShowFull = !ShowFull; }
	if (window.KeyBoardManager[Keys::D2].State == State::Press) { ShowWire = !ShowWire; }
	if (window.KeyBoardManager[Keys::D3].State == State::Press)
	{
		ShowArrows = !ShowArrows;
		for (unsigned int i = 0; i < Perlin0_Nodes.Count; i++)
		{
			if (Perlin0_Nodes[i].Is())
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
	}
	if (window.KeyBoardManager[Keys::D4].State == State::Press)
	{
		ShowPlane = !ShowPlane;
		if (Image_Object.Is())
		{
			if (ShowPlane)
			{
				Image_Object.HideFull();
			}
			else
			{
				Image_Object.ShowFull();
			}
		}
	}

	if (window.KeyBoardManager[Keys::F4].State == State::Press)
	{
		PlaneManager.ShouldGenerate = !PlaneManager.ShouldGenerate;
	}
	if (window.KeyBoardManager[Keys::F5].State == State::Press)
	{
		PlaneManager.Clear();
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

	GL::Clear(GL::ClearMask::DepthBufferBit);
	{
		unsigned int count_planes = PlaneManager.Planes.Count();
		unsigned int count_tiles = count_planes * PLANE_VALUES_PER_AREA;

		unsigned long long memory0 = count_tiles * sizeof(float);
		unsigned long long memory1 = memory0 / 1000;
		unsigned long long memory2 = memory1 / 1000;

		std::stringstream ss;
		ss << "Frame Hz(" << frame_time.WantedFramesPerSecond << '|' << frame_time.ActualFramesPerSecond << ")\n";
		ss << "Frame D(" << frame_time.WantedFrameTime << '|' << frame_time.ActualFrameTime << ")\n";
		ss << '\n';
		ss << "ShouldGenerate:" << PlaneManager.ShouldGenerate << '\n';
		ss << "Count Planes: " << count_planes << '\n';
		ss << "Count Tiles:" << count_tiles << '\n';
		ss << "Memory:" << memory0 << "B\n";
		ss << "Memory:" << memory1 << "kB\n";
		ss << "Memory:" << memory2 << "MB\n";

		UI::Text::Object text; text.Create();
		text.Pos().X = 10;
		text.Pos().Y = 10;
		text.Bound().Min = Point2D();
		text.Bound().Max = window.Size.Buffer.Full;
		text.String() = ss.str();
	}
	TextDraw();
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
