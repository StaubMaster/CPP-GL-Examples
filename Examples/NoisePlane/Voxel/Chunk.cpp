#include "Chunk.hpp"
#include "VoxelTemplate.hpp"

#include "Graphics/Inst/Data.hpp"

#include "VoxelOrientation.hpp"

#include "ValueGen/Perlin2D.hpp"
#include "ValueGen/Perlin3D.hpp"

#include "ValueType/BoxI3.hpp"

#include "ValueType/Bool3.hpp"
#include "ValueType/VectorU3.hpp"

#include "ValueType/Undex2D.hpp"
#include "ValueType/UndexLoop2D.hpp"

#include "ValueType/Undex3D.hpp"
#include "ValueType/UndexLoop3D.hpp"



#include <iostream>
#include "ValueType/_Show.hpp"



bool	Chunk::Done() const { return GenerationState == GenerationState::Generated; }

Voxel &			Chunk::operator[](VectorU3 udx)			{ return Data[VectorU3::Convert(CHUNK_VALUES_PER_SIDE, udx)]; }
const Voxel &	Chunk::operator[](VectorU3 udx) const	{ return Data[VectorU3::Convert(CHUNK_VALUES_PER_SIDE, udx)]; }



Chunk::~Chunk()
{
	//std::cout << "  ----  Chunk: " << this << '\n';
	delete[] Data;
	if (GraphicsExist)
	{
		Buffer.Delete();
	}
}
Chunk::Chunk(VectorI3 idx, bool graphics_exist)
	: Data(nullptr)
	, Index(idx)
	, GenerationState(GenerationState::None)
	, Buffer()
	, GraphicsExist(false)
	, BufferNeedsInit(false)
	, MainBufferState(BufferDataState::None)
	, InstBufferNeedsData(false)
{
	//std::cout << "  ++++  Chunk: " << this << '\n';
	Buffer.Main.Pos.Change(0);
	Buffer.Main.Tex.Change(1);
	Buffer.Inst.Pos.Change(2);
	if (graphics_exist)
	{
		Buffer.Create();
		GraphicsExist = true;
		BufferNeedsInit = true;
		InstBufferNeedsData = true;
	}
}
//void Chunk::Dispose() { }



bool Chunk::IsEmpty() const
{
	return (Data == nullptr);
}
bool Chunk::IsNullOrEmpty() const
{
	if (IsEmpty()) { return true; }
	for (unsigned int i = 0; i < CHUNK_VALUES_PER_VOLM; i++)
	{
		if (Data[i].Template != nullptr)
		{
			return false;
		}
	}
	return true;
}
void Chunk::MakeEmpty()
{
	if (IsEmpty()) { return; }
	delete[] Data;
	Data = nullptr;
	Neighbours.UpdateBufferMain();
}
void Chunk::MakeNull()
{
	if (IsEmpty())
	{
		Data = new Voxel[CHUNK_VALUES_PER_VOLM];
	}
	for (unsigned int i = 0; i < CHUNK_VALUES_PER_VOLM; i++)
	{
		Data[i].Template = nullptr;
		Data[i].Orientation = VoxelOrientation();
	}
	Neighbours.UpdateBufferMain();
}



static void TestOrientation(Chunk & chunk, const VoxelTemplate & voxel_template, Diag diag, Flip flip, VectorU3 u)
{
	//unsigned int i = VectorU3::Convert(CHUNK_VALUES_PER_SIDE, u);
	chunk[u].Template = &voxel_template;
	chunk[u].Orientation.make(diag, flip);
}
static void TestOrientation(Chunk & chunk, const VoxelTemplate & voxel_template, unsigned int y)
{
	Diag diags[6] =
	{
		Diag::Here,
		Diag::Prev,
		Diag::Next,
		Diag::DiagX,
		Diag::DiagY,
		Diag::DiagZ,
	};
	Flip flips[4] = 
	{
		Flip::None,
		Flip::FlipX,
		Flip::FlipY,
		Flip::FlipZ,
	};

	unsigned int uX[6] { 0x0, 0x3, 0x6, 0x9, 0xC, 0xF };
	unsigned int uZ[4] { 0x0, 0x2, 0x4, 0x6 };

	for (unsigned int f = 0; f < 4; f++)
	{
		for (unsigned int d = 0; d < 6; d++)
		{
			TestOrientation(chunk, voxel_template, diags[d], flips[f], VectorU3(uX[d], y, uZ[f]));
		}
	}
}


/*
	0	1	2	3	4	5	6	7	8	9	A	B	C	D	E	F
		#		#		#		|	|		#		#		#	
	#			#			#	|	|	#			#			#
	#		#		#		#	|	|	#		#		#		#
*/

void Chunk::TestOrientation()
{
	MakeNull();
	::TestOrientation(*this, VoxelTemplate::OrientationCube, 0x0);
	::TestOrientation(*this, VoxelTemplate::OrientationCylinder, 0x2);
	::TestOrientation(*this, VoxelTemplate::OrientationSlope, 0x4);
}
void Chunk::TestHouse()
{
	MakeNull();
	unsigned int i;

	for (unsigned int x = 0x5; x <= 0xA; x++)
	{
		for (unsigned int z = 0x3; z <= 0xC; z++)
		{
			i = VectorU3::Convert(CHUNK_VALUES_PER_SIDE, VectorU3(x, 0, z));
			Data[i].Template = &VoxelTemplate::Grass;
			Data[i].Orientation.make(Diag::Here, Flip::None);
		}
	}

	for (unsigned int y = 0x1; y <= 0x4; y++)
	{
		i = VectorU3::Convert(CHUNK_VALUES_PER_SIDE, VectorU3(0x5, y, 0x3));
		Data[i].Template = &VoxelTemplate::RedLog;
		Data[i].Orientation.make(Diag::Here, Flip::None);
		i = VectorU3::Convert(CHUNK_VALUES_PER_SIDE, VectorU3(0xA, y, 0x3));
		Data[i].Template = &VoxelTemplate::RedLog;
		Data[i].Orientation.make(Diag::Here, Flip::None);
		i = VectorU3::Convert(CHUNK_VALUES_PER_SIDE, VectorU3(0x5, y, 0xC));
		Data[i].Template = &VoxelTemplate::RedLog;
		Data[i].Orientation.make(Diag::Here, Flip::None);
		i = VectorU3::Convert(CHUNK_VALUES_PER_SIDE, VectorU3(0xA, y, 0xC));
		Data[i].Template = &VoxelTemplate::RedLog;
		Data[i].Orientation.make(Diag::Here, Flip::None);
		for (unsigned int z = 0x4; z <= 0xB; z++)
		{
			i = VectorU3::Convert(CHUNK_VALUES_PER_SIDE, VectorU3(0x5, y, z));
			Data[i].Template = &VoxelTemplate::RedLog;
			Data[i].Orientation.make(AxisRel::NextY, AxisRel::NextZ, AxisRel::None, AxisRel::None);
			i = VectorU3::Convert(CHUNK_VALUES_PER_SIDE, VectorU3(0xA, y, z));
			Data[i].Template = &VoxelTemplate::RedLog;
			Data[i].Orientation.make(AxisRel::NextY, AxisRel::NextZ, AxisRel::None, AxisRel::None);
		}
	}
}

float Chunk::Generation3D_Factor = 5.0f; // 32
float Chunk::Generation3D_Comparison = 0.0f;

void Chunk::GenerateGrid()
{
	Undex3D size3(CHUNK_VALUES_PER_SIDE);

	VectorI3 chunk_pos = Index * CHUNK_VALUES_PER_SIDE;

	UndexLoop3D loop3(Undex3D(), size3);
	for (Undex3D u = loop3.Min(); loop3.Check(u).All(true); loop3.Next(u))
	{
		VectorI3 voxel_idx = chunk_pos + u;
		VectorF3 voxel_pos = voxel_idx;

		VectorF3 grid_pos = voxel_pos.round(256);
		VectorF3 grid_rel = voxel_pos - grid_pos;

		if (grid_rel.length() < 4.0f) { Data[size3.Convert(u)].Template = &VoxelTemplate::OrientationCube; }
		if (VectorF3(grid_rel.X, grid_rel.Y, 0.0f).length() < 2.0f) { Data[size3.Convert(u)].Template = &VoxelTemplate::OrientationCube; }
		if (VectorF3(grid_rel.X, 0.0f, grid_rel.Z).length() < 2.0f) { Data[size3.Convert(u)].Template = &VoxelTemplate::OrientationCube; }
		if (VectorF3(0.0f, grid_rel.Y, grid_rel.Z).length() < 2.0f) { Data[size3.Convert(u)].Template = &VoxelTemplate::OrientationCube; }
	}
}
void Chunk::GeneratePerlin(const Perlin2D & noise)
{
	VectorF3 p3 = Index * CHUNK_VALUES_PER_SIDE;
	UndexLoop2D loop(Undex2D(), Undex2D(CHUNK_VALUES_PER_SIDE));
	for (Undex2D u = loop.Min(); loop.Check(u).All(true); loop.Next(u))
	{
		VectorF2 p2(
			p3.X + u.X,
			p3.Z + u.Y
		);

		float val = 0.0f;
		val += noise.Calculate(p2 / 32.0f) * 8;
		//val += noise.Calculate(p2 / 32.0f) * 32;
		//val += noise.Calculate(p2 / 16.0f) * 16;
		//val += noise.Calculate(p2 / 8.0f) * 8;
		//val += noise.Calculate(p2 / 4.0f) * 4;
		//val += noise.Calculate(p2 / 2.0f) * 2;
		//val += noise.Calculate(p2 / 1.0f) * 1;
		val = val - p3.Y;

		for (unsigned int i = 0; i < CHUNK_VALUES_PER_SIDE; i++)
		{
			unsigned int voxel_u = VectorU3::Convert(CHUNK_VALUES_PER_SIDE, Undex3D(u.X, i, u.Y));
			if (i > val)
			{
				Data[voxel_u].Template = nullptr;
			}
			else if (val - i < 1)
			{
				//Data[voxel_u].Template = &VoxelTemplate::Grass;
				Data[voxel_u].Template = &VoxelTemplate::ConcreteCube;
			}
			else
			{
				Data[voxel_u].Template = &VoxelTemplate::Gray;
			}
		}
	}
}
void Chunk::GeneratePerlin(const Perlin3D & noise)
{
	VectorF3 pos = Index * CHUNK_VALUES_PER_SIDE;
	UndexLoop3D loop(Undex3D(), Undex3D(CHUNK_VALUES_PER_SIDE));
	for (Undex3D u = loop.Min(); loop.Check(u).All(true); loop.Next(u))
	{
		VectorF3 p(
			pos.X + u.X,
			pos.Y + u.Y,
			pos.Z + u.Z
		);

		float val = 0.0f;
		//val += noise.Calculate(p / 32.0f) / 32.0f;
		val += noise.Calculate(p / Generation3D_Factor) / Generation3D_Factor;

		if (val > Generation3D_Comparison)
		{ Data[VectorU3::Convert(CHUNK_VALUES_PER_SIDE, u)].Template = nullptr; }
		else
		{ Data[VectorU3::Convert(CHUNK_VALUES_PER_SIDE, u)].Template = &VoxelTemplate::Gray; }

		/*if (val > 0.1f)
		{
			if (Data[VectorU3::Convert(CHUNK_VALUES_PER_SIDE, u)].Template != nullptr)
			{
				Data[VectorU3::Convert(CHUNK_VALUES_PER_SIDE, u)].Template = nullptr;
			}
		}*/
	}
}

static void GeneratePlane(Chunk & chunk)
{
	if (chunk.Index.Y >= 0) { return; }
	for (unsigned int i = 0; i < CHUNK_VALUES_PER_VOLM; i++)
	{
		chunk.Data[i].Template = &VoxelTemplate::ConcreteCube;
		chunk.Data[i].Orientation = VoxelOrientation();
	}
}

void Chunk::Generate(const Perlin2D & noise2, const Perlin3D & noise3)
{
	if (GenerationState != GenerationState::None) { return; }

	MakeNull();

	(void)noise2;
	(void)noise3;
	GeneratePlane(*this);
//	GeneratePerlin(noise2);
//	GeneratePerlin(noise3);
//	GenerateGrid();

	GenerationState = GenerationState::Generated;

	if (IsNullOrEmpty()) { MakeEmpty(); }

	if (GraphicsExist)
	{
		MainBufferState = BufferDataState::Needed;
	}
}



void Chunk::GraphicsCreate()
{
	if (GraphicsExist) { return; }

	Buffer.Create();

	GraphicsExist = true;

	BufferNeedsInit = true;

	if (Done())
	{
		MainBufferState = BufferDataState::Needed;
	}
	InstBufferNeedsData = true;
}
void Chunk::GraphicsDelete()
{
	if (!GraphicsExist) { return; }

	Buffer.Delete();

	GraphicsExist = false;
}



static void GraphicsData(Container::Binary<VoxelGraphics::MainTriangle> & data, const Container::Binary<VoxelGraphics::MainTriangle> & face, const VoxelOrientation & orientation, VectorU3 u)
{
	for (unsigned int i = 0; i < face.Count(); i++)
	{
		VoxelGraphics::MainTriangle v = face[i];
		v.Corners[0].Pos = orientation.absolute(v.Corners[0].Pos) + u;
		v.Corners[1].Pos = orientation.absolute(v.Corners[1].Pos) + u;
		v.Corners[2].Pos = orientation.absolute(v.Corners[2].Pos) + u;
		data.Insert(v);
	}
}

static void GraphicsData(Container::Binary<VoxelGraphics::MainTriangle> & data, VectorU3 u, const Voxel & voxel, const ChunkNeighbours & neighbours, AxisRel axis)
{
	if (neighbours.Visible(voxel.Orientation.absolute(axis), u))
	{
		GraphicsData(data, voxel.Template -> AxisData(axis), voxel.Orientation, u);
	}
}

void Chunk::GraphicsUpdateMainData()
{
	if (MainBufferState != BufferDataState::Needed) { return; }

	//std::cout << "Done: " << Done() << '\n';
	if (!Done()) { return; }

	//std::cout << "Clear\n";
	MainBufferData.Clear();

	//std::cout << "IsEmpty: " << IsEmpty() << '\n';
	if (!IsEmpty())
	{
		Undex3D size(CHUNK_VALUES_PER_SIDE);
		UndexLoop3D loop(Undex3D(), size);
		for (Undex3D u = loop.Min(); loop.Check(u).All(true); loop.Next(u))
		{
			const Voxel & voxel = Data[size.Convert(u)];
			if (voxel.Template == nullptr) { continue; }
			const VoxelTemplate & voxel_template = *voxel.Template;
			GraphicsData(MainBufferData, voxel_template.Here, voxel.Orientation, u);
			GraphicsData(MainBufferData, u, voxel, Neighbours, AxisRel::PrevX);
			GraphicsData(MainBufferData, u, voxel, Neighbours, AxisRel::PrevY);
			GraphicsData(MainBufferData, u, voxel, Neighbours, AxisRel::PrevZ);
			GraphicsData(MainBufferData, u, voxel, Neighbours, AxisRel::NextX);
			GraphicsData(MainBufferData, u, voxel, Neighbours, AxisRel::NextY);
			GraphicsData(MainBufferData, u, voxel, Neighbours, AxisRel::NextZ);
		}
	}
	MainBufferState = BufferDataState::Ready;
	//std::cout << "MainBUfferData done\n";
}
void Chunk::GraphicsUpdateMainBuffer()
{
	if (!GraphicsExist) { return; }

	if (MainBufferState != BufferDataState::Ready) { return; }

	Buffer.Main.Change(MainBufferData);
	Buffer.Main.DrawCount = MainBufferData.Count() * 3;
	MainBufferData.Clear();

	MainBufferState = BufferDataState::None;
}

void Chunk::UpdateInstBuffer()
{
	if (!GraphicsExist) { return; }
	if (!InstBufferNeedsData) { return; }

	{
		Container::Binary<VoxelGraphics::InstData> data;

		VoxelGraphics::InstData temp;
		temp.Pos = Index * CHUNK_VALUES_PER_SIDE;
		data.Insert(temp);

		Buffer.Inst.Change(data);
	}

	InstBufferNeedsData = false;
}



void Chunk::Draw()
{
	if (!GraphicsExist) { return; }
	if (BufferNeedsInit)
	{
		Buffer.Inst.Init();
		Buffer.Main.Init();
		BufferNeedsInit = false;
	}
	GraphicsUpdateMainBuffer();
	UpdateInstBuffer();
	Buffer.Draw();
}
