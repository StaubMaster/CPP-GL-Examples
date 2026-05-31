#include "Chunk.hpp"
#include "ChunkManager.hpp"
#include "ChunkNeighbours.hpp"

#include "VoxelPallet.hpp"

#include "Graphics/Inst/Data.hpp"

#include "VoxelOrientation.hpp"

#include "Structure.hpp"

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
#include "Telemetry/AuxThreadBase.hpp"



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
		BufferF.Delete();
	}*/
}
Chunk::Chunk(VectorI3 idx, ChunkManager & manager)
	: Index(idx)
	, Manager(manager)
	, Voxels()
	, Lock()
	, TerrainDone(false)
	, Decorations()
	, DecorationsGenerated(false)
	, DecorationsAssambled(false)
	, GraphicsExist(false)
	, BufferUData()
	, BufferUData_Entry(manager.BufferU)
	, BufferUData_Want(false)
	, BufferUData_Have(false)
//	, BufferF()
//	, BufferUMain_NewData(false)
//	, BufferFMain_NewData(false)
//	, BufferFInst_NewData(false)
{
	//BufferF.Main.Pos.Change(0);
	//BufferF.Main.Tex.Change(1);
	//BufferF.Main.Normal.Change(2);
	//BufferF.Inst.Pos.Change(3);

	Manager.AuxThread2.Poke();
	Manager.AuxThread3.Poke();
}



bool Chunk::InUse() const { return Lock.InUse(); }
void Chunk::AccessL() { Lock.AccessL(); }
void Chunk::AccessU() { Lock.AccessU(); }
bool Chunk::AccessT() { return Lock.AccessT(); }
void Chunk::AccessToAssign() { Lock.AccessToAssign(); }
void Chunk::AssignL() { Lock.AssignL(); }
void Chunk::AssignU() { Lock.AssignU(); }

AccessLockedChunk Chunk::ToAccess()
{
	AccessL();
	return AccessLockedChunk(this);
}
AccessLockedChunk Chunk::ToAccessTry()
{
	if (AccessT())
	{
		return AccessLockedChunk(this);
	}
	return AccessLockedChunk();
}
AssignLockedChunk Chunk::ToAssign()
{
	AssignL();
	return AssignLockedChunk(this);
}
/*AssignLockedChunk Chunk::ToAssignTry()
{
	if (AssignT())
	{
		return AssignLockedChunk(this);
	}
	return AssignLockedChunk();
}*/





bool Chunk::IsEmpty() const
{
	return Voxels.IsNull();
}
bool Chunk::IsNullOrEmpty() const
{
	if (IsEmpty()) { return true; }
	for (unsigned int i = 0; i < CHUNK_VALUES_PER_VOLM; i++)
	{
		if (!Voxels[i].IsEmpty())
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
		Neighbours.BufferDataWant();
	}
}
void Chunk::MakeNull()
{
	if (IsEmpty())
	{
		Voxels.Size(VectorU3(CHUNK_VALUES_PER_SIDE));
	}
	for (unsigned int i = 0; i < CHUNK_VALUES_PER_VOLM; i++)
	{
		Voxels[i] = Voxel();
	}
	Neighbours.BufferDataWant();
}



bool Chunk::ClearVoxel(VectorU3 udx, Voxel & vox)
{
	if (!GenerationDone()) { return false; }

	if (IsEmpty()) { return false; }

	Voxel & voxel = Voxels[udx];
	if (voxel.IsEmpty()) { return false; }

	vox = voxel;
	voxel = Voxel();

	if (IsNullOrEmpty()) { MakeEmpty(); }

	Neighbours.BufferDataWant();
	return true;
}
bool Chunk::PlaceVoxel(VectorU3 udx, Voxel & vox)
{
	if (!GenerationDone()) { return false; }

	if (IsEmpty()) { MakeNull(); }

	Voxel & voxel = Voxels[udx];
	if (!voxel.IsEmpty()) {return false; }

	voxel = vox;
	vox = Voxel();

	Neighbours.BufferDataWant();
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





bool Chunk::GenerationDone() const
{
	return TerrainDone && DecorationsGenerated && DecorationsAssambled;
}



void Chunk::GenerateTerrain(const ChunkGenerationNoise & noise)
{
	(void)noise;

	if (TerrainDone) { return; }

	MakeNull();

//	TerrainFlat(0, 0);
//	TerrainPillars();
	TerrainPlane(noise.Plane);
//	TerrainCaveNoodle(noise.Cave0, noise.Cave1);
//	TerrainCaveBlob(noise.Cave2);

	TerrainDone = true;
	Manager.AuxThread3.Poke();
}

/*
Condition: Y <= 0
Place: ConcreteCube
*/
void Chunk::TerrainFlat(int y_chunk, unsigned int y_voxel)
{
	// 0.016s

	const VoxelPallet & pallet_dirt = VoxelPalletMap::All["Dirt"];
	const VoxelPallet & pallet_grass = VoxelPalletMap::All["Grass"];

	(void)pallet_dirt;
	(void)pallet_grass;

	if (Index.Y == y_chunk)
	{
		LoopU3 loop(0, Voxels.Size());
		for (VectorU3 u = loop.Min(); loop.Check(u).All(true); loop.Next(u))
		{
			if (u.Y == y_voxel)
			{
				Voxels[u] = pallet_grass.ToVoxel();
			}
			else if (u.Y < y_voxel)
			{
				Voxels[u] = pallet_dirt.ToVoxel();
			}
		}
	}
	else if (Index.Y < y_chunk)
	{
		LoopU3 loop(0, Voxels.Size());
		for (VectorU3 u = loop.Min(); loop.Check(u).All(true); loop.Next(u))
		{
			Voxels[u] = pallet_dirt.ToVoxel();
		}
	}
}
/*
Condition: Y == 0 || Y == 31
Place: ConcreteCube

Condition: ((X == 7 || X == 24) && (Z == 7 || Z == 24))
Place: ConcreteCylinder
*/
void Chunk::TerrainPillars()
{
	//0123456789ABCDEF0123456789ABCDEF
	//       #                #       

	VectorI3 chunk_pos = Index * CHUNK_VALUES_PER_SIDE;

	const VoxelPallet & pallet0 = VoxelPalletMap::All["ConcreteCube"];
	const VoxelPallet & pallet1 = VoxelPalletMap::All["ConcreteCylinder"];

	LoopU3 loop3(VectorU3(), Voxels.Size());
	for (VectorU3 u = loop3.Min(); loop3.Check(u).All(true); loop3.Next(u))
	{
		if (u.Y == 0 || u.Y == 31)
		{ Voxels[u] = pallet0.ToVoxel(); }
		//else if ((u.X == 7 || u.X == 24) && (u.Z == 7 || u.Z == 24))
		else if ((u.X == 1 || u.X == 30) && (u.Z == 1 || u.Z == 30))
		{ Voxels[u] = pallet1.ToVoxel(); }
	}
}

void Chunk::TerrainPlane(const Perlin2D & noise)
{
	const VoxelPallet & pallet_gray = VoxelPalletMap::All["Gray"];
	const VoxelPallet & pallet_dirt = VoxelPalletMap::All["Dirt"];
	const VoxelPallet & pallet_grass = VoxelPalletMap::All["Grass"];
	const VoxelPallet & pallet_water = VoxelPalletMap::All["Water"];

	(void)pallet_gray;
	(void)pallet_dirt;
	(void)pallet_grass;
	(void)pallet_water;

	VectorF3 Offset = Index * CHUNK_VALUES_PER_SIDE;
	LoopU2 loop(VectorU2(), VectorU2(CHUNK_VALUES_PER_SIDE));
	for (VectorU2 u = loop.Min(); loop.Check(u).All(true); loop.Next(u))
	{
		VectorF2 p2(
			Offset.X + u.X,
			Offset.Z + u.Y
		);

		float val = 0.0f;

		//val += noise.Calculate(p2 / 128.0f) * 128;
		//val += noise.Calculate(p2 / 64.0f) * 64;
		//val += noise.Calculate(p2 / 32.0f) * 32;
		//val += noise.Calculate(p2 / 16.0f) * 16;
		//val += noise.Calculate(p2 / 8.0f) * 8;
		//val += noise.Calculate(p2 / 4.0f) * 4;
		//val += noise.Calculate(p2 / 2.0f) * 2;
		//val += noise.Calculate(p2 / 1.0f) * 1;

		//val += noise.Calculate(p2 / 1.0f) * 1.0f;
		//val += noise.Calculate(p2 / 2.0f) * 2.0f;
		//val += noise.Calculate(p2 / 4.0f) * 4.0f;
		//val += noise.Calculate(p2 / 8.0f) * 8.0f;
		//val += noise.Calculate(p2 / 16.0f) * 16.0f;
		//val += noise.Calculate(p2 / 32.0f) * 32.0f;
		//val += noise.Calculate(p2 / 64.0f) * 64.0f;
		//val += noise.Calculate(p2 / 128.0f) * 128.0f;
		//val += noise.Calculate(p2 / 256.0f) * 256.0f;

		val += noise.Calculate(p2 / 256.0f) * 64;

		for (unsigned int y = 0; y < CHUNK_VALUES_PER_SIDE; y++)
		{
			unsigned int voxel_u = VectorU3::Convert(CHUNK_VALUES_PER_SIDE, VectorU3(u.X, y, u.Y));
			int abs_y = y + Offset.Y;
			float diff = val - abs_y;
			if (diff < 0.0f)
			{
				Voxels[voxel_u] = Voxel();
				//if (abs_y < 0)
				//{ Voxels[voxel_u] = pallet_water.ToVoxel(); }
			}
			else if (diff < 1.0f)
			{
				{ Voxels[voxel_u] = pallet_grass.ToVoxel(); }
				//if (abs_y >= 0)
				//{ Voxels[voxel_u] = pallet_grass.ToVoxel(); }
				//else
				//{ Voxels[voxel_u] = pallet_dirt.ToVoxel(); }
			}
			else if (diff < 4.0f) { Voxels[voxel_u] = pallet_dirt.ToVoxel(); }
			else                  { Voxels[voxel_u] = pallet_gray.ToVoxel(); }
		}
	}
}

void Chunk::TerrainCaveNoodle(const Perlin3D & noise0, const Perlin3D & noise1)
{
	//if (Index.Y >= 0) { return; }
	//if (Index.Y != -1) { return; }
	if (IsEmpty()) { return; }

	(void)noise0;
	(void)noise1;

	const VoxelPallet & pallet_r = VoxelPalletMap::All["DebugR"];
	const VoxelPallet & pallet_g = VoxelPalletMap::All["DebugG"];
	const VoxelPallet & pallet_b = VoxelPalletMap::All["DebugB"];

	(void)pallet_r;
	(void)pallet_g;
	(void)pallet_b;

	const float range = 4.0f;
	const float center = 0.0f;
	const float min = center - range;
	const float max = center + range;

	VectorF3 Offset = Index * CHUNK_VALUES_PER_SIDE;
	LoopU3 loop(VectorU3(), VectorU3(CHUNK_VALUES_PER_SIDE));
	for (VectorU3 u = loop.Min(); loop.Check(u).All(true); loop.Next(u))
	{
		//if (u.Y != 31) { continue; }
		VectorF3 p(
			Offset.X + u.X,
			Offset.Y + u.Y,
			Offset.Z + u.Z
		);

		const float factor = 128.0f;
		float val0 = noise0.Calculate(p / factor) * factor;
		float val1 = noise1.Calculate(p / factor) * factor;

		//if (!(val0 > min && val0 < max)) { Voxels[u] = pallet_r.ToVoxel(); }
		//if (!(val1 > min && val1 < max)) { Voxels[u] = pallet_b.ToVoxel(); }
		if ((val0 > min && val0 < max) && (val1 > min && val1 < max)) { Voxels[u] = pallet_g.ToVoxel(); }
		//if ((val0 > min && val0 < max) && (val1 > min && val1 < max)) { Voxels[u] = Voxel(); }

		/*float val0 = 0.0f;
		//val += noise.Calculate(p / 32.0f) * 32.0f;
		//val += noise.Calculate(p / 64.0f) * 64.0f;
		//val += noise.Calculate(p / 128.0f) * 128.0f;
		val0 += noise0.Calculate(p / 256.0f) * 256.0f;
		//val += noise.Calculate(p / 512.0f) * 512.0f;

		if (val0 > min && val0 < max)
		{
			Voxels[u] = pallet_g.ToVoxel();
		}
		else if (val0 < 0.0f)
		{
			//Voxels[u] = pallet_b.ToVoxel();
		}
		else if (val0 > 0.0f)
		{
			//Voxels[u] = pallet_r.ToVoxel();
		}*/
	}
}

/*
Condition:
Place: OrientationCube
*/
void Chunk::TerrainGrid()
{
	VectorI3 chunk_pos = Index * CHUNK_VALUES_PER_SIDE;

	LoopU3 loop3(VectorU3(), Voxels.Size());
	for (VectorU3 u = loop3.Min(); loop3.Check(u).All(true); loop3.Next(u))
	{
		VectorI3 voxel_idx = chunk_pos + u;
		VectorF3 voxel_pos = voxel_idx;

		VectorF3 grid_pos = voxel_pos.round(256);
		VectorF3 grid_rel = voxel_pos - grid_pos + VectorF3(0.5f);

		if (grid_rel.length() < 4.0f) { Voxels[u] = VoxelPalletMap::All["OrientationCube"].ToVoxel(); }
		if (VectorF3(grid_rel.X, grid_rel.Y, 0.0f).length() < 2.0f) { Voxels[u] = VoxelPalletMap::All["OrientationCube"].ToVoxel(); }
		if (VectorF3(grid_rel.X, 0.0f, grid_rel.Z).length() < 2.0f) { Voxels[u] = VoxelPalletMap::All["OrientationCube"].ToVoxel(); }
		if (VectorF3(0.0f, grid_rel.Y, grid_rel.Z).length() < 2.0f) { Voxels[u] = VoxelPalletMap::All["OrientationCube"].ToVoxel(); }
	}
}

void Chunk::TerrainCity()
{
	const VoxelPallet & pallet = VoxelPalletMap::All["ConcreteCube"];

	LoopU3 loop3(VectorU3(), Voxels.Size());
	for (VectorU3 u = loop3.Min(); loop3.Check(u).All(true); loop3.Next(u))
	{
		if ((u.X == 8 || u.X == 11 || u.X == 14 || u.X == 17 || u.X == 20 || u.X == 23) &&
			(u.Z == 8 || u.Z == 11 || u.Z == 14 || u.Z == 17 || u.Z == 20 || u.Z == 23))
		{
			Voxels[u] = pallet.ToVoxel();
		}
		if ((u.X >= 8 && u.X <= 23) && (u.Z >= 8 && u.Z <= 23) &&
			(u.Y == 4 || u.Y == 27))
		{
			Voxels[u] = pallet.ToVoxel();
		}
	}
}



void Chunk::GenerateDecoration(const Perlin2D & noise2, const Perlin3D & noise3)
{
	(void)noise2;
	(void)noise3;

	if (DecorationsGenerated) { return; }

	if ((Index.X % 2 == 0) && (Index.Z % 2 == 0))
	{
		StructureObject obj;
		obj.Structure = &Structure::Tree1;
		obj.Origin = VectorU3(15, 0, 15);
		if (FindMinYNull(obj.Origin))
		{ Decorations.Insert(obj); }
	}

	//DecorateTrees(noise2);

	DecorationsGenerated = true;
	Manager.AuxThread3.Poke();
}

bool Chunk::FindMinYNull(VectorU3 & udx) const
{
	udx.Y = CHUNK_VALUES_PER_SIDE - 1;
	if (!Voxels[udx].IsEmpty())
	{
		return false;
	}
	for (; udx.Y < CHUNK_VALUES_PER_SIDE; udx.Y--)
	{
		if (!Voxels[udx].IsEmpty())
		{
			udx.Y++;
			return true;
		}
	}
	udx.Y = CHUNK_VALUES_PER_SIDE;
	return false;
}
void Chunk::DecorateTrees(const Perlin2D & noise)
{
//	if (Index.Z < 1) { return; }
//	if (Index.Y < 0) { return; }
//	if (Index.Y > 0) { return; }

	(void)noise;

	const VoxelPallet & pallet_r = VoxelPalletMap::All["DebugR"];
	const VoxelPallet & pallet_g = VoxelPalletMap::All["DebugG"];
	const VoxelPallet & pallet_b = VoxelPalletMap::All["DebugB"];

	(void)pallet_r;
	(void)pallet_g;
	(void)pallet_b;

	//const float range = 0.1f;
	//const float center = 0.0f;
	//const float min = center - range;
	//const float max = center + range;

	const VoxelPallet & pallet = VoxelPalletMap::All["OrientationCube"];
	(void)pallet;

	VectorI3 Offset = Index * (int)CHUNK_VALUES_PER_SIDE;
	for (unsigned int z = 0; z < CHUNK_VALUES_PER_SIDE; z++)
	{
		for (unsigned int x = 0; x < CHUNK_VALUES_PER_SIDE; x++)
		{
			//VectorF2 pos(Offset.X + (int)x, Offset.Z + (int)z);

			//float val = 0.0f;

			//val += noise.Calculate(pos / 001.0f) * 1.0f;
			//val += noise.Calculate(pos / 002.0f) * 1.0f;
			//val += noise.Calculate(pos / 003.0f) * 1.0f;
			//val += noise.Calculate(pos / 005.0f) * 1.0f;
			//val += noise.Calculate(pos / 007.0f) * 1.0f;
			//val += noise.Calculate(pos / 011.0f) * 1.0f;
			//val += noise.Calculate(pos / 013.0f) * 1.0f;

			//val += noise.Calculate(pos / 001.0f) * 1.0f;
			//val += noise.Calculate(pos / 002.0f) * 1.0f;
			//val += noise.Calculate(pos / 004.0f) * 1.0f;
			//val += noise.Calculate(pos / 008.0f) * 1.0f;
			//val += noise.Calculate(pos / 016.0f) * 1.0f;
			//val += noise.Calculate(pos / 032.0f) * 1.0f;
			//val += noise.Calculate(pos / 064.0f) * 1.0f;
			//val += noise.Calculate(pos / 128.0f) * 1.0f;
			//val += noise.Calculate(pos / 256.0f) * 1.0f;

			//if (val == 0.0f)
			//if (val > -0.01f && val < +0.01f)
			{
				//for (unsigned int y = 0; y < CHUNK_VALUES_PER_SIDE; y++)
				{
					//VectorU3 u(x, 0, z);

					//if (val >= min && val <= max) { Voxels[u] = pallet_g.ToVoxel(); }
					//else if (val > 0.0f) { Voxels[u] = pallet_r.ToVoxel(); }
					//else if (val < 0.0f) { Voxels[u] = pallet_b.ToVoxel(); }

					//Voxels[VectorU3(x, y, z)] = pallet.ToVoxel();
					/*if ((Offset.Y + y) < val)
					{
						Voxels[VectorU3(x, y, z)] = pallet.ToVoxel();
					}*/
				}
				/*VectorU3 origin = TopVoxel(*this, VectorU3(x, 0, z));
				if (origin.Y < CHUNK_VALUES_PER_SIDE)
				{
					Voxels[origin] = pallet.ToVoxel();
				}*/
				//StructureObject obj;
				//obj.Structure = &Structure::Tree0;
				//obj.Origin = TopVoxel(*this, VectorU3(x, 0, z));
				//Decorations.Insert(obj);
			}
		}
	}


	/*
		know Axis Neighbours
		only the touching face, like for BufferData
	*/

	for (unsigned int z = 1; z < CHUNK_VALUES_PER_SIDE; z += 4)
	{
		for (unsigned int x = 1; x < CHUNK_VALUES_PER_SIDE; x += 4)
		{
			StructureObject obj;
			obj.Structure = &Structure::Tree0;
			obj.Origin = VectorU3(x, 0, z);
			if (FindMinYNull(obj.Origin))
			{ Decorations.Insert(obj); }
		}
		z += 4;
		for (unsigned int x = 3; x < CHUNK_VALUES_PER_SIDE; x += 4)
		{
			StructureObject obj;
			obj.Structure = &Structure::Tree0;
			obj.Origin = VectorU3(x, 0, z);
			if (FindMinYNull(obj.Origin))
			{ Decorations.Insert(obj); }
		}
	}
}



void Chunk::AssambleDecoration()
{
	if (DecorationsAssambled) { return; }

	for (int z = 0; z < 3; z++)
	{
		for (int y = 0; y < 3; y++)
		{
			for (int x = 0; x < 3; x++)
			{
				const Chunk & chunk = *Neighbours.Cube[z][y][x];
				for (unsigned int i = 0; i < chunk.Decorations.Count(); i++)
				{
					AssambleDecoration(chunk.Decorations[i], VectorI3(x - 1, y - 1, z - 1) * CHUNK_VALUES_PER_SIDE);
				}
			}
		}
	}

	//Decorations.Clear();

	if (IsNullOrEmpty()) { MakeEmpty(); }

	DecorationsAssambled = true;
	Manager.AuxThread3.Poke();

	if (GraphicsExist)
	{
		Neighbours.BufferDataWant();
		Manager.AuxThread1.QueuePut(this);
	}
}

void Chunk::AssambleDecoration(const StructureObject & obj, const VectorI3 & offset)
{
	if (obj.Structure == nullptr) { return; }

	const Structure & structure = *obj.Structure;
	LoopU3 loop(VectorU3(), structure.Voxels.Size());
	for (VectorU3 u = loop.Min(); loop.Check(u).All(true); loop.Next(u))
	{
		VectorU3 p = obj.Origin - structure.Center + u + offset;
		if ((p < Voxels.Size()).All(true))
		{
			if (!structure.Voxels[u].IsEmpty())
			{
				Voxels[p] = structure.Voxels[u];
			}
		}
	}
}





void Chunk::GraphicsCreate()
{
	if (GraphicsExist) { return; }

	GraphicsExist = true;

	BufferUData_Have = false;

	if (GenerationDone())
	{
		Manager.AuxThread1.QueuePut(this);
	}
}
void Chunk::GraphicsDelete()
{
	if (!GraphicsExist) { return; }

	//BufferF.Delete();

	GraphicsExist = false;
}

void Chunk::BufferUData_Make()
{
	if (!BufferUData_Want) { return; }
	if (!GenerationDone()) { return; }

	BufferUData.Make(*this, Neighbours);

	BufferUData_Want = false;
	BufferUData_Have = true;

	Manager.BufferDataHaveQueueMutex.lock();
	Manager.BufferDataHaveQueue.Insert(this);
	Manager.BufferDataHaveQueueMutex.unlock();
}

void Chunk::BufferUData_Update()
{
	if (!GraphicsExist) { return; }
	if (!BufferUData_Have) { return; }

	BufferUData.ArrayLock.lock();
	BufferUData_Entry.Put(BufferUData.GraphicsDataU());
	BufferUData.ClearU();
	BufferUData.ArrayLock.unlock();

	BufferUData_Have = false;
}

/*void Chunk::BufferFMain_UpdateData()
{
	if (!GraphicsExist) { return; }
	if (!BufferFMain_NewData) { return; }

	BufferUData.ArrayLock.lock();
	//BufferF.Main.DataFull(BufferUData.GraphicsDataF().ToVoid());
	BufferUData.ClearF();
	BufferUData.ArrayLock.unlock();

	BufferFMain_NewData = false;
}*/
/*void Chunk::BufferFInst_UpdateData()
{
	if (!GraphicsExist) { return; }
	if (!BufferFInst_NewData) { return; }

	{
		Container::Binary<VoxelGraphics::InstData> data;

		VoxelGraphics::InstData temp;
		temp.Pos = Index * CHUNK_VALUES_PER_SIDE;
		data.Insert(temp);

		//BufferF.Inst.DataFull(data.ToVoid());
	}

	BufferFInst_NewData = false;
}*/
/*void Chunk::DrawF()
{
	if (!GraphicsExist) { return; }
	BufferFMain_UpdateData();
	BufferFInst_UpdateData();
}*/
