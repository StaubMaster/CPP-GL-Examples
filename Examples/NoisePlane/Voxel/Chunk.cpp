#include "Chunk.hpp"
#include "VoxelTemplate.hpp"

#include "Graphics/Inst/Data.hpp"

#include "VoxelOrientation.hpp"

#include "Noise/Perlin2D.hpp"
#include "Noise/Perlin3D.hpp"

#include "ValueType/BoxI3.hpp"

#include "ValueType/Bool3.hpp"
#include "ValueType/VectorU3.hpp"

#include "ValueType/Undex2D.hpp"
#include "ValueType/UndexLoop2D.hpp"

#include "ValueType/Undex3D.hpp"
#include "ValueType/UndexLoop3D.hpp"

#include "Miscellaneous/Container/Binary.hpp"



Voxel &			Chunk::operator[](VectorU3 udx)			{ return Data[VectorU3::Convert(CHUNK_VALUES_PER_SIDE, udx)]; }
const Voxel &	Chunk::operator[](VectorU3 udx) const	{ return Data[VectorU3::Convert(CHUNK_VALUES_PER_SIDE, udx)]; }



Chunk::~Chunk()
{
	if (ChunkType == ChunkType::Empty)
	{
		delete Data;
	}
	else
	{
		delete[] Data;
	}
}
Chunk::Chunk()
	: Data(nullptr)
	, Index()
	, ChunkType(ChunkType::UnGenerated)
	, MainCount(0)
	, Buffer()
	, GraphicsExist(false)
	, BufferNeedsInit(false)
	, MainBufferNeedsData(false)
	, InstBufferNeedsData(false)
{ }
//void Chunk::Dispose() { }



void Chunk::MakeEmpty()
{
	if (ChunkType == ChunkType::Filled)
	{
		delete[] Data;
		ChunkType = ChunkType::Empty;
		Data = new Voxel();
		Data -> Template = nullptr;
	}
}
void Chunk::CheckEmpty()
{
	bool empty = true;
	if (ChunkType == ChunkType::Filled)
	{
		for (unsigned int i = 0; i < CHUNK_VALUES_PER_VOLM; i++)
		{
			if (Data[i].Template != nullptr) { empty = false; break; }
		}
	}
	if (empty)
	{
		MakeEmpty();
	}
	else
	{
		ChunkType = ChunkType::Filled;
	}
}

void Chunk::FillNull()
{
	if (ChunkType == ChunkType::Empty)
	{
		delete Data;
		Data = nullptr;
	}
	if (Data == nullptr)
	{
		Data = new Voxel[CHUNK_VALUES_PER_VOLM];
	}
	ChunkType = ChunkType::Filled;
	Neighbours.UpdateBufferMain();

	for (unsigned int i = 0; i < CHUNK_VALUES_PER_VOLM; i++)
	{
		Data[i].Template = nullptr;
		Data[i].Orientation = VoxelOrientation();
	}
}



static void TestOrientation(Chunk & chunk, const VoxelTemplate & voxel_template, Diag diag, Flip flip, VectorU3 u)
{
	unsigned int i = VectorU3::Convert(CHUNK_VALUES_PER_SIDE, u);
	chunk.Data[i].Template = &voxel_template;
	chunk.Data[i].Orientation.make(diag, flip);
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
	FillNull();
	::TestOrientation(*this, VoxelTemplate::OrientationCube, 0x0);
	::TestOrientation(*this, VoxelTemplate::OrientationCylinder, 0x2);
	::TestOrientation(*this, VoxelTemplate::OrientationSlope, 0x4);
}
void Chunk::TestHouse()
{
	FillNull();
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
			Data[i].Orientation.make(Axis::NextY, Axis::NextZ, Axis::None, Axis::None);
			i = VectorU3::Convert(CHUNK_VALUES_PER_SIDE, VectorU3(0xA, y, z));
			Data[i].Template = &VoxelTemplate::RedLog;
			Data[i].Orientation.make(Axis::NextY, Axis::NextZ, Axis::None, Axis::None);
		}
	}
}

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
		val += noise.Calculate(p2 / 32) * 32;
		val += noise.Calculate(p2 / 16) * 16;
		val += noise.Calculate(p2 / 8) * 8;
		val += noise.Calculate(p2 / 4) * 4;
		val += noise.Calculate(p2 / 2) * 2;
		val += noise.Calculate(p2 / 1) * 1;
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
				Data[voxel_u].Template = &VoxelTemplate::Grass;
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
		val += noise.Calculate(p / 32.0f) / 32.0f;

		if (val > 0.0f)
		{
			Data[VectorU3::Convert(CHUNK_VALUES_PER_SIDE, u)].Template = &VoxelTemplate::Gray;
		}
		else
		{
			Data[VectorU3::Convert(CHUNK_VALUES_PER_SIDE, u)].Template = nullptr;
		}
	}
}

void Chunk::Generate(const Perlin2D & noise2, const Perlin3D & noise3)
{
	if (ChunkType != ChunkType::UnGenerated) { return; }

	FillNull();

	(void)noise2;
	(void)noise3;
//	GeneratePerlin(noise3);
//	GeneratePerlin(noise2);
//	GenerateGrid();

	CheckEmpty();

	if (GraphicsExist)
	{
		MainBufferNeedsData = true;
	}
}



void Chunk::GraphicsCreate()
{
	if (GraphicsExist) { return; }

	Buffer.Create();

	GraphicsExist = true;

	BufferNeedsInit = true;

	if (ChunkType == ChunkType::Filled || ChunkType == ChunkType::Empty)
	{
		MainBufferNeedsData = true;
	}
	InstBufferNeedsData = true;
}
void Chunk::GraphicsDelete()
{
	if (!GraphicsExist) { return; }

	Buffer.Delete();

	GraphicsExist = false;
}



/*static void GraphicsData(Container::Binary<VoxelGraphics::MainData> & data, VoxelGraphics::VoxelFace face)
{
	data.Insert(face.Corn[0b00]);
	data.Insert(face.Corn[0b10]);
	data.Insert(face.Corn[0b01]);

	data.Insert(face.Corn[0b01]);
	data.Insert(face.Corn[0b10]);
	data.Insert(face.Corn[0b11]);
}*/

static void GraphicsData(Container::Binary<VoxelGraphics::MainData> & data, const Container::Binary<VoxelGraphics::MainData> & face, VoxelOrientation & orientation, VectorU3 u)
{
	//if (orientation.oppo == Oppo::Regular)
	{
		for (unsigned int i = 0; i < face.Count(); i++)
		{
			VoxelGraphics::MainData v = face[i];
			v.Pos = orientation.absolute(v.Pos) + u;
			data.Insert(v);
		}
	}
	//else
	/*{
		for (unsigned int i = face.Count() - 1; i < face.Count(); i--)
		{
			VoxelGraphics::MainData v = face[i];
			v.Pos = orientation.orient(v.Pos) + u;
			data.Insert(v);
		}
	}*/
}

static void GraphicsData(Container::Binary<VoxelGraphics::MainData> & data, const VoxelTemplate & voxel_template, VoxelOrientation & orientations, ChunkNeighbours & neighbours, Axis axis, VectorU3 u)
{
	if (!neighbours.Visible(orientations.absolute(axis), u)) { return; }
	GraphicsData(data, voxel_template.AxisData(axis), orientations, u);
}

void Chunk::UpdateMainBuffer()
{
	if (!GraphicsExist) { return; }
	if (!MainBufferNeedsData) { return; }

	{
		Container::Binary<VoxelGraphics::MainData> data;

		if (ChunkType == ChunkType::Filled)
		{
			Undex3D size(CHUNK_VALUES_PER_SIDE);
			UndexLoop3D loop(Undex3D(), size);
			for (Undex3D u = loop.Min(); loop.Check(u).All(true); loop.Next(u))
			{
				Voxel & voxel = Data[size.Convert(u)];
				if (voxel.Template == nullptr) { continue; }
				const VoxelTemplate & voxel_template = *voxel.Template;
				GraphicsData(data, voxel_template.Here, voxel.Orientation, u);
				GraphicsData(data, *voxel.Template, voxel.Orientation, Neighbours, Axis::PrevX, u);
				GraphicsData(data, *voxel.Template, voxel.Orientation, Neighbours, Axis::PrevY, u);
				GraphicsData(data, *voxel.Template, voxel.Orientation, Neighbours, Axis::PrevZ, u);
				GraphicsData(data, *voxel.Template, voxel.Orientation, Neighbours, Axis::NextX, u);
				GraphicsData(data, *voxel.Template, voxel.Orientation, Neighbours, Axis::NextY, u);
				GraphicsData(data, *voxel.Template, voxel.Orientation, Neighbours, Axis::NextZ, u);
				/*if (Neighbours.Visible(Axis::PrevX, u))*/ //{ GraphicsData(data, voxel_template.PrevX, voxel.Orientation, u); }
				/*if (Neighbours.Visible(Axis::PrevY, u))*/ //{ GraphicsData(data, voxel_template.PrevY, voxel.Orientation, u); }
				/*if (Neighbours.Visible(Axis::PrevZ, u))*/ //{ GraphicsData(data, voxel_template.PrevZ, voxel.Orientation, u); }
				/*if (Neighbours.Visible(Axis::NextX, u))*/ //{ GraphicsData(data, voxel_template.NextX, voxel.Orientation, u); }
				/*if (Neighbours.Visible(Axis::NextY, u))*/ //{ GraphicsData(data, voxel_template.NextY, voxel.Orientation, u); }
				/*if (Neighbours.Visible(Axis::NextZ, u))*/ //{ GraphicsData(data, voxel_template.NextZ, voxel.Orientation, u); }
			}
		}

		MainCount = data.Count();

		Buffer.Main.Change(data);
	}

	MainBufferNeedsData = false;
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
	UpdateMainBuffer();
	UpdateInstBuffer();
	Buffer.Draw();
}
