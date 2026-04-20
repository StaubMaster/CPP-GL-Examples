
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
#include "PolyHedra/Data.hpp"

// Graphics
#include "Graphics/Shader/Code.hpp"
#include "Miscellaneous/Container/Array.hpp"
#include "Graphics/Multiform/_Include.hpp"

// FileManager
#include "Image.hpp"

// Text
#include "Text/Manager.hpp"
#include "Text/Object.hpp"

// Units
#include "UnitToString.hpp"

// Random
#include "Random.hpp"

// Noise
#include "Noise/Perlin2D.hpp"
#include "Noise/Perlin3D.hpp"

// Plane
#include "Plane/Plane.hpp"
#include "Plane/PlaneGraphics.hpp"
#include "Plane/PlaneManager.hpp"

// Voxel
#include "Voxel/Chunk.hpp"
#include "Voxel/ChunkManager.hpp"
#include "Voxel/VoxelOrientation.hpp"

#include "ValueType/LoopI3.hpp"



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

std::ostream & operator<<(std::ostream & s, Axis axis)
{
	switch (axis)
	{
		case Axis::Here : s << "Here"; break;
		case Axis::PrevX: s << "PrevX"; break;
		case Axis::PrevY: s << "PrevY"; break;
		case Axis::PrevZ: s << "PrevZ"; break;
		case Axis::NextX: s << "NextX"; break;
		case Axis::NextY: s << "NextY"; break;
		case Axis::NextZ: s << "NextZ"; break;
		case Axis::None : s << "None"; break;
		default : s << "Axis:" << ((unsigned int)axis); break;
	}
	return s;
}
std::ostream & operator<<(std::ostream & s, Diag diag)
{
	switch (diag)
	{
		case Diag::Here : s << "Here"; break;
		case Diag::Prev : s << "Prev"; break;
		case Diag::Next : s << "Next"; break;
		case Diag::DiagX: s << "DiagX"; break;
		case Diag::DiagY: s << "DiagY"; break;
		case Diag::DiagZ: s << "DiagZ"; break;
		default : s << "Diag:" << ((unsigned int)diag); break;
	}
	return s;
}
std::ostream & operator<<(std::ostream & s, Flip flip)
{
	switch (flip)
	{
		case Flip::None : s << "None"; break;
		case Flip::FlipX: s << "FlipX"; break;
		case Flip::FlipY: s << "FlipY"; break;
		case Flip::FlipZ: s << "FlipZ"; break;
		default : s << "Flip:" << ((unsigned int)flip); break;
	}
	return s;
}

struct MainContext : public MainContext3D
{
::PolyHedraManager		PolyHedraManager;
UI::Text::Manager		TextManager;
::PlaneManager			PlaneManager;
::ChunkManager			ChunkManager;

Perlin2D				Perlin2;
Perlin3D				Perlin3;

::Multiform::Matrix4x4		Multiform_View;
::Multiform::Depth			Multiform_Depth;
::Multiform::Angle			Multiform_FOV;

~MainContext()
{ }
MainContext()
	: MainContext3D()
	, PolyHedraManager()
	, TextManager()
	, PlaneManager()
	, ChunkManager()
	, Perlin2(Perlin2D::Random(Undex2D(8, 8)))
	, Perlin3(Perlin3D::Random(Undex3D(8, 8, 8)))
	, Multiform_View("View")
	, Multiform_Depth("Depth")
	, Multiform_FOV("FOV")
{
	PolyHedraManager.MakeCurrent();
	TextManager.MakeCurrent();
	Container::Array<Shader::Base*> shaders({
		&PolyHedraManager.ShaderFullDefault,
		&PolyHedraManager.ShaderWireDefault,
		&TextManager.Shader,
		&PlaneManager.Shader,
		&ChunkManager.Shader,
	});
	Multiform_DisplaySize.FindUniforms(shaders);
	Multiform_View.FindUniforms(shaders);
	Multiform_Depth.FindUniforms(shaders);
	Multiform_FOV.FindUniforms(shaders);
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

void VoxelGraphicsCreate()
{
	{
		Container::Array<::Shader::Code> code({
			Shader::Code(MediaDirectory.File("Shaders/Voxel/Voxel.vert")),
			Shader::Code(MediaDirectory.File("Shaders/Voxel/Voxel.frag")),
		});
		ChunkManager.Shader.Change(code);
	}
	ChunkManager.GraphicsCreate();
	{
		ChunkManager.Texture.Bind();
		Container::Array<FileInfo> files({
			MediaDirectory.File("Images/OrientationCorners.png"),
			MediaDirectory.File("Images/Gray6.png"),
			MediaDirectory.File("Images/fancy_GreenDirt.png"),
			MediaDirectory.File("Images/fancy_RedWood.png"),
		});
		ChunkManager.Texture.Assign(128, 64, files);
	}
	{
		VoxelTemplate::OrientationCube.InitCube(0);
		VoxelTemplate::OrientationCylinder.InitCylinder(0);
		VoxelTemplate::Gray.InitCube(1);
		VoxelTemplate::Grass.InitCube(2);
		VoxelTemplate::RedLog.InitCylinder(3);
	}
}
void VoxelGraphicsDelete()
{
	ChunkManager.GraphicsCreate();
}



PolyHedra * VoxelCube;
PolyHedra * VoxelChunkCube;

BoxF3 ViewBox = BoxF3(
	VectorF3(-0.4f, -1.2f, -0.4f),
	VectorF3(+0.4f, +0.4f, +0.4f)
);
PolyHedra * ViewBoxCube;

PolyHedra * ViewRayPolyHedra;

void PolyHedraBoxEdges(PolyHedra & polyhedra, BoxF3 box)
{
	polyhedra.Corners.Insert(PolyHedra::Corner(Point3D(box.Min.X, box.Min.Y, box.Min.Z))); // 000
	polyhedra.Corners.Insert(PolyHedra::Corner(Point3D(box.Max.X, box.Min.Y, box.Min.Z))); // 001
	polyhedra.Corners.Insert(PolyHedra::Corner(Point3D(box.Min.X, box.Max.Y, box.Min.Z))); // 010
	polyhedra.Corners.Insert(PolyHedra::Corner(Point3D(box.Max.X, box.Max.Y, box.Min.Z))); // 011
	polyhedra.Corners.Insert(PolyHedra::Corner(Point3D(box.Min.X, box.Min.Y, box.Max.Z))); // 100
	polyhedra.Corners.Insert(PolyHedra::Corner(Point3D(box.Max.X, box.Min.Y, box.Max.Z))); // 101
	polyhedra.Corners.Insert(PolyHedra::Corner(Point3D(box.Min.X, box.Max.Y, box.Max.Z))); // 110
	polyhedra.Corners.Insert(PolyHedra::Corner(Point3D(box.Max.X, box.Max.Y, box.Max.Z))); // 111

	polyhedra.Edges.Insert(PolyHedra::Edge(0b000, 0b001));
	polyhedra.Edges.Insert(PolyHedra::Edge(0b010, 0b011));
	polyhedra.Edges.Insert(PolyHedra::Edge(0b100, 0b101));
	polyhedra.Edges.Insert(PolyHedra::Edge(0b110, 0b111));

	polyhedra.Edges.Insert(PolyHedra::Edge(0b000, 0b010));
	polyhedra.Edges.Insert(PolyHedra::Edge(0b001, 0b011));
	polyhedra.Edges.Insert(PolyHedra::Edge(0b100, 0b110));
	polyhedra.Edges.Insert(PolyHedra::Edge(0b101, 0b111));

	polyhedra.Edges.Insert(PolyHedra::Edge(0b000, 0b100));
	polyhedra.Edges.Insert(PolyHedra::Edge(0b001, 0b101));
	polyhedra.Edges.Insert(PolyHedra::Edge(0b010, 0b110));
	polyhedra.Edges.Insert(PolyHedra::Edge(0b011, 0b111));
}

void Make() override
{
//	window.DefaultColor = ColorF4(1, 1, 1);
//	view.Depth.Factors.ChangeFar(50.0f);
	//view.Trans.Position = VectorF3(0, 7, 7);
//	view.Trans.Position = VectorF3(0.5f, 2.5f, 7.5f);
	view.Trans.Position = VectorF3(0.5f, 0.5f, 0.5f);

	{
		// this is needed to prevent compiler from complaining about multiple definitions of Bool2D
		Image img(Undex2D(1, 1));
		PolyHedra * picture = PolyHedra::Generate::DuoHedra(img);
		delete picture;
	}
	{
		VoxelCube = new PolyHedra();
		PolyHedraBoxEdges(*VoxelCube, BoxF3(VectorF3(0.0f), VectorF3(1.0f)));
		PolyHedraManager.PlacePolyHedra(VoxelCube);
		ChunkManager.VoxelBoxPolyHedra = VoxelCube;
	}
	{
		VoxelChunkCube = new PolyHedra();
		PolyHedraBoxEdges(*VoxelChunkCube, BoxF3(VectorF3(), VectorF3(CHUNK_VALUES_PER_SIDE)));
		PolyHedraManager.PlacePolyHedra(VoxelChunkCube);
		ChunkManager.ChunkBoxPolyHedra = VoxelChunkCube;
	}
	{
		ViewBoxCube = new PolyHedra();
		PolyHedraBoxEdges(*ViewBoxCube, ViewBox);
		PolyHedraManager.PlacePolyHedra(ViewBoxCube);
	}
	{
		ViewRayPolyHedra = PolyHedra::Generate::ConeC(8, 0.01f, 0.1f);
		PolyHedraManager.PlacePolyHedra(ViewRayPolyHedra);
		ChunkManager.ViewRayPolyHedra = ViewRayPolyHedra;
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

	Multiform_Depth.ChangeData(view.Depth);
	Multiform_FOV.ChangeData(view.FOV);
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

bool ShowText = true;

bool ShowTiles = false;
bool ShowVoxels = true;

bool IgnoreCollision = true;
bool ViewBack = false;



static VectorF3 VectorAbsolute(VectorF3 vec)
{
	if (vec.X < 0) { vec.X = -vec.X; }
	if (vec.Y < 0) { vec.Y = -vec.Y; }
	if (vec.Z < 0) { vec.Z = -vec.Z; }
	return vec;
}
static VectorI3 VectorAxisRank(VectorF3 vec)
{
	VectorI3 ret;

	float * vI = (float*)&vec;
	int * vO = (int*)&ret;

	for (unsigned int i = 0; i < 3; i++)
	{
		if (!(vI[i] == vI[i])) { vO[i] = -1; }
		if (vI[i] < 0) { vI[i] = -vI[i]; }
	}

	for (unsigned int i0 = 0; i0 < 3; i0++)
	{
		for (unsigned int i1 = 0; i1 < 3; i1++)
		{
			if (i0 != i1)
			{
				if (vI[i0] > vI[i1])
				{
					vO[i0]++;
				}
			}
		}
	}
	return ret;
}

static VectorF3 BoxAxisCollision(BoxF3 box0, VectorF3 vel0, BoxF3 box1)
{
	VectorF3 pos0;
	if (vel0.X > 0.0f) { pos0.X = box0.Max.X; } else { pos0.X = box0.Min.X; }
	if (vel0.Y > 0.0f) { pos0.Y = box0.Max.Y; } else { pos0.Y = box0.Min.Y; }
	if (vel0.Z > 0.0f) { pos0.Z = box0.Max.Z; } else { pos0.Z = box0.Min.Z; }

	VectorF3 pos1;
	if (vel0.X > 0.0f) { pos1.X = box1.Min.X; } else { pos1.X = box1.Max.X; }
	if (vel0.Y > 0.0f) { pos1.Y = box1.Min.Y; } else { pos1.Y = box1.Max.Y; }
	if (vel0.Z > 0.0f) { pos1.Z = box1.Min.Z; } else { pos1.Z = box1.Max.Z; }

	return (pos1 - pos0) / vel0;
}
static VectorF3 BoxCollision(BoxF3 box0, VectorF3 vel0, BoxF3 box1)
{
	VectorF3 t = BoxAxisCollision(box0, vel0, box1);

	if (t.X < 0.0f) { t.X = 0.0f / 0.0f; }
	if (t.Y < 0.0f) { t.Y = 0.0f / 0.0f; }
	if (t.Z < 0.0f) { t.Z = 0.0f / 0.0f; }

	if (t.X > 0.0f) // not NaN
	{
		BoxF3 box = box0 + (vel0 * t.X);
		box.Min.X = -1.0f/0.0f; // -Infinity
		box.Max.X = +1.0f/0.0f; // +Infinity
		if (!box.IntersectBoxInclusive(box1).All(true))
		{
			t.X = 0.0f / 0.0f; // no Collision
		}
	}
	if (t.Y > 0.0f) // not NaN
	{
		BoxF3 box = box0 + (vel0 * t.Y);
		box.Min.Y = -1.0f/0.0f; // -Infinity
		box.Max.Y = +1.0f/0.0f; // +Infinity
		if (!box.IntersectBoxInclusive(box1).All(true))
		{
			t.Y = 0.0f / 0.0f; // no Collision
		}
	}
	if (t.Z > 0.0f) // not NaN
	{
		BoxF3 box = box0 + (vel0 * t.Z);
		box.Min.Z = -1.0f/0.0f; // -Infinity
		box.Max.Z = +1.0f/0.0f; // +Infinity
		if (!box.IntersectBoxInclusive(box1).All(true))
		{
			t.Z = 0.0f / 0.0f; // no Collision
		}
	}

	return t;
}

struct TimeBoxCollision
{
	float		Time;
	VectorF3	Normal;

	TimeBoxCollision()
		: Time(0.0f/0.0f)
		, Normal()
	{ }
	void Consider(VectorF3 t, VectorF3 dir)
	{
		float time;
		VectorF3 normal;
		VectorI3 ranks = VectorAxisRank(t);
		     if (ranks.X == 0) { time = t.X; normal = VectorF3(dir.X, 0, 0); }
		else if (ranks.Y == 0) { time = t.Y; normal = VectorF3(0, dir.Y, 0); }
		else if (ranks.Z == 0) { time = t.Z; normal = VectorF3(0, 0, dir.Z); }
		else { return; }
		if (Time != Time || Time > time)
		{
			Time = time;
			Normal = normal;
		}
	}
};

TimeBoxCollision FindTimeBoxCollision(BoxF3 box, VectorF3 off, VectorF3 vel, LoopI3 loop)
{
	TimeBoxCollision collision;
	for (VectorI3 i = loop.Min(); loop.Check(i).All(true); loop.Next(i))
	{
		const Voxel * voxel = ChunkManager.FindVoxelOrNull(i);
		if (voxel != nullptr && voxel -> Template != nullptr)
		{
			BoxF3 voxel_box(i + VectorI3(0, 0, 0), i + VectorI3(1, 1, 1));
			if (box.IntersectBoxInclusive(voxel_box).All(true)) { continue; }
			{
				VectorF3 t = BoxCollision(box + off, vel, voxel_box);
				VectorF3 dir;
				if (vel.X > 0.0f) { dir.X = +1.0f; } else { dir.X = -1.0f; }
				if (vel.Y > 0.0f) { dir.Y = +1.0f; } else { dir.Y = -1.0f; }
				if (vel.Z > 0.0f) { dir.Z = +1.0f; } else { dir.Z = -1.0f; }
				collision.Consider(t, -dir);
			}
		}
	}
	return collision;
}



bool		ViewRaySync = true;
Ray3D		ViewRay;
void ViewRayFunction()
{
	VectorI3 idx;
	Axis side;
	Ray3D hit;
	if (ChunkManager.FindVoxelIndex(ViewRay, idx, side, hit))
	{
		{
			PolyHedraObject voxel_box_obj(VoxelCube);
			voxel_box_obj.Trans().Position = idx;
			voxel_box_obj.ShowWire();
		}
		/*{
			PolyHedraObject voxel_dir_obj(ViewRayPolyHedra);
			voxel_dir_obj.Trans().Position = hit.Pos;
			voxel_dir_obj.Trans().Rotation = EulerAngle3D::PointToZ(hit.Dir);
			voxel_dir_obj.ShowWire();
		}*/

		{
			VectorI3 chunk_idx = (VectorF3(idx) / (float)CHUNK_VALUES_PER_SIDE).roundF(); // make intager division round down;
			VectorU3 voxel_idx = idx - (chunk_idx * CHUNK_VALUES_PER_SIDE);

			std::stringstream ss;

			ss << "ViewRay\n";
			ss << idx << '\n';
			ss << chunk_idx << '\n';
			ss << voxel_idx << '\n';

			{
				const Voxel * voxel = ChunkManager.FindVoxelOrNull(idx);
				if (voxel != nullptr)
				{
					ss << (voxel -> Orientation.GetDiag()) << " :Diag\n";
					ss << (voxel -> Orientation.GetFlip()) << " :Flip\n";
					ss << (voxel -> Orientation.absolute(Axis::PrevX)) << " :PrevX\n";
					ss << (voxel -> Orientation.absolute(Axis::PrevY)) << " :PrevY\n";
					ss << (voxel -> Orientation.absolute(Axis::PrevZ)) << " :PrevZ\n";
					ss << (voxel -> Orientation.absolute(Axis::NextX)) << " :NextX\n";
					ss << (voxel -> Orientation.absolute(Axis::NextY)) << " :NextY\n";
					ss << (voxel -> Orientation.absolute(Axis::NextZ)) << " :NextZ\n";
					//ss << (voxel -> Orientation.Diag) << ":Diag\n";
					//ss << (voxel -> Orientation.Flip) << ":Flip\n";
					//ss << (voxel -> Orientation.Origin0) << ":Origin0\n";
					//ss << (voxel -> Orientation.Target0) << ":Target0\n";
					//ss << (voxel -> Orientation.Origin1) << ":Origin1\n";
					//ss << (voxel -> Orientation.Target1) << ":Target1\n";
				}
				else
				{
					ss << "null";
				}
				ss << '\n';
			}

			UI::Text::Object text; text.Create();
			text.Pos().X = window.Size.Buffer.Full.X - 10;
			text.Pos().Y = 10;
			text.AlignmentX() = UI::Text::Alignment::Max;
			text.Bound().Min = Point2D();
			text.Bound().Max = window.Size.Buffer.Full;
			text.String() = ss.str();
		}

		if (window.MouseManager[MouseButtons::MouseL].State == State::Press)
		{
			Voxel voxel;
			ChunkManager.ClearVoxel(idx, voxel);
		}
		if (window.MouseManager[MouseButtons::MouseR].State == State::Press)
		{
			if (side == Axis::NextX) { idx.X += 1; }
			if (side == Axis::NextY) { idx.Y += 1; }
			if (side == Axis::NextZ) { idx.Z += 1; }
			if (side == Axis::PrevX) { idx.X -= 1; }
			if (side == Axis::PrevY) { idx.Y -= 1; }
			if (side == Axis::PrevZ) { idx.Z -= 1; }

			Voxel voxel;
			voxel.Template = &VoxelTemplate::OrientationCube;
			voxel.Orientation.make(Axis::PrevY, side, Axis::None, Axis::None);
			ChunkManager.PlaneVoxel(idx, voxel);
		}
	}

	if (window.KeyBoardManager[Keys::NumPadEnter].State == State::Press)
	{
		VectorI3 view_chunk_idx(view.Trans.Position.roundF() / (float)CHUNK_VALUES_PER_SIDE);
		Chunk * view_chunk = ChunkManager.FindChunkOrNull(view_chunk_idx);
		if (view_chunk != nullptr)
		{
			view_chunk -> GenerateTestRotation();
		}
	}
}

VectorF3	GravityForce = VectorF3(0, -0.1f, 0);
VectorF3	ViewVel;

void UpdateViewColliding(FrameTime frame_time)
{
	Trans3D change;

	if (window.KeyBoardManager[Keys::Tab].State == State::Press) { window.MouseManager.CursorModeToggle(); }
	if (window.MouseManager.CursorModeIsLocked())
	{
		change = window.MoveSpinFromKeysCursor();
		//change.Position = window.MoveFromKeys();
		if (window.KeyBoardManager[Keys::LeftControl].State == State::Down) { change.Position *= 10; }
		change.Position *= 2;
		change.Rotation *= view.FOV.ToRadians() * 0.05f;
		{
			EulerAngle3D e(Angle(), Angle(), view.Trans.Rotation.Y2);
			change.Position = e.forward(change.Position);
		}
	}

	change.Position *= frame_time.Delta;
	change.Rotation *= frame_time.Delta;

	if (!IgnoreCollision)
	{
		{
			PolyHedraObject view_box_obj(ViewBoxCube);
			view_box_obj.Trans().Position = view.Trans.Position;
			view_box_obj.ShowWire();
		}

		int size = 2;
		VectorI3 center = view.Trans.Position.roundF();
		LoopI3 loop(center - VectorI3(size), Bool3(false), center + VectorI3(size), Bool3(false));

		{
			unsigned int p = PolyHedraManager.FindPolyHedra(VoxelCube);
			for (VectorI3 i = loop.Min(); loop.Check(i).All(true); loop.Next(i))
			{
				const Voxel * voxel = ChunkManager.FindVoxelOrNull(i);
				if (voxel != nullptr && voxel -> Template != nullptr)
				{
					PolyHedraObject voxel_obj(p);
					voxel_obj.Trans().Position = i;
					voxel_obj.ShowWire();
				}
			}
		}

		BoxF3 view_box_old = ViewBox + view.Trans.Position;
		ViewVel -= ViewVel * 0.5f;
		ViewVel += change.Position;
		ViewVel += GravityForce;

		VectorF3 rel;
		//VectorF3 vel = change.Position;
		VectorF3 & vel = ViewVel;

		float time_limit = 1.0f;
		for (unsigned int l = 0; l < 4; l++)
		{
			TimeBoxCollision collision = FindTimeBoxCollision(view_box_old, rel, vel, loop);
			if (collision.Time <= time_limit)
			{
				rel += vel * collision.Time;
				time_limit -= collision.Time;
				float dot = collision.Normal.dot(vel);
				if (dot < 0.0f)
				{
					vel -= (collision.Normal * dot);
					rel += (collision.Normal * 0.01f);
				}
			}
			else { break; }
		}
		if (time_limit > 0.0f)
		{
			rel += vel * time_limit;
		}

		//change.Position = rel;

		view.Trans.Position += ViewVel;
		view.Trans.Rotation += change.Rotation;
		view.Trans.Rotation.X1.clampPI();

		{
			PolyHedraObject view_box_obj(ViewBoxCube);
			view_box_obj.Trans().Position = view.Trans.Position;
			view_box_obj.ShowWire();
		}
	}
	else
	{
		ViewVel = VectorF3();
		view.Trans.Position += change.Position;
		view.Trans.Rotation += change.Rotation;
		view.Trans.Rotation.X1.clampPI();

		/*{
			PolyHedraObject view_box_obj(ViewBoxCube);
			view_box_obj.Trans().Position = view.Trans.Position;
			view_box_obj.ShowWire();
		}*/
	}
}

void Draw()
{
	PolyHedraManager.ClearInstances();
	PolyHedraManager.UpdateInstances();
	if (ShowFull) { PolyHedraManager.DrawFull(); }
	if (ShowWire) { PolyHedraManager.DrawWire(); }
	if (ShowTiles) { PlaneManager.Draw(); }
	if (ShowVoxels) { ChunkManager.Draw(); }

	GL::Clear(GL::ClearMask::DepthBufferBit);
	if (ShowText)
	{
		TextManager.Draw();
	}
}

void UpdateAroundView(FrameTime frame_time)
{
	UpdateViewColliding(frame_time);
	if (!ViewBack)
	{
		Multiform_View.ChangeData(Matrix4x4::TransformReverse(view.Trans));
	}
	else
	{
		Multiform_View.ChangeData(Matrix4x4::TransformReverse(Trans3D(view.Trans.Position - view.Trans.Rotation.forward(Point3D(0, 0, 3)), view.Trans.Rotation)));
	}

	ChunkManager.RemoveAround(view.Trans.Position, 5);

	if (ViewRaySync)
	{
		ViewRay.Pos = view.Trans.Position;
		ViewRay.Dir = view.Trans.Rotation.forward(VectorF3(0, 0, 1));
		//ViewRay.Dir.Z = 0.0f;
		//ViewRay.Dir = !ViewRay.Dir;
	}
	ViewRayFunction();

	ChunkManager.InsertAround(view.Trans.Position, 2);
	ChunkManager.GenerateAround(Perlin2, Perlin3, view.Trans.Position, 2, 1);

	PlaneManager.UpdateAround(Perlin2, Point2D(view.Trans.Position.X, view.Trans.Position.Z));
}

void Frame(double timeDelta) override
{
	FrameTime frame_time(64);
	frame_time.Update(timeDelta);

	if (window.KeyBoardManager[Keys::D1].State == State::Press) { ShowFull = !ShowFull; }
	if (window.KeyBoardManager[Keys::D2].State == State::Press) { ShowWire = !ShowWire; }
	if (window.KeyBoardManager[Keys::D3].State == State::Press) { ShowText = !ShowText; }
	if (window.KeyBoardManager[Keys::D4].State == State::Press) { ShowTiles = !ShowTiles; }
	if (window.KeyBoardManager[Keys::D5].State == State::Press) { ShowVoxels = !ShowVoxels; }

	if (window.KeyBoardManager[Keys::F1].State == State::Press) { ViewRaySync = !ViewRaySync; }
	if (window.KeyBoardManager[Keys::F2].State == State::Press) { IgnoreCollision = !IgnoreCollision; }
	if (window.KeyBoardManager[Keys::F3].State == State::Press) { ViewBack = !ViewBack; }
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

	UpdateAroundView(frame_time);

	/*if (ShowWire)
	{
		unsigned int p = PolyHedraManager.FindPolyHedra(VoxelChunkCube);
		for (unsigned int i = 0; i < ChunkManager.Chunks.Count(); i++)
		{
			PolyHedraObject chunk_box(p);
			chunk_box.Create(VoxelChunkCube);
			chunk_box.Trans().Position = (ChunkManager.Chunks[i] -> Index) * CHUNK_VALUES_PER_SIDE;
			chunk_box.ShowWire();
		}
	}*/

	{
		std::stringstream ss;

		{
			ss << "Frame Hz(" << frame_time.WantedFramesPerSecond << '|' << frame_time.ActualFramesPerSecond << ")\n";
			ss << "Frame D(" << frame_time.WantedFrameTime << '|' << frame_time.ActualFrameTime << ")\n";
			ss << '\n';
		}

		/*{
			ss << "0123456789+-* /=<>" << '\n';
			ss << "()[]{}#~'\"_|&%$" << '\n';
			ss << "ABCDEFGHIJKLM" << '\n';
			ss << "NOPQRSTUVWXYZ" << '\n';
			ss << "abcdefghijklm" << '\n';
			ss << "nopqrstuvwxyz" << '\n';
			ss << ".,:;!?" << '\n';
			ss << '\n';
		}*/

		/*{
			ss << "[1] " << "PolyHedra Full:" << (ShowFull ? "Show" : "Hide") << '\n';
			ss << "[2] " << "PolyHedra Wire:" << (ShowWire ? "Show" : "Hide") << '\n';
			ss << "[3] " << "Text:" << (ShowText ? "Show" : "Hide") << '\n';
			ss << "[4] " << "TilePlanes:" << (ShowTiles ? "Show" : "Hide") << '\n';
			ss << "[5] " << "VoxelChunks:" << (ShowVoxels ? "Show" : "Hide") << '\n';
			ss << '\n';
			ss << "[F2] " << "IgnoreCollision:" << (IgnoreCollision ? "true" : "false") << '\n';
			ss << "[F3] " << "ViewBack:" << (ViewBack ? "true" : "false") << '\n';
			ss << "[F4] " << "Planes.ShouldGenerate:" << (PlaneManager.ShouldGenerate ? "true" : "false") << '\n';
			ss << "[F4] " << "Chunks.ShouldGenerate:" << (ChunkManager.ShouldGenerate ? "true" : "false") << '\n';
			ss << "[F5] " << "Clear Planes" << '\n';
			ss << "[F5] " << "Clear Chunks" << '\n';
			ss << '\n';
		}*/

		{
			ss << "View " << view.Trans.Position << '\n';
			ss << "View " << ViewVel << '\n';
			//ss << "Box " << (ViewBox + view.Trans.Position) << '\n';
			VectorI3 chunk_idx = (view.Trans.Position / (float)CHUNK_VALUES_PER_SIDE).roundF();
			VectorU3 voxel_idx = VectorI3(view.Trans.Position.roundF()) - (chunk_idx * CHUNK_VALUES_PER_SIDE);
			ss << "Voxel " << chunk_idx << ' ' << voxel_idx << '\n';
			ss << '\n';
		}

		{
			unsigned int count = PolyHedraManager.InstanceManagers.Count();
			unsigned int all_count = PolyHedraManager.ObjectDatas.Count();
			unsigned int full_count = 0;
			unsigned int wire_count = 0;
			for (unsigned int i = 0; i < count; i++)
			{
				full_count += PolyHedraManager.InstanceManagers[i].InstancesFull.Count();
				wire_count += PolyHedraManager.InstanceManagers[i].InstancesWire.Count();
			}
			ss << "PolyHedra Main|Inst " << count << '|' << all_count << '\n';
			ss << "Full|Wire" << ' ' << full_count << '|' << wire_count << '\n';
			ss << '\n';
		}

		{
			unsigned int count_planes = PlaneManager.Planes.Count();
			unsigned int count_tiles = count_planes * PLANE_VALUES_PER_AREA;
			ss << "Planes|Tiles:" << count_planes << '|' << count_tiles;
			ss << " (" << Memory1000ToString(count_tiles * sizeof(float)) << ")\n";
			ss << '\n';
		}

		{
			unsigned int chunks_t = ChunkManager.Chunks.Count(); // total
			unsigned int chunks_u = 0; // ungenerated
			unsigned int chunks_f = 0; // filled
			unsigned int chunks_e = 0; // empty
			unsigned int voxel_count = 0;
			for (unsigned int i = 0; i < ChunkManager.Chunks.Count(); i++)
			{
				Chunk & chunk = *ChunkManager.Chunks[i];
				if (chunk.ChunkType == ChunkType::UnGenerated) { chunks_u++; }
				if (chunk.ChunkType == ChunkType::Filled) { chunks_f++; voxel_count += CHUNK_VALUES_PER_VOLM; }
				if (chunk.ChunkType == ChunkType::Empty) { chunks_e++; voxel_count += 1; }
			}
			ss << "Chunks"
			 << ':' << chunks_t << '['
			 << 'U' << chunks_u << '|'
			 << 'E' << chunks_e << '|'
			 << 'F' << chunks_f << ']'
			 << '\n';
			ss << "Voxels:" << Seperated1000(voxel_count);
			ss << " * " << Memory1000ToString(sizeof(Voxel));
			ss << " = " << Memory1000ToString(voxel_count * sizeof(Voxel)) << '\n';
			ss << '\n';
		}

		{
			unsigned long long main_count = 0;
			for (unsigned int i = 0; i < ChunkManager.Chunks.Count(); i++)
			{
				main_count += ChunkManager.Chunks[i] -> MainCount;
			}
			ss << "Voxel BufferData: " << Seperated1000(main_count);
			ss << " (" << Memory1000ToString(main_count * sizeof(VoxelGraphics::MainData)) <<")\n";
		}

		UI::Text::Object text; text.Create();
		text.Pos().X = 10;
		text.Pos().Y = 10;
		text.Bound().Min = Point2D();
		text.Bound().Max = window.Size.Buffer.Full;
		text.String() = ss.str();
	}

	Draw();
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
