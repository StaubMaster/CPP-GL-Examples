#include "Chunk.hpp"
#include "ChunkManager.hpp"

#include "VoxelPallet.hpp"

#include "Graphics/Inst/Data.hpp"

#include "VoxelOrientation.hpp"

#include "ValueGen/Perlin2D.hpp"
#include "ValueGen/Perlin3D.hpp"

#include "ValueType/Box/I3.hpp"

#include "ValueType/Bool3.hpp"
#include "ValueType/Vector/U3.hpp"

#include "ValueType/Vector/U2.hpp"
#include "ValueType/LoopU2.hpp"

#include "ValueType/Vector/U3.hpp"
#include "ValueType/LoopU3.hpp"

#include "Telemetry/StopWatch.hpp"



#include <iostream>


const Voxel &	Chunk::operator[](VectorU3 udx) const { return Voxels[udx]; }
const Voxel *	Chunk::FindVoxelOrNull(VectorU3 udx) const
{
	if (!(GenerationDone())) { return nullptr; }
	if (IsEmpty()) { return nullptr; }
	return &Voxels[udx];
}



Chunk::~Chunk()
{
	//delete[] Data;
	/*if (GraphicsExist)
	{
		Buffer.Delete();
	}*/
}
Chunk::Chunk(VectorI3 idx, ChunkManager & manager)
	: Index(idx)
	, Manager(manager)
	, Voxels()
	, Changing()
	, GenerationState(GenerationState::None)
	, Buffer()
	, GraphicsExist(false)
	, BufferNeedsInit(false)
	, MainBufferState(BufferDataState::None)
	, InstBufferNeedsData(false)
{
	Buffer.Main.Pos.Change(0);
	Buffer.Main.Tex.Change(1);
	Buffer.Main.Normal.Change(2);
	Buffer.Inst.Pos.Change(3);
}



void Chunk::lock()
{
//	std::cout << "Chunk:" << this << ".lock()\n";
	Changing.lock();
}
void Chunk::unlock()
{
//	std::cout << "Chunk:" << this << ".unlock()\n";
	Changing.unlock();
}
bool Chunk::try_lock()
{
	bool ret = Changing.try_lock();
//	std::cout << "Chunk:" << this << ".try_lock():" << ret << '\n';
	return ret;
}



bool Chunk::IsEmpty() const
{
	return (Voxels.Length() == 0);
}
bool Chunk::IsNullOrEmpty() const
{
	if (IsEmpty()) { return true; }
	for (unsigned int i = 0; i < CHUNK_VALUES_PER_VOLM; i++)
	{
		if (Voxels[i].Pallet != nullptr)
		{
			return false;
		}
	}
	return true;
}
void Chunk::MakeEmpty()
{
	if (!IsEmpty())
	{
		Voxels.Clear();
		Manager.NeighbourUpdateBufferMain(Index);
	}
}
void Chunk::MakeNull()
{
	if (IsEmpty())
	{
		Voxels.ChangeSize(VectorU3(CHUNK_VALUES_PER_SIDE));
	}
	for (unsigned int i = 0; i < CHUNK_VALUES_PER_VOLM; i++)
	{
		Voxels[i].Pallet = nullptr;
		Voxels[i].Orientation = VoxelOrientation();
	}
	Manager.NeighbourUpdateBufferMain(Index);
}



bool Chunk::HitVoxel(VectorU3 udx) const
{
	return (Voxels[udx].Pallet != nullptr);
}
bool Chunk::ClearVoxel(VectorU3 udx, Voxel & vox)
{
	if (!GenerationDone()) { return false; }

	if (IsEmpty()) { return false; }

	Voxel & voxel = Voxels[udx];
	if (voxel.Pallet == nullptr) { return false; }

	vox = voxel;
	voxel.Pallet = nullptr;

	if (IsNullOrEmpty()) { MakeEmpty(); }

	Manager.NeighbourUpdateBufferMain(Index);
	return true;
}
bool Chunk::PlaceVoxel(VectorU3 udx, Voxel & vox)
{
	if (!GenerationDone()) { return false; }

	if (IsEmpty()) { MakeNull(); }

	Voxel & voxel = Voxels[udx];
	if (voxel.Pallet != nullptr) {return false; }

	voxel = vox;
	vox.Pallet = nullptr;

	Manager.NeighbourUpdateBufferMain(Index);
	return true;
}



/*static void TestOrientation(Chunk & chunk, const VoxelPallet & voxel_template, Diag diag, Flip flip, VectorU3 u)
{
	//unsigned int i = VectorU3::Convert(CHUNK_VALUES_PER_SIDE, u);
	chunk[u].Pallet = &voxel_template;
	chunk[u].Orientation.make(diag, flip);
}*/
/*static void TestOrientation(Chunk & chunk, const VoxelPallet & voxel_template, unsigned int y)
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
}*/

/*void Chunk::TestOrientation()
{
	MakeNull();
	::TestOrientation(*this, VoxelPallet::OrientationCube, 0x0);
	::TestOrientation(*this, VoxelPallet::OrientationCylinder, 0x2);
	::TestOrientation(*this, VoxelPallet::OrientationSlope, 0x4);
}*/
/*void Chunk::TestHouse()
{
	MakeNull();
	unsigned int i;

	for (unsigned int x = 0x5; x <= 0xA; x++)
	{
		for (unsigned int z = 0x3; z <= 0xC; z++)
		{
			i = VectorU3::Convert(CHUNK_VALUES_PER_SIDE, VectorU3(x, 0, z));
			Data[i].Pallet = &VoxelPallet::Grass;
			Data[i].Orientation.make(Diag::Here, Flip::None);
		}
	}

	for (unsigned int y = 0x1; y <= 0x4; y++)
	{
		i = VectorU3::Convert(CHUNK_VALUES_PER_SIDE, VectorU3(0x5, y, 0x3));
		Data[i].Pallet = &VoxelPallet::RedLog;
		Data[i].Orientation.make(Diag::Here, Flip::None);
		i = VectorU3::Convert(CHUNK_VALUES_PER_SIDE, VectorU3(0xA, y, 0x3));
		Data[i].Pallet = &VoxelPallet::RedLog;
		Data[i].Orientation.make(Diag::Here, Flip::None);
		i = VectorU3::Convert(CHUNK_VALUES_PER_SIDE, VectorU3(0x5, y, 0xC));
		Data[i].Pallet = &VoxelPallet::RedLog;
		Data[i].Orientation.make(Diag::Here, Flip::None);
		i = VectorU3::Convert(CHUNK_VALUES_PER_SIDE, VectorU3(0xA, y, 0xC));
		Data[i].Pallet = &VoxelPallet::RedLog;
		Data[i].Orientation.make(Diag::Here, Flip::None);
		for (unsigned int z = 0x4; z <= 0xB; z++)
		{
			i = VectorU3::Convert(CHUNK_VALUES_PER_SIDE, VectorU3(0x5, y, z));
			Data[i].Pallet = &VoxelPallet::RedLog;
			Data[i].Orientation.make(AxisRel::NextY, AxisRel::NextZ, AxisRel::None, AxisRel::None);
			i = VectorU3::Convert(CHUNK_VALUES_PER_SIDE, VectorU3(0xA, y, z));
			Data[i].Pallet = &VoxelPallet::RedLog;
			Data[i].Orientation.make(AxisRel::NextY, AxisRel::NextZ, AxisRel::None, AxisRel::None);
		}
	}
}*/

float Chunk::Generation3D_Factor = 5.0f; // 32
float Chunk::Generation3D_Comparison = 0.0f;

bool Chunk::GenerationDone() const { return GenerationState == GenerationState::Generated; }

/*
Condition:
Place: OrientationCube
*/
void Chunk::GenerateGrid()
{
	VectorI3 chunk_pos = Index * CHUNK_VALUES_PER_SIDE;

	LoopU3 loop3(VectorU3(), Voxels.Size());
	for (VectorU3 u = loop3.Min(); loop3.Check(u).All(true); loop3.Next(u))
	{
		VectorI3 voxel_idx = chunk_pos + u;
		VectorF3 voxel_pos = voxel_idx;

		VectorF3 grid_pos = voxel_pos.round(256);
		VectorF3 grid_rel = voxel_pos - grid_pos + VectorF3(0.5f);

		if (grid_rel.length() < 4.0f) { Voxels[u].Pallet = &VoxelPalletMap::All["OrientationCube"]; }
		if (VectorF3(grid_rel.X, grid_rel.Y, 0.0f).length() < 2.0f) { Voxels[u].Pallet = &VoxelPalletMap::All["OrientationCube"]; }
		if (VectorF3(grid_rel.X, 0.0f, grid_rel.Z).length() < 2.0f) { Voxels[u].Pallet = &VoxelPalletMap::All["OrientationCube"]; }
		if (VectorF3(0.0f, grid_rel.Y, grid_rel.Z).length() < 2.0f) { Voxels[u].Pallet = &VoxelPalletMap::All["OrientationCube"]; }
	}
}
/*
Condition: Y <= 0
Place: ConcreteCube
*/
void Chunk::GeneratePlane()
{
	if (Index.Y >= 0) { return; }
	for (unsigned int i = 0; i < CHUNK_VALUES_PER_VOLM; i++)
	{
		Voxels[i].Pallet = &VoxelPalletMap::All["ConcreteCube"];
		//Data[i].Orientation = VoxelOrientation();
	}
}
/*
Condition: Y == 0 || Y == 31
Place: ConcreteCube

Condition: ((X == 7 || X == 24) && (Z == 7 || Z == 24))
Place: ConcreteCylinder
*/
void Chunk::GeneratePillars()
{
	//0123456789ABCDEF0123456789ABCDEF
	//       #                #       

	VectorI3 chunk_pos = Index * CHUNK_VALUES_PER_SIDE;

	VoxelPallet & pallet0 = VoxelPalletMap::All["ConcreteCube"];
	VoxelPallet & pallet1 = VoxelPalletMap::All["ConcreteCylinder"];

	LoopU3 loop3(VectorU3(), Voxels.Size());
	for (VectorU3 u = loop3.Min(); loop3.Check(u).All(true); loop3.Next(u))
	{
		if (u.Y == 0 || u.Y == 31)
		{ Voxels[u].Pallet = &pallet0; }
		//else if ((u.X == 7 || u.X == 24) && (u.Z == 7 || u.Z == 24))
		else if ((u.X == 1 || u.X == 30) && (u.Z == 1 || u.Z == 30))
		{ Voxels[u].Pallet = &pallet1; }
	}
}
void Chunk::GeneratePillars(const Perlin2D & noise)
{
	(void)noise;

	VectorU3 origin(15, 0, 15);
	if (Voxels[origin].Pallet == nullptr) { return; }
	for (; origin.Y < CHUNK_VALUES_PER_SIDE; origin.Y++)
	{
		if (Voxels[origin].Pallet == nullptr)
		{
			break;
		}
	}
	if (origin.Y == CHUNK_VALUES_PER_SIDE) { return; }

	/*
		|     |     |  #  |     |     |
		|     |  #  | ### |  #  |     |
		|  #  | ### |##|##| ### |  #  |
		| ### |#####|##|##|#####| ### |
		|     |     |  |  |     |     |
		|     |     |  |  |     |     |
		|     |     |  |  |     |     |
	*/

	Array3D<Voxel> Tree;
	Tree.ChangeSize(VectorU3(5, 7, 5));

	Tree[VectorU3(1, 3, 0)].Pallet = &VoxelPalletMap::All["OrientationCube"];
	Tree[VectorU3(2, 3, 0)].Pallet = &VoxelPalletMap::All["OrientationCube"];
	Tree[VectorU3(3, 3, 0)].Pallet = &VoxelPalletMap::All["OrientationCube"];
	Tree[VectorU3(2, 4, 0)].Pallet = &VoxelPalletMap::All["OrientationCube"];

	Tree[VectorU3(0, 3, 1)].Pallet = &VoxelPalletMap::All["OrientationCube"];
	Tree[VectorU3(1, 3, 1)].Pallet = &VoxelPalletMap::All["OrientationCube"];
	Tree[VectorU3(2, 3, 1)].Pallet = &VoxelPalletMap::All["OrientationCube"];
	Tree[VectorU3(3, 3, 1)].Pallet = &VoxelPalletMap::All["OrientationCube"];
	Tree[VectorU3(4, 3, 1)].Pallet = &VoxelPalletMap::All["OrientationCube"];
	Tree[VectorU3(1, 4, 1)].Pallet = &VoxelPalletMap::All["OrientationCube"];
	Tree[VectorU3(2, 4, 1)].Pallet = &VoxelPalletMap::All["OrientationCube"];
	Tree[VectorU3(3, 4, 1)].Pallet = &VoxelPalletMap::All["OrientationCube"];
	Tree[VectorU3(2, 5, 1)].Pallet = &VoxelPalletMap::All["OrientationCube"];

	Tree[VectorU3(0, 3, 2)].Pallet = &VoxelPalletMap::All["OrientationCube"];
	Tree[VectorU3(1, 3, 2)].Pallet = &VoxelPalletMap::All["OrientationCube"];
	Tree[VectorU3(2, 3, 2)].Pallet = &VoxelPalletMap::All["OrientationCube"];
	Tree[VectorU3(3, 3, 2)].Pallet = &VoxelPalletMap::All["OrientationCube"];
	Tree[VectorU3(4, 3, 2)].Pallet = &VoxelPalletMap::All["OrientationCube"];
	Tree[VectorU3(0, 4, 2)].Pallet = &VoxelPalletMap::All["OrientationCube"];
	Tree[VectorU3(1, 4, 2)].Pallet = &VoxelPalletMap::All["OrientationCube"];
	Tree[VectorU3(2, 4, 2)].Pallet = &VoxelPalletMap::All["OrientationCube"];
	Tree[VectorU3(3, 4, 2)].Pallet = &VoxelPalletMap::All["OrientationCube"];
	Tree[VectorU3(4, 4, 2)].Pallet = &VoxelPalletMap::All["OrientationCube"];
	Tree[VectorU3(1, 5, 2)].Pallet = &VoxelPalletMap::All["OrientationCube"];
	Tree[VectorU3(2, 5, 2)].Pallet = &VoxelPalletMap::All["OrientationCube"];
	Tree[VectorU3(3, 5, 2)].Pallet = &VoxelPalletMap::All["OrientationCube"];
	Tree[VectorU3(2, 6, 2)].Pallet = &VoxelPalletMap::All["OrientationCube"];

	Tree[VectorU3(0, 3, 3)].Pallet = &VoxelPalletMap::All["OrientationCube"];
	Tree[VectorU3(1, 3, 3)].Pallet = &VoxelPalletMap::All["OrientationCube"];
	Tree[VectorU3(2, 3, 3)].Pallet = &VoxelPalletMap::All["OrientationCube"];
	Tree[VectorU3(3, 3, 3)].Pallet = &VoxelPalletMap::All["OrientationCube"];
	Tree[VectorU3(4, 3, 3)].Pallet = &VoxelPalletMap::All["OrientationCube"];
	Tree[VectorU3(1, 4, 3)].Pallet = &VoxelPalletMap::All["OrientationCube"];
	Tree[VectorU3(2, 4, 3)].Pallet = &VoxelPalletMap::All["OrientationCube"];
	Tree[VectorU3(3, 4, 3)].Pallet = &VoxelPalletMap::All["OrientationCube"];
	Tree[VectorU3(2, 5, 3)].Pallet = &VoxelPalletMap::All["OrientationCube"];

	Tree[VectorU3(1, 3, 4)].Pallet = &VoxelPalletMap::All["OrientationCube"];
	Tree[VectorU3(2, 3, 4)].Pallet = &VoxelPalletMap::All["OrientationCube"];
	Tree[VectorU3(3, 3, 4)].Pallet = &VoxelPalletMap::All["OrientationCube"];
	Tree[VectorU3(2, 4, 4)].Pallet = &VoxelPalletMap::All["OrientationCube"];

	Tree[VectorU3(2, 0, 2)].Pallet = &VoxelPalletMap::All["OrientationCylinder"];
	Tree[VectorU3(2, 1, 2)].Pallet = &VoxelPalletMap::All["OrientationCylinder"];
	Tree[VectorU3(2, 2, 2)].Pallet = &VoxelPalletMap::All["OrientationCylinder"];
	Tree[VectorU3(2, 3, 2)].Pallet = &VoxelPalletMap::All["OrientationCylinder"];
	Tree[VectorU3(2, 4, 2)].Pallet = &VoxelPalletMap::All["OrientationCylinder"];

	VectorI3 offset(-2, 0, -2);

	LoopU3 loop(0, Tree.Size());
	for (VectorU3 u = loop.Min(); loop.Check(u).All(true); loop.Next(u))
	{
		VectorU3 p = origin - offset + u;
		if ((p < Voxels.Size()).All(true))
		{
			if (Voxels[p].Pallet == nullptr)
			{
				Voxels[p] = Tree[u];
			}
		}
	}
}
void Chunk::GeneratePerlin(const Perlin2D & noise)
{
	VectorF3 Offset = Index * CHUNK_VALUES_PER_SIDE;
	LoopU2 loop(VectorU2(), VectorU2(CHUNK_VALUES_PER_SIDE));
	for (VectorU2 u = loop.Min(); loop.Check(u).All(true); loop.Next(u))
	{
		VectorF2 p2(
			Offset.X + u.X,
			Offset.Z + u.Y
		);

		float val = 0.0f;
		val += noise.Calculate(p2 / 256.0f) * 64;
		//val += noise.Calculate(p2 / 128.0f) * 128;
		//val += noise.Calculate(p2 / 64.0f) * 64;
		//val += noise.Calculate(p2 / 32.0f) * 32;
		//val += noise.Calculate(p2 / 16.0f) * 16;
		//val += noise.Calculate(p2 / 8.0f) * 8;
		//val += noise.Calculate(p2 / 4.0f) * 4;
		//val += noise.Calculate(p2 / 2.0f) * 2;
		//val += noise.Calculate(p2 / 1.0f) * 1;

		float val_rel = val - Offset.Y;
		for (unsigned int i = 0; i < CHUNK_VALUES_PER_SIDE; i++)
		{
			unsigned int voxel_u = VectorU3::Convert(CHUNK_VALUES_PER_SIDE, VectorU3(u.X, i, u.Y));
			if (i > val_rel)
			{
				Voxels[voxel_u].Pallet = nullptr;
			}
			else
			{
				//Voxels[voxel_u].Pallet = &VoxelPalletMap::All["Gray"];

				if (val < -1.0f) { Voxels[voxel_u].Pallet = &VoxelPalletMap::All["Water"]; }
				//else if (val < +1.0f) { Voxels[voxel_u].Pallet = &VoxelPalletMap::All["Sand"]; }
				else if (val < +1.0f) { Voxels[voxel_u].Pallet = &VoxelPalletMap::All["Dirt"]; }
				else { Voxels[voxel_u].Pallet = &VoxelPalletMap::All["Grass"]; }
			}
		}
	}
}
void Chunk::GeneratePerlin(const Perlin3D & noise)
{
	VectorF3 pos = Index * CHUNK_VALUES_PER_SIDE;
	LoopU3 loop(VectorU3(), VectorU3(CHUNK_VALUES_PER_SIDE));
	for (VectorU3 u = loop.Min(); loop.Check(u).All(true); loop.Next(u))
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
		{ Voxels[u].Pallet = nullptr; }
		else
		{ Voxels[u].Pallet = &VoxelPalletMap::All["Gray"]; }

		/*if (val > 0.1f)
		{
			if (Voxels[u].Pallet != nullptr)
			{
				Voxels[u].Pallet = nullptr;
			}
		}*/
	}
}

void Chunk::Generate(const Perlin2D & noise2, const Perlin3D & noise3)
{
	if (GenerationState != GenerationState::None) { return; }

	(void)noise2;
	(void)noise3;

	MakeNull();

//	GenerateGrid();
//	GeneratePlane();
//	GeneratePillars();
	GeneratePerlin(noise2);
//	GeneratePerlin(noise3);

	GeneratePillars(noise2);

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

	if (GenerationDone())
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



bool Chunk::Visible(VectorU3 udx, AxisRel axis) const
{
	const Chunk * chunk = Manager.NeighbourLoopChunk(*this, udx, axis);
	if (chunk == nullptr) { return false; }
	if (!chunk -> GenerationDone()) { return false; }
	if (chunk -> IsEmpty()) { return true; }
	const Voxel & voxel = (*chunk)[udx];
	return voxel.Visible(axis);
}

void Chunk::GraphicsUpdateMainData()
{
	if (MainBufferState != BufferDataState::Needed) { return; }

	if (!GenerationDone()) { return; }

	MainBufferData.Make(*this);

	MainBufferState = BufferDataState::Ready;
}
void Chunk::GraphicsUpdateMainBuffer()
{
	if (!GraphicsExist) { return; }

	if (MainBufferState != BufferDataState::Ready) { return; }

	Buffer.Main.Data(MainBufferData.Array);
	if (MainBufferData.Array.Count() != 0)
	{
		MainBufferData.Clear();
		MainBufferState = BufferDataState::Drawable;
	}
	else
	{
		MainBufferState = BufferDataState::None;
	}
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

		Buffer.Inst.Data(data);
	}

	InstBufferNeedsData = false;
}



void Chunk::Draw()
{
	if (!GraphicsExist) { return; }
	if (!GenerationDone()) { return; }
	if (BufferNeedsInit)
	{
		Buffer.Inst.Init();
		Buffer.Main.Init();
		BufferNeedsInit = false;
	}
	GraphicsUpdateMainBuffer();
	UpdateInstBuffer();
	if (MainBufferState != BufferDataState::None)
	{
		Buffer.Draw();
	}
}
