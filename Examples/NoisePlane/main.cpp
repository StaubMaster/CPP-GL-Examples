
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
#include "Voxel/ChunkManager.hpp"

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

struct MainContext : public MainContext3D
{
::PolyHedraManager		PolyHedraManager;
UI::Text::Manager		TextManager;
::PlaneManager			PlaneManager;
::ChunkManager			ChunkManager;

Perlin2D				Perlin0;

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
	, Perlin0(Perlin2D::Random(Undex2D(8, 8)))
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
			MediaDirectory.File("Images/fancy_GreenDirt.png"),
			MediaDirectory.File("Images/Wood.png"),
		});
		ChunkManager.Texture.Assign(128, 64, files);
	}
}
void VoxelGraphicsDelete()
{
	ChunkManager.GraphicsCreate();
}



PolyHedra * VoxelCube;
PolyHedra * VoxelChunkCube;

BoxF3 ViewBox = BoxF3(
	VectorF3(-0.4f, -0.4f, -0.4f),
	VectorF3(+0.4f, +0.4f, +0.4f)
);
PolyHedra * ViewBoxCube;

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
	view.Depth.Factors.ChangeFar(50.0f);
	Multiform_Depth.ChangeData(view.Depth);
	Multiform_FOV.ChangeData(view.FOV);

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
	}
	{
		VoxelChunkCube = new PolyHedra();
		PolyHedraBoxEdges(*VoxelChunkCube, BoxF3(VectorF3(), VectorF3(CHUNK_VALUES_PER_SIDE)));
		PolyHedraManager.PlacePolyHedra(VoxelChunkCube);
	}
	{
		ViewBoxCube = new PolyHedra();
		PolyHedraBoxEdges(*ViewBoxCube, ViewBox);
		PolyHedraManager.PlacePolyHedra(ViewBoxCube);
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

bool ShowText = true;

bool ShowTiles = true;
bool ShowVoxels = true;

/* Collision
do as part of View Update
Calculate Movement Direction

check for collision with current Position

move Box in that direction.
for all boxes not currently colliding
	check for collision.
	if collision
		get collision normal
		remove normal part. so only perpendicular remains

keep doing until all Boxes in area are checked

add result to current position

have a way to turn off collision, for testing

*/

VectorF3 Absolute(VectorF3 vec)
{
	if (vec.X < 0) { vec.X = -vec.X; }
	if (vec.Y < 0) { vec.Y = -vec.Y; }
	if (vec.Z < 0) { vec.Z = -vec.Z; }
	return vec;
}
VectorI3 RankAbs(VectorF3 vec)
{
	float * vI = (float*)&vec;
	for (unsigned int i = 0; i < 3; i++)
	{
		if (vI[i] < 0) { vI[i] = -vI[i]; }
	}
	VectorI3 ret;
	int * vO = (int*)&ret;
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

bool IgnoreCollision = true;
bool ViewBack = false;

void UpdateViewColliding(FrameTime frame_time)
{
	Trans3D change;

	// Input
	if (window.KeyBoardManager[Keys::Tab].State == State::Press) { window.MouseManager.CursorModeToggle(); }
	if (window.MouseManager.CursorModeIsLocked())
	{
		change = window.MoveSpinFromKeysCursor();
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

	{
		PolyHedraObject view_box_obj(ViewBoxCube);
		view_box_obj.Trans().Position = view.Trans.Position;
		view_box_obj.ShowWire();
	}

	if (!IgnoreCollision)
	{
		BoxF3 view_box_old = ViewBox + view.Trans.Position;
		unsigned int p = PolyHedraManager.FindPolyHedra(VoxelCube);
		int size = 2;
		VectorI3 center = view.Trans.Position.roundF();
		LoopI3 loop(center - VectorI3(size), Bool3(false), center + VectorI3(size), Bool3(false));
		for (VectorI3 i = loop.Min(); loop.Check(i).All(true); loop.Next(i))
		{
			Voxel * voxel = ChunkManager[i];
			if (voxel != nullptr && (voxel -> IsSolid()))
			{
				{
					PolyHedraObject voxel_obj(p);
					voxel_obj.Trans().Position = i;
					voxel_obj.ShowWire();
				}
				BoxI3 voxel_box(i + VectorI3(0, 0, 0), i + VectorI3(1, 1, 1));
				if (view_box_old.IntersectBoxInclusive(voxel_box).All(true))
				{
					continue;
				}

				{
					BoxF3 view_box_new = view_box_old + change.Position;
					if (view_box_new.IntersectBoxInclusive(voxel_box).All(true))
					{
						// turn into function. Collision between a moving and a non-moving Box
						// also make one for where both move. that would return 2 t for both Boxes

						VectorF3 & vel = change.Position;
						std::cout << "vel " << vel << '\n';

						VectorF3 pos0;
						std::cout << "pos0";
						if (vel.X > 0.0f) { pos0.X = view_box_old.Max.X; std::cout << " Max"; } else { pos0.X = view_box_old.Min.X; std::cout << " Min"; }
						if (vel.Y > 0.0f) { pos0.Y = view_box_old.Max.Y; std::cout << " Max"; } else { pos0.Y = view_box_old.Min.Y; std::cout << " Min"; }
						if (vel.Z > 0.0f) { pos0.Z = view_box_old.Max.Z; std::cout << " Max"; } else { pos0.Z = view_box_old.Min.Z; std::cout << " Min"; }
						std::cout << '\n';

						VectorF3 pos1;
						std::cout << "pos1";
						if (vel.X > 0.0f) { pos1.X = voxel_box.Min.X; std::cout << " Min"; } else { pos1.X = voxel_box.Max.X; std::cout << " Max"; }
						if (vel.Y > 0.0f) { pos1.Y = voxel_box.Min.Y; std::cout << " Min"; } else { pos1.Y = voxel_box.Max.Y; std::cout << " Max"; }
						if (vel.Z > 0.0f) { pos1.Z = voxel_box.Min.Z; std::cout << " Min"; } else { pos1.Z = voxel_box.Max.Z; std::cout << " Max"; }
						std::cout << '\n';

						std::cout << "pos0 " << pos0 << '\n';
						std::cout << "pos1 " << pos1 << '\n';

						// pos0 + vel * t = pos1
						// (pos1 - pos0) / vel = t
						VectorF3 t = (pos1 - pos0) / vel;
						std::cout << "t " << t << '\n';
						// which happens first ?

						VectorI3 ranks = RankAbs(t);
						std::cout << "ranks " << ranks << '\n';

						VectorF3 normal;
						     if (ranks.X == 0) { if (vel.X > 0.0f) { normal.X = +1; } else { normal.X = -1; } }
						else if (ranks.Y == 0) { if (vel.Y > 0.0f) { normal.Y = +1; } else { normal.Y = -1; } }
						else if (ranks.Z == 0) { if (vel.Z > 0.0f) { normal.Z = +1; } else { normal.Z = -1; } }
						// normal direction based on vel
						std::cout << "normal " << normal << '\n';

						if (normal.length2() != 0) // check for lenght == 1
						{
							float dot = normal.dot(vel);
							VectorF3 normal_vel = normal * (dot / normal.length()); // normalize normal before this ?
							vel = vel - normal_vel;
						}
					}
				}
			}
		}
	}

	view.Trans.Position += change.Position;
	view.Trans.Rotation += change.Rotation;
	view.Trans.Rotation.X1.clampPI();
}

void Frame(double timeDelta) override
{
	FrameTime frame_time(64);
	frame_time.Update(timeDelta);
	UpdateViewColliding(frame_time);
	if (!ViewBack)
	{
		Multiform_View.ChangeData(Matrix4x4::TransformReverse(view.Trans));
	}
	else
	{
		Multiform_View.ChangeData(Matrix4x4::TransformReverse(Trans3D(view.Trans.Position - view.Trans.Rotation.forward(Point3D(0, 0, 10)), view.Trans.Rotation)));
	}

	PlaneManager.UpdateAround(Perlin0, Point2D(view.Trans.Position.X, view.Trans.Position.Z));
	ChunkManager.UpdateAround(Perlin0, view.Trans.Position);

	if (window.KeyBoardManager[Keys::D1].State == State::Press) { ShowFull = !ShowFull; }
	if (window.KeyBoardManager[Keys::D2].State == State::Press) { ShowWire = !ShowWire; }
	if (window.KeyBoardManager[Keys::D3].State == State::Press) { ShowText = !ShowText; }
	if (window.KeyBoardManager[Keys::D4].State == State::Press) { ShowTiles = !ShowTiles; }
	if (window.KeyBoardManager[Keys::D5].State == State::Press) { ShowVoxels = !ShowVoxels; }

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

	// Chunk Boxes
	{
		unsigned int p = PolyHedraManager.FindPolyHedra(VoxelChunkCube);
		for (unsigned int i = 0; i < ChunkManager.Chunks.Count(); i++)
		{
			PolyHedraObject chunk_box(p);
			chunk_box.Create(VoxelChunkCube);
			chunk_box.Trans().Position = (ChunkManager.Chunks[i] -> Index) * CHUNK_VALUES_PER_SIDE;
			chunk_box.ShowWire();
		}
	}

	PolyHedraManager.ClearInstances();
	PolyHedraManager.UpdateInstances();
	if (ShowFull)
	{
		PolyHedraManager.ShaderFullDefault.Bind();
		PolyHedraManager.ShaderFullDefault.Depth.Put(view.Depth);
		PolyHedraManager.ShaderFullDefault.FOV.Put(view.FOV);
		PolyHedraManager.DrawFull();
	}
	if (ShowWire)
	{
		PolyHedraManager.ShaderWireDefault.Bind();
		PolyHedraManager.ShaderWireDefault.Depth.Put(view.Depth);
		PolyHedraManager.ShaderWireDefault.FOV.Put(view.FOV);
		PolyHedraManager.DrawWire();
	}
	if (ShowTiles)
	{
		PlaneManager.Shader.Bind();
		PlaneManager.Shader.Depth.Put(view.Depth);
		PlaneManager.Shader.FOV.Put(view.FOV);
		PlaneManager.Draw();
	}
	if (ShowVoxels)
	{
		ChunkManager.Shader.Bind();
		ChunkManager.Shader.Depth.Put(view.Depth);
		ChunkManager.Shader.FOV.Put(view.FOV);
		ChunkManager.Draw();
	}

	GL::Clear(GL::ClearMask::DepthBufferBit);
	{
		std::stringstream ss;

		{
			ss << "Frame Hz(" << frame_time.WantedFramesPerSecond << '|' << frame_time.ActualFramesPerSecond << ")\n";
			ss << "Frame D(" << frame_time.WantedFrameTime << '|' << frame_time.ActualFrameTime << ")\n";
			ss << '\n';
		}

		{
			ss << "0123456789+-* /=<>" << '\n';
			ss << "()[]{}#~'\"_|&" << '\n';
			ss << "ABCDEFGHIJKLM" << '\n';
			ss << "NOPQRSTUVWXYZ" << '\n';
			ss << "abcdefghijklm" << '\n';
			ss << "nopqrstuvwxyz" << '\n';
			ss << ".,:;!?" << '\n';
			ss << '\n';
		}

		{
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
		}

		// put all the control stuff together

		{
			ss << "View " << view.Trans.Position << '\n';
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
			ss << "PolyHedra " << PolyHedraManager.InstanceManagers.Count() << '|' << all_count << '\n';
			ss << "[1] Full " << (ShowFull ? "Show" : "Hide") << ' ' << full_count << '\n';
			ss << "[2] Wire " << (ShowWire ? "Show" : "Hide") << ' ' << wire_count << '\n';
			ss << '\n';
		}

		{
			unsigned int count_planes = PlaneManager.Planes.Count();
			unsigned int count_tiles = count_planes * PLANE_VALUES_PER_AREA;
			ss << "[4] Planes|Tiles:" << (ShowTiles ? "Show" : "Hide") << ' ' << count_planes << '|' << count_tiles << '\n';
			unsigned long long memory = count_tiles * sizeof(float);
			const char * factor = "B";
			if (memory >= 1000) { memory = memory / 1000; factor = "kB"; }
			if (memory >= 1000) { memory = memory / 1000; factor = "MB"; }
			ss << "Memory:" << memory << factor << "\n";
			ss << '\n';
		}

		{
			unsigned int count_chunks = ChunkManager.Chunks.Count();
			unsigned int count_voxels = count_chunks * CHUNK_VALUES_PER_VOLM;
			ss << "[5] Chunks|Voxels:" << (ShowVoxels ? "Show" : "Hide") << ' ' << count_chunks << '|' << count_voxels << '\n';
			unsigned long long memory = count_voxels * sizeof(float);
			const char * factor = "B";
			if (memory >= 1000) { memory = memory / 1000; factor = "kB"; }
			if (memory >= 1000) { memory = memory / 1000; factor = "MB"; }
			ss << "Memory:" << memory << factor << "\n";
			ss << '\n';
		}

		{
			unsigned long long main_count = 0;
			for (unsigned int i = 0; i < ChunkManager.Chunks.Count(); i++)
			{
				main_count += ChunkManager.Chunks[i] -> MainCount;
			}
			ss << "Main Count:" << main_count << '\n';
			unsigned long long memory = main_count * sizeof(VoxelGraphics::MainData);
			const char * factor = "B";
			if (memory >= 1000) { memory = memory / 1000; factor = "kB"; }
			if (memory >= 1000) { memory = memory / 1000; factor = "MB"; }
			ss << "Memory:" << memory << factor << "\n";
			ss << '\n';
		}

		UI::Text::Object text; text.Create();
		text.Pos().X = 10;
		text.Pos().Y = 10;
		text.Bound().Min = Point2D();
		text.Bound().Max = window.Size.Buffer.Full;
		text.String() = ss.str();
	}
	if (ShowText)
	{
		TextManager.Draw();
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
