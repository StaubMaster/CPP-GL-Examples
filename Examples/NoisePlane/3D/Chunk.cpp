#include "3D/Chunk.hpp"
#include "3D/Chunk/Manager.hpp"

#include "Threading/ObjectTypeAccessUniqueGuard.hpp"
//#include "Threading/ObjectTypeAccessSharedGuard.hpp"
#include "Threading/ObjectTypeAssignUniqueGuard.hpp"
//#include "Threading/ObjectTypeAssignSharedGuard.hpp"

//#include <iostream>

#include "AuxThread/Collection.hpp"



const Voxel & Chunk::operator[](unsigned int udx) const
{
	return Voxels[udx];
}
const Voxel & Chunk::operator[](const VectorU3 & udx) const
{
	return Voxels[udx];
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
		Neighbours.BufferDataWantAll(); // this should be done outside
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
	Neighbours.BufferDataWantAll(); // this should be done outside
}

bool Chunk::ClearVoxel(const VectorU3 & udx, Voxel & vox)
{
	if (!IsDone()) { return false; }

	if (IsEmpty()) { return false; }

	Voxel & voxel = Voxels[udx];
	if (voxel.IsEmpty()) { return false; }

	vox = voxel;
	voxel = Voxel();

	if (IsNullOrEmpty()) { MakeEmpty(); }

	Neighbours.BufferDataWant(udx);
	return true;
}
bool Chunk::PlaceVoxel(const VectorU3 & udx, Voxel & vox)
{
	if (!IsDone()) { return false; }

	if (IsEmpty()) { MakeNull(); }

	Voxel & voxel = Voxels[udx];
	if (!voxel.IsEmpty()) {return false; }

	voxel = vox;
	vox = Voxel();

	Neighbours.BufferDataWant(udx);
	return true;
}



Chunk::~Chunk()
{
	//std::cout << "delete Chunk " << Index << '\n';
}
Chunk::Chunk(VectorI3 idx, ChunkManager & manager)
	: Index(idx)
	, Manager(manager)
	, Neighbours()
	, Voxels()
	, Lock()
	, TerrainDone(false)
	, Decorations()
	, DecorationsGenerated(false)
	, DecorationsAssambled(false)
	, GraphicsData()
	, BufferData_Want(false)
	, BufferData_Have(false)
	, GraphicsDataU_Entry(Manager.Graphics.BufferU)
	, GraphicsDataF_Entry(Manager.Graphics.BufferF)
{ }



bool Chunk::InUse() const		{ return Lock.InUse(); }

//void Chunk::AccessL()			{ Lock.AccessL(); }
//void Chunk::AccessU()			{ Lock.AccessU(); }
//bool Chunk::AccessT()			{ return Lock.AccessT(); }

//void Chunk::AssignL()			{ Lock.AssignL(); }
//void Chunk::AssignU()			{ Lock.AssignU(); }

//void Chunk::AccessToAssign()	{ Lock.AccessToAssign(); }

//ObjectTypeAccessUniqueGuard<Chunk>	Chunk::ToAccessUniqueMake()		{ return ObjectTypeAccessUniqueGuard<Chunk>::Make(Lock, *this); }

AccessLockedChunk	Chunk::ToAccessMake()		{ return AccessLockedChunk::Make(Lock, *this); }
AccessLockedChunk	Chunk::ToAccessTake()		{ return AccessLockedChunk::Take(Lock, *this); }
//AccessLockedChunk	Chunk::ToAccessTry()		{ return AccessLockedChunk::Try(Lock, *this); }

AccessLockedChunk	Chunk::ToAccessTake(Chunk * chunk)
{
	if (chunk != nullptr)
	{
		return chunk -> ToAccessTake();
	}
	return AccessLockedChunk();
}

AssignLockedChunk	Chunk::ToAssign()	{ return AssignLockedChunk::Make(Lock, *this); }



bool Chunk::IsDone() const
{
	return TerrainDone && DecorationsGenerated && DecorationsAssambled;
}



void Chunk::GraphicsData_Make_Queue()
{
	BufferData_Want = true;
	Manager.AuxThreadCollection.AuxThread1.QueuePut(*this);
}
bool Chunk::GraphicsData_Make_Can() const
{
	return BufferData_Want && IsDone() && Neighbours.CanMakeBuffer();
}
void Chunk::GraphicsData_Make()
{
	if (!GraphicsData_Make_Can()) { return; }

	GraphicsData.Make(*this, Neighbours);

	BufferData_Want = false;

	GraphicsData_Put_Queue();
}

void Chunk::GraphicsData_Put_Queue()
{
	BufferData_Have = true;
	Manager.Graphics.Queue.Put(*this);
}
bool Chunk::GraphicsData_Put_Can() const
{
	return BufferData_Have;
}
void Chunk::GraphicsData_Put()
{
	if (!GraphicsData_Put_Can()) { return; }

	GraphicsData.ArrayLock.lock();
	{
		const Container::Array<VoxelGraphicsDataU::Face> & data = GraphicsData.DataU();
		GraphicsDataU_Entry.Put(data.ToVoid());
		GraphicsData.ClearU();
	}
	{
		const Container::Array<VoxelGraphicsDataF::Face> & data = GraphicsData.DataF();
		GraphicsDataF_Entry.Put(data.ToVoid());
		GraphicsData.ClearF();
	}
	GraphicsData.ArrayLock.unlock();

	BufferData_Have = false;
}
