
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

// Text
#include "Text/Manager.hpp"
#include "Text/Object.hpp"

// Random
#include "Random.hpp"

// Perlin
#include "Noise/Perlin2D.hpp"

// Plane
#include "Plane/Plane.hpp"
#include "Plane/PlaneGraphics.hpp"
#include "Plane/PlaneManager.hpp"

// Voxel
#include "Voxel/Chunk.hpp"
#include "Voxel/ChunkGraphics.hpp"
#include "Voxel/ChunkManager.hpp"



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
::ChunkManager			ChunkManager;

Perlin2D				Perlin0;

~MainContext()
{ }
MainContext()
	: MainContext3D()
	, PolyHedraManager()
	, TextManager()
	, PlaneManager()
	, ChunkManager()
	, Perlin0(Perlin2D::Random(Undex2D(8, 8)))
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

void VoxelGraphicsCreate()
{
	{
		Container::Array<::Shader::Code> code({
			Shader::Code(MediaDirectory.File("Shaders/Plane/Plane.vert")),
			Shader::Code(MediaDirectory.File("Shaders/Plane/Plane.frag")),
		});
		ChunkManager.Shader.Change(code);
	}

	ChunkManager.GraphicsCreate();
}
void VoxelGraphicsDelete()
{
	ChunkManager.GraphicsCreate();
}
void VoxelDraw()
{
	ChunkManager.Shader.Bind();
	ChunkManager.Shader.DisplaySize.Put(window.Size);
	ChunkManager.Shader.Depth.Put(view.Depth);
	ChunkManager.Shader.View.Put(Matrix4x4::TransformReverse(view.Trans));
	ChunkManager.Shader.FOV.Put(view.FOV);
	ChunkManager.Draw();
}



void Make() override
{
	window.DefaultColor = ColorF4(1, 1, 1);
//	view.Trans.Position = Point3D(1, 0, 1);

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
	VoxelGraphicsCreate();
}
void Free() override
{
	PolyHedraManager.GraphicsDelete();
	TextManager.GraphicsDelete();
	PlanesGraphicsDelete();
	VoxelGraphicsDelete();
}



bool ShowFull = true;
bool ShowWire = false;

bool ShowTiles = true;
bool ShowVoxels = true;

void Frame(double timeDelta) override
{
	FrameTime frame_time(64);
	frame_time.Update(timeDelta);
	UpdateView(frame_time);

	PlaneManager.UpdateAround(Perlin0, Point2D(view.Trans.Position.X, view.Trans.Position.Z));
	ChunkManager.UpdateAround(Perlin0, view.Trans.Position);

	if (window.KeyBoardManager[Keys::D1].State == State::Press) { ShowFull = !ShowFull; }
	if (window.KeyBoardManager[Keys::D2].State == State::Press) { ShowWire = !ShowWire; }
	if (window.KeyBoardManager[Keys::D3].State == State::Press) { ShowTiles = !ShowTiles; }
	if (window.KeyBoardManager[Keys::D4].State == State::Press) { ShowVoxels = !ShowVoxels; }

	if (window.KeyBoardManager[Keys::F4].State == State::Press)
	{
		PlaneManager.ShouldGenerate = !PlaneManager.ShouldGenerate;
		ChunkManager.ShouldGenerate = !ChunkManager.ShouldGenerate;
	}
	if (window.KeyBoardManager[Keys::F5].State == State::Press)
	{
		PlaneManager.Clear();
		ChunkManager.Clear();
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

	if (ShowTiles) { PlanesDraw(); }
	if (ShowVoxels) { VoxelDraw(); }

	GL::Clear(GL::ClearMask::DepthBufferBit);
	{
		std::stringstream ss;
		ss << "Frame Hz(" << frame_time.WantedFramesPerSecond << '|' << frame_time.ActualFramesPerSecond << ")\n";
		ss << "Frame D(" << frame_time.WantedFrameTime << '|' << frame_time.ActualFrameTime << ")\n";
		ss << '\n';

		unsigned int count_planes = PlaneManager.Planes.Count();
		unsigned int count_tiles = count_planes * PLANE_VALUES_PER_AREA;

		unsigned long long planes_memory0 = count_tiles * sizeof(float);
		unsigned long long planes_memory1 = planes_memory0 / 1000;
		unsigned long long planes_memory2 = planes_memory1 / 1000;

		ss << "ShouldGenerate:" << PlaneManager.ShouldGenerate << '\n';
		ss << "Count Planes:" << count_planes << '\n';
		ss << "Count Tiles:" << count_tiles << '\n';
		ss << "Memory:" << planes_memory0 << "B\n";
		ss << "Memory:" << planes_memory1 << "kB\n";
		ss << "Memory:" << planes_memory2 << "MB\n";
		ss << '\n';

		unsigned int count_chunks = ChunkManager.Chunks.Count();
		unsigned int count_voxels = count_chunks * CHUNK_VALUES_PER_VOLM;

		unsigned long long chunks_memory0 = count_voxels * sizeof(float);
		unsigned long long chunks_memory1 = chunks_memory0 / 1000;
		unsigned long long chunks_memory2 = chunks_memory1 / 1000;

		ss << "ShouldGenerate:" << ChunkManager.ShouldGenerate << '\n';
		ss << "Count Chunks:" << count_chunks << '\n';
		ss << "Count Voxels:" << count_voxels << '\n';
		ss << "Memory:" << chunks_memory0 << "B\n";
		ss << "Memory:" << chunks_memory1 << "kB\n";
		ss << "Memory:" << chunks_memory2 << "MB\n";
		ss << '\n';

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
