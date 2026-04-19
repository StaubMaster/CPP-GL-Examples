#include "Chunk.hpp"

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



/*static void TestOrientation(Chunk & chunk, VectorU3 u, Axis origin, Axis target)
{
	unsigned int i = VectorU3::Convert(CHUNK_VALUES_PER_SIDE, u);
	chunk.Data[i].Template = &VoxelTemplate::OrientationCube;
	chunk.Data[i].Orientation.make(origin, target, Axis::None, Axis::None);
}*/
static void TestOrientation(Chunk & chunk, VectorU3 u, Axis origin0, Axis target0, Axis origin1, Axis target1)
{
	unsigned int i = VectorU3::Convert(CHUNK_VALUES_PER_SIDE, u);
	chunk.Data[i].Template = &VoxelTemplate::OrientationCube;
	chunk.Data[i].Orientation.make(origin0, target0, origin1, target1);
}
/*static void TestOrientation(Chunk & chunk, VectorU3 u, Diag diag, Flip flip)
{
	unsigned int i = VectorU3::Convert(CHUNK_VALUES_PER_SIDE, u);
	chunk.Data[i].Template = &VoxelTemplate::OrientationCube;
	chunk.Data[i].Orientation.make(diag, flip);
}*/

void Chunk::GenerateTestRotation()
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

//	0	1	2	3	4	5	6	7	8	9	A	B	C	D	E	F
//		#		#		#		|	|		#		#		#	
//	#			#			#	|	|	#			#			#
//	#		#		#		#	|	|	#		#		#		#

//	Data[VectorU3::Convert(CHUNK_VALUES_PER_SIDE, VectorU3( 0,  0,  0))].Template = &VoxelTemplate::OrientationCube;
//	Data[VectorU3::Convert(CHUNK_VALUES_PER_SIDE, VectorU3(15, 15, 15))].Template = &VoxelTemplate::OrientationCube;



//	TestOrientation(*this, VectorU3(0x0, 0x1, 0x0), Diag::Here, Flip::None); // XYZ +++
//	TestOrientation(*this, VectorU3(0x3, 0x1, 0x0), Diag::Prev, Flip::None); // ZXY +++
//	TestOrientation(*this, VectorU3(0x6, 0x1, 0x0), Diag::Next, Flip::None); // YZX +++
//
//	TestOrientation(*this, VectorU3(0x0, 0x1, 0x2), Diag::Here, Flip::FlipX); // XYZ +--
//	TestOrientation(*this, VectorU3(0x3, 0x1, 0x2), Diag::Prev, Flip::FlipX); // ZXY +--
//	TestOrientation(*this, VectorU3(0x6, 0x1, 0x2), Diag::Next, Flip::FlipX); // YZX +--
//
//	TestOrientation(*this, VectorU3(0x0, 0x1, 0x4), Diag::Here, Flip::FlipY); // XYZ -+-
//	TestOrientation(*this, VectorU3(0x3, 0x1, 0x4), Diag::Prev, Flip::FlipY); // ZXY -+-
//	TestOrientation(*this, VectorU3(0x6, 0x1, 0x4), Diag::Next, Flip::FlipY); // YZX -+-
//
//	TestOrientation(*this, VectorU3(0x0, 0x1, 0x6), Diag::Here, Flip::FlipZ); // XYZ --+
//	TestOrientation(*this, VectorU3(0x3, 0x1, 0x6), Diag::Prev, Flip::FlipZ); // ZXY --+
//	TestOrientation(*this, VectorU3(0x6, 0x1, 0x6), Diag::Next, Flip::FlipZ); // YZX --+
//
//
//
//	TestOrientation(*this, VectorU3(0x0, 0x1, 0x9), Diag::DiagX, Flip::None); // XZY ---
//	TestOrientation(*this, VectorU3(0x3, 0x1, 0x9), Diag::DiagY, Flip::None); // ZYX ---
//	TestOrientation(*this, VectorU3(0x6, 0x1, 0x9), Diag::DiagZ, Flip::None); // YXZ ---
//
//	TestOrientation(*this, VectorU3(0x0, 0x1, 0xB), Diag::DiagX, Flip::FlipX); // XZY -++
//	TestOrientation(*this, VectorU3(0x3, 0x1, 0xB), Diag::DiagY, Flip::FlipX); // ZYX -++
//	TestOrientation(*this, VectorU3(0x6, 0x1, 0xB), Diag::DiagZ, Flip::FlipX); // YXZ -++
//
//	TestOrientation(*this, VectorU3(0x0, 0x1, 0xD), Diag::DiagX, Flip::FlipY); // XZY +-+
//	TestOrientation(*this, VectorU3(0x3, 0x1, 0xD), Diag::DiagY, Flip::FlipY); // ZYX +-+
//	TestOrientation(*this, VectorU3(0x6, 0x1, 0xD), Diag::DiagZ, Flip::FlipY); // YXZ +-+
//
//	TestOrientation(*this, VectorU3(0x0, 0x1, 0xF), Diag::DiagX, Flip::FlipZ); // XZY ++-
//	TestOrientation(*this, VectorU3(0x3, 0x1, 0xF), Diag::DiagY, Flip::FlipZ); // ZYX ++-
//	TestOrientation(*this, VectorU3(0x6, 0x1, 0xF), Diag::DiagZ, Flip::FlipZ); // YXZ ++-



//	TestOrientation(*this, VectorU3(0x0, 0x6, 0x1), Axis::PrevX, Axis::PrevX, Axis::PrevY, Axis::PrevY);
//	TestOrientation(*this, VectorU3(0x2, 0x6, 0x1), Axis::PrevX, Axis::PrevX, Axis::PrevY, Axis::PrevZ);
//	TestOrientation(*this, VectorU3(0x4, 0x6, 0x1), Axis::PrevX, Axis::PrevX, Axis::PrevY, Axis::NextY);
//	TestOrientation(*this, VectorU3(0x6, 0x6, 0x1), Axis::PrevX, Axis::PrevX, Axis::PrevY, Axis::NextZ);
//	TestOrientation(*this, VectorU3(0x9, 0x6, 0x1), Axis::PrevX, Axis::PrevX, Axis::PrevZ, Axis::PrevY);
//	TestOrientation(*this, VectorU3(0xB, 0x6, 0x1), Axis::PrevX, Axis::PrevX, Axis::PrevZ, Axis::PrevZ);
//	TestOrientation(*this, VectorU3(0xD, 0x6, 0x1), Axis::PrevX, Axis::PrevX, Axis::PrevZ, Axis::NextY);
//	TestOrientation(*this, VectorU3(0xF, 0x6, 0x1), Axis::PrevX, Axis::PrevX, Axis::PrevZ, Axis::NextZ);
//	TestOrientation(*this, VectorU3(0x0, 0x9, 0x1), Axis::PrevX, Axis::PrevX, Axis::NextY, Axis::PrevY);
//	TestOrientation(*this, VectorU3(0x2, 0x9, 0x1), Axis::PrevX, Axis::PrevX, Axis::NextY, Axis::PrevZ);
//	TestOrientation(*this, VectorU3(0x4, 0x9, 0x1), Axis::PrevX, Axis::PrevX, Axis::NextY, Axis::NextY);
//	TestOrientation(*this, VectorU3(0x6, 0x9, 0x1), Axis::PrevX, Axis::PrevX, Axis::NextY, Axis::NextZ);
//	TestOrientation(*this, VectorU3(0x9, 0x9, 0x1), Axis::PrevX, Axis::PrevX, Axis::NextZ, Axis::PrevY);
//	TestOrientation(*this, VectorU3(0xB, 0x9, 0x1), Axis::PrevX, Axis::PrevX, Axis::NextZ, Axis::PrevZ);
//	TestOrientation(*this, VectorU3(0xD, 0x9, 0x1), Axis::PrevX, Axis::PrevX, Axis::NextZ, Axis::NextY);
//	TestOrientation(*this, VectorU3(0xF, 0x9, 0x1), Axis::PrevX, Axis::PrevX, Axis::NextZ, Axis::NextZ);

//	TestOrientation(*this, VectorU3(0x0, 0x6, 0x1), Axis::PrevX, Axis::PrevZ, Axis::PrevY, Axis::PrevX);
//	TestOrientation(*this, VectorU3(0x2, 0x6, 0x1), Axis::PrevX, Axis::PrevZ, Axis::PrevY, Axis::PrevZ);
//	TestOrientation(*this, VectorU3(0x4, 0x6, 0x1), Axis::PrevX, Axis::PrevZ, Axis::PrevY, Axis::NextX);
//	TestOrientation(*this, VectorU3(0x6, 0x6, 0x1), Axis::PrevX, Axis::PrevZ, Axis::PrevY, Axis::NextZ);
//	TestOrientation(*this, VectorU3(0x9, 0x6, 0x1), Axis::PrevX, Axis::PrevZ, Axis::PrevZ, Axis::PrevX);
//	TestOrientation(*this, VectorU3(0xB, 0x6, 0x1), Axis::PrevX, Axis::PrevZ, Axis::PrevZ, Axis::PrevZ);
//	TestOrientation(*this, VectorU3(0xD, 0x6, 0x1), Axis::PrevX, Axis::PrevZ, Axis::PrevZ, Axis::NextX);
//	TestOrientation(*this, VectorU3(0xF, 0x6, 0x1), Axis::PrevX, Axis::PrevZ, Axis::PrevZ, Axis::NextZ);
//	TestOrientation(*this, VectorU3(0x0, 0x9, 0x1), Axis::PrevX, Axis::PrevZ, Axis::NextY, Axis::PrevX);
//	TestOrientation(*this, VectorU3(0x2, 0x9, 0x1), Axis::PrevX, Axis::PrevZ, Axis::NextY, Axis::PrevZ);
//	TestOrientation(*this, VectorU3(0x4, 0x9, 0x1), Axis::PrevX, Axis::PrevZ, Axis::NextY, Axis::NextX);
//	TestOrientation(*this, VectorU3(0x6, 0x9, 0x1), Axis::PrevX, Axis::PrevZ, Axis::NextY, Axis::NextZ);
//	TestOrientation(*this, VectorU3(0x9, 0x9, 0x1), Axis::PrevX, Axis::PrevZ, Axis::NextZ, Axis::PrevX);
//	TestOrientation(*this, VectorU3(0xB, 0x9, 0x1), Axis::PrevX, Axis::PrevZ, Axis::NextZ, Axis::PrevZ);
//	TestOrientation(*this, VectorU3(0xD, 0x9, 0x1), Axis::PrevX, Axis::PrevZ, Axis::NextZ, Axis::NextX);
//	TestOrientation(*this, VectorU3(0xF, 0x9, 0x1), Axis::PrevX, Axis::PrevZ, Axis::NextZ, Axis::NextZ);



	TestOrientation(*this, VectorU3(0x1, 0x1, 0x1), Axis::PrevX, Axis::PrevX, Axis::None, Axis::None);
	TestOrientation(*this, VectorU3(0x3, 0x1, 0x1), Axis::PrevX, Axis::PrevY, Axis::None, Axis::None);
	TestOrientation(*this, VectorU3(0x5, 0x1, 0x1), Axis::PrevX, Axis::PrevZ, Axis::None, Axis::None);
	TestOrientation(*this, VectorU3(0xA, 0x1, 0x1), Axis::PrevX, Axis::NextX, Axis::None, Axis::None);
	TestOrientation(*this, VectorU3(0xC, 0x1, 0x1), Axis::PrevX, Axis::NextY, Axis::None, Axis::None);
	TestOrientation(*this, VectorU3(0xE, 0x1, 0x1), Axis::PrevX, Axis::NextZ, Axis::None, Axis::None);

	TestOrientation(*this, VectorU3(0x1, 0x1, 0x3), Axis::PrevY, Axis::PrevX, Axis::None, Axis::None);
	TestOrientation(*this, VectorU3(0x3, 0x1, 0x3), Axis::PrevY, Axis::PrevY, Axis::None, Axis::None);
	TestOrientation(*this, VectorU3(0x5, 0x1, 0x3), Axis::PrevY, Axis::PrevZ, Axis::None, Axis::None);
	TestOrientation(*this, VectorU3(0xA, 0x1, 0x3), Axis::PrevY, Axis::NextX, Axis::None, Axis::None);
	TestOrientation(*this, VectorU3(0xC, 0x1, 0x3), Axis::PrevY, Axis::NextY, Axis::None, Axis::None);
	TestOrientation(*this, VectorU3(0xE, 0x1, 0x3), Axis::PrevY, Axis::NextZ, Axis::None, Axis::None);

	TestOrientation(*this, VectorU3(0x1, 0x1, 0x5), Axis::PrevZ, Axis::PrevX, Axis::None, Axis::None);
	TestOrientation(*this, VectorU3(0x3, 0x1, 0x5), Axis::PrevZ, Axis::PrevY, Axis::None, Axis::None);
	TestOrientation(*this, VectorU3(0x5, 0x1, 0x5), Axis::PrevZ, Axis::PrevZ, Axis::None, Axis::None);
	TestOrientation(*this, VectorU3(0xA, 0x1, 0x5), Axis::PrevZ, Axis::NextX, Axis::None, Axis::None);
	TestOrientation(*this, VectorU3(0xC, 0x1, 0x5), Axis::PrevZ, Axis::NextY, Axis::None, Axis::None);
	TestOrientation(*this, VectorU3(0xE, 0x1, 0x5), Axis::PrevZ, Axis::NextZ, Axis::None, Axis::None);



	TestOrientation(*this, VectorU3(0x1, 0x1, 0xA), Axis::NextX, Axis::PrevX, Axis::None, Axis::None);
	TestOrientation(*this, VectorU3(0x3, 0x1, 0xA), Axis::NextX, Axis::PrevY, Axis::None, Axis::None);
	TestOrientation(*this, VectorU3(0x5, 0x1, 0xA), Axis::NextX, Axis::PrevZ, Axis::None, Axis::None);
	TestOrientation(*this, VectorU3(0xA, 0x1, 0xA), Axis::NextX, Axis::NextX, Axis::None, Axis::None);
	TestOrientation(*this, VectorU3(0xC, 0x1, 0xA), Axis::NextX, Axis::NextY, Axis::None, Axis::None);
	TestOrientation(*this, VectorU3(0xE, 0x1, 0xA), Axis::NextX, Axis::NextZ, Axis::None, Axis::None);

	TestOrientation(*this, VectorU3(0x1, 0x1, 0xC), Axis::NextY, Axis::PrevX, Axis::None, Axis::None);
	TestOrientation(*this, VectorU3(0x3, 0x1, 0xC), Axis::NextY, Axis::PrevY, Axis::None, Axis::None);
	TestOrientation(*this, VectorU3(0x5, 0x1, 0xC), Axis::NextY, Axis::PrevZ, Axis::None, Axis::None);
	TestOrientation(*this, VectorU3(0xA, 0x1, 0xC), Axis::NextY, Axis::NextX, Axis::None, Axis::None);
	TestOrientation(*this, VectorU3(0xC, 0x1, 0xC), Axis::NextY, Axis::NextY, Axis::None, Axis::None);
	TestOrientation(*this, VectorU3(0xE, 0x1, 0xC), Axis::NextY, Axis::NextZ, Axis::None, Axis::None);

	TestOrientation(*this, VectorU3(0x1, 0x1, 0xE), Axis::NextZ, Axis::PrevX, Axis::None, Axis::None);
	TestOrientation(*this, VectorU3(0x3, 0x1, 0xE), Axis::NextZ, Axis::PrevY, Axis::None, Axis::None);
	TestOrientation(*this, VectorU3(0x5, 0x1, 0xE), Axis::NextZ, Axis::PrevZ, Axis::None, Axis::None);
	TestOrientation(*this, VectorU3(0xA, 0x1, 0xE), Axis::NextZ, Axis::NextX, Axis::None, Axis::None);
	TestOrientation(*this, VectorU3(0xC, 0x1, 0xE), Axis::NextZ, Axis::NextY, Axis::None, Axis::None);
	TestOrientation(*this, VectorU3(0xE, 0x1, 0xE), Axis::NextZ, Axis::NextZ, Axis::None, Axis::None);
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

	if (Data == nullptr)
	{
		Data = new Voxel[CHUNK_VALUES_PER_VOLM];
	}
	for (unsigned int i = 0; i < CHUNK_VALUES_PER_VOLM; i++)
	{
		Data[i].Template = nullptr;
	}

	(void)noise2;
	(void)noise3;
//	GeneratePerlin(noise3);
//	GeneratePerlin(noise2);
//	GenerateGrid();

	bool empty = true;
	for (unsigned int i = 0; i < CHUNK_VALUES_PER_VOLM; i++)
	{
		if (Data[i].Template != nullptr) { empty = false; break; }
	}
	if (empty)
	{
		delete[] Data;
		ChunkType = ChunkType::Empty;
		Data = new Voxel();
		Data -> Template = nullptr;
	}
	else
	{
		ChunkType = ChunkType::Filled;
	}

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
			v.Pos = orientation.orient(v.Pos) + u;
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
				VoxelTemplate & voxel_template = *voxel.Template;
				GraphicsData(data, voxel_template.Here, voxel.Orientation, u);
				/*if (Neighbours.Visible(Axis::PrevX, u))*/ { GraphicsData(data, voxel_template.PrevX, voxel.Orientation, u); }
				/*if (Neighbours.Visible(Axis::PrevY, u))*/ { GraphicsData(data, voxel_template.PrevY, voxel.Orientation, u); }
				/*if (Neighbours.Visible(Axis::PrevZ, u))*/ { GraphicsData(data, voxel_template.PrevZ, voxel.Orientation, u); }
				/*if (Neighbours.Visible(Axis::NextX, u))*/ { GraphicsData(data, voxel_template.NextX, voxel.Orientation, u); }
				/*if (Neighbours.Visible(Axis::NextY, u))*/ { GraphicsData(data, voxel_template.NextY, voxel.Orientation, u); }
				/*if (Neighbours.Visible(Axis::NextZ, u))*/ { GraphicsData(data, voxel_template.NextZ, voxel.Orientation, u); }
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
