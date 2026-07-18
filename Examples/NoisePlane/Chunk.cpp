#include "Chunk.hpp"
#include "Chunk/Manager.hpp"
#include "Chunk/Neighbours.hpp"

#include "Voxel/Pallet.hpp"

#include "Graphics/Inst/Data.hpp"

#include "Axis/Orientation.hpp"

#include "Structure.hpp"

#include "ValueGen/Perlin2D.hpp"
#include "ValueGen/Perlin3D.hpp"

#include "ValueType/Box/I3.hpp"

#include "ValueType/Bool/3.hpp"
#include "ValueType/Vector/U3.hpp"

#include "ValueType/Vector/U2.hpp"
#include "ValueType/Loop/U2.hpp"

#include "ValueType/Vector/U3.hpp"
#include "ValueType/Loop/U3.hpp"

#include "Telemetry/StopWatch.hpp"
#include "AuxThreadBase.hpp"

#include "ContainerLock/AccessTypeGuard.hpp"
#include "ContainerLock/AssignTypeGuard.hpp"



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
	//std::cout << "delete Chunk " << Index << '\n';
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
	, BufferUData()
	, BufferUData_Entry(manager.BufferU)
	, BufferUData_Want(false)
	, BufferUData_Have(false)
{ }



bool Chunk::InUse() const { return Lock.InUse(); }
void Chunk::AccessL() { Lock.AccessL(); }
void Chunk::AccessU() { Lock.AccessU(); }
bool Chunk::AccessT() { return Lock.AccessT(); }
void Chunk::AccessToAssign() { Lock.AccessToAssign(); }
void Chunk::AssignL() { Lock.AssignL(); }
void Chunk::AssignU() { Lock.AssignU(); }

AccessLockedChunk Chunk::ToAccess() { return AccessLockedChunk::MakeLock(Lock, *this); }
AccessLockedChunk Chunk::ToAccessTry() { return AccessLockedChunk::TryLock(Lock, *this); }
AssignLockedChunk Chunk::ToAssign()
{
	AssignL();
	return AssignLockedChunk::TakeLock(Lock, *this);
}

AccessLockedChunk Chunk::ToAccess(Chunk * chunk)
{
	if (chunk != nullptr)
	{
		return AccessLockedChunk::TakeLock(chunk -> Lock, *chunk);
	}
	return AccessLockedChunk();
}




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





void Chunk::BufferUData_Make()
{
	if (!BufferUData_Want) { return; }
	if (!GenerationDone()) { return; }

	BufferUData.Make(*this, Neighbours);

	BufferUData_Want = false;

	Manager.BufferDataHave.QueuePut(this);
}

void Chunk::BufferUData_Update()
{
	if (!BufferUData_Have) { return; }

	BufferUData.ArrayLock.lock();
	BufferUData_Entry.Put(BufferUData.GraphicsDataU());
	BufferUData.ClearU();
	BufferUData.ArrayLock.unlock();

	BufferUData_Have = false;
}
