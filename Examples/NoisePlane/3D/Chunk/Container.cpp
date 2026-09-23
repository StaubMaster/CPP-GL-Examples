#include "3D/Chunk/Container.hpp"
#include "3D/Chunk/Manager.hpp"
#include "3D/Chunk.hpp"

#include "Threading/ObjectTypeAccessUniqueGuard.hpp"
//#include "Threading/ObjectTypeAccessSharedGuard.hpp"
#include "Threading/ObjectTypeAssignUniqueGuard.hpp"
//#include "Threading/ObjectTypeAssignSharedGuard.hpp"

#include "ValueType/Loop/I3.hpp"
#include "ValueType/Loop/U3.hpp"

#include "ValueType/_Show.hpp"
#include <iostream>

#include "Telemetry/StopWatch.hpp"

#include "AuxThread/Collection.hpp"



ChunkContainer::~ChunkContainer()
{
	for (unsigned int i = 0; i < Chunks.Length(); i++)
	{
		delete Chunks[i];
	}
}
ChunkContainer::ChunkContainer(ChunkManager & manager)
	: Manager(manager)
{ }



bool ChunkContainer::AbsoluteCheckCareBox(const VectorI3 & idx) const
{
	return CareBox.ContainsInclusive(idx).All(true);
}
bool ChunkContainer::AbsoluteCheckKnowBox(const VectorI3 & idx) const
{
	return KnowBox.ContainsInclusive(idx).All(true);
}

VectorI3 ChunkContainer::RelativeToAbsolute(VectorU3 u) const
{
	return (u.ToI() + KnowBox.Min);
}
VectorU3 ChunkContainer::AbsoluteToRelative(VectorI3 i) const
{
	return (i - KnowBox.Min).ToU();
}
VectorI3 ChunkContainer::CenteredToAbsolute(VectorI3 i) const
{
	return (i + Center);
}
VectorI3 ChunkContainer::AbsoluteToCentered(VectorI3 i) const
{
	return (i - Center);
}



Chunk * ChunkContainer::FindAbsolutePointer(VectorI3 idx)
{
	VectorU3 udx = AbsoluteToRelative(idx);
	if (Chunks.Check(udx))
	{
		return Chunks[udx];
	}
	return nullptr;
}
Chunk * ChunkContainer::FindCenteredPointer(VectorI3 idx)
{
	VectorU3 udx = AbsoluteToRelative(CenteredToAbsolute(idx));
	if (Chunks.Check(udx))
	{
		return Chunks[udx];
	}
	return nullptr;
}

AccessLockedChunk ChunkContainer::FindAbsoluteAccess(VectorI3 idx)
{
	Chunk * chunk = FindAbsolutePointer(idx);
	if (chunk != nullptr)
	{
		return chunk -> ToAccessMake();
	}
	return AccessLockedChunk();
}



void ChunkContainer::Clear()
{
//	std::cout << "Clear:" << __LINE__ << '\n';
	for (unsigned int i = 0; i < Chunks.Length(); i++)
	{
		//Chunks[i] -> GraphicsDelete();
		delete Chunks[i];
	}
//	std::cout << "Clear:" << __LINE__ << '\n';
}
/* size
know: all the Chunks that are stored
care: where Chunks are inserted / generated
*/
void ChunkContainer::ChangeSize(unsigned int know_size, unsigned int care_size)
{
	KnowSize = know_size;
	CareSize = care_size;
//	std::cout << "ChangeChunksArraySize:" << __LINE__ << '\n';
	ChunksLock.AssignL();
//	std::cout << "ChangeChunksArraySize:" << __LINE__ << '\n';
	Clear();
//	std::cout << "ChangeChunksArraySize:" << __LINE__ << '\n';
	KnowBox = BoxI3(Center - (int)KnowSize, Center + (int)KnowSize);
	CareBox = BoxI3(Center - (int)CareSize, Center + (int)CareSize);
//	std::cout << "ChangeChunksArraySize:" << __LINE__ << '\n';
	Chunks.Size(VectorU3((KnowSize * 2) + 1), nullptr);
//	std::cout << "ChangeChunksArraySize:" << __LINE__ << '\n';
	ChunksLock.AssignU();
//	std::cout << "ChangeChunksArraySize:" << __LINE__ << '\n';
	PutMissingCareChunks();
}

static VectorU3 ChunkSkipped;
static VectorU3 ChunkMoved;
/* dont have ChunkToRemove here ?
put moved in NewChunks
leave old chunks in Chunks
set moved chunks in Chunks to null
after, collect from Chunks into ChunksToRemove
*/
static void ChangeCenterMoveX(const Array3D<Chunk*> & Chunks, Array3D<Chunk*> & NewChunks, Container::Binary<Chunk*> & ChunksToRemove, VectorU3 u, VectorI3 diff)
{
	unsigned int udx0 = Chunks.Size().Convert(u);
	if (Chunks[udx0] != nullptr) { ChunksToRemove.Insert(Chunks[udx0]); }
	NewChunks[udx0] = nullptr;

	if (((int)u.X) + diff.X < 0) { ChunkSkipped.X++; return; }
	if (((int)u.X) + diff.X >= (int)Chunks.Size().X) { ChunkSkipped.X++; return; }

	unsigned int udx1 = Chunks.Size().Convert(VectorU3(u.X + diff.X, u.Y, u.Z));
	NewChunks[udx0] = Chunks[udx1];
	NewChunks[udx1] = nullptr;
	ChunkMoved.X++;
}
static void ChangeCenterMoveY(const Array3D<Chunk*> & Chunks, Array3D<Chunk*> & NewChunks, Container::Binary<Chunk*> & ChunksToRemove, VectorU3 u, VectorI3 diff)
{
	unsigned int udx0 = Chunks.Size().Convert(u);
	if (Chunks[udx0] != nullptr) { ChunksToRemove.Insert(Chunks[udx0]); }
	NewChunks[udx0] = nullptr;

	if (((int)u.Y) + diff.Y < 0) { ChunkSkipped.Y++; return; }
	if (((int)u.Y) + diff.Y >= (int)Chunks.Size().Y) { ChunkSkipped.Y++; return; }

	unsigned int udx1 = Chunks.Size().Convert(VectorU3(u.X, u.Y + diff.Y, u.Z));
	NewChunks[udx0] = Chunks[udx1];
	NewChunks[udx1] = nullptr;
	ChunkMoved.Y++;
}
static void ChangeCenterMoveZ(const Array3D<Chunk*> & Chunks, Array3D<Chunk*> & NewChunks, Container::Binary<Chunk*> & ChunksToRemove, VectorU3 u, VectorI3 diff)
{
	unsigned int udx0 = Chunks.Size().Convert(u);
	if (Chunks[udx0] != nullptr) { ChunksToRemove.Insert(Chunks[udx0]); }
	NewChunks[udx0] = nullptr;

	if (((int)u.Z) + diff.Z < 0) { ChunkSkipped.Z++; return; }
	if (((int)u.Z) + diff.Z >= (int)Chunks.Size().Z) { ChunkSkipped.Z++; return; }

	unsigned int udx1 = Chunks.Size().Convert(VectorU3(u.X, u.Y, u.Z + diff.Z));
	NewChunks[udx0] = Chunks[udx1];
	NewChunks[udx1] = nullptr;
	ChunkMoved.Z++;
}
void ChunkContainer::ChangeCenter(VectorI3 center)
{
	if ((Center == center).All(true)) { return; }

	ChunksLock.AssignL();
	ChunksToRemoveLock.AssignL();

	//Array3D<Chunk*> new_chunks(Chunks.Size());
	Array3D<Chunk*> new_chunks(Chunks);

	// make a new Array, then replace the old one
	// dont put into ToRemove until done
	// make a temp Binary Array for that as well
	// give Binary a Insert(Array)
	//   this would allocate every tine Center changes
	//   the current version dosent do that

	VectorI3 diff = center - Center;

	ChunkSkipped = VectorU3(0);
	ChunkMoved = VectorU3(0);

	LoopU3 loop(VectorU3(), Chunks.Size());

	if (diff.X > 0) { for (VectorU3 u = loop.Min(); loop.Check(u).All(true); loop.Next(u)) { ChangeCenterMoveX(Chunks, new_chunks, ChunksToRemove, u, diff); } }
	if (diff.X < 0) { for (VectorU3 u = loop.Max(); loop.Check(u).All(true); loop.Prev(u)) { ChangeCenterMoveX(Chunks, new_chunks, ChunksToRemove, u, diff); } }

	if (diff.Y > 0) { for (VectorU3 u = loop.Min(); loop.Check(u).All(true); loop.Next(u)) { ChangeCenterMoveY(Chunks, new_chunks, ChunksToRemove, u, diff); } }
	if (diff.Y < 0) { for (VectorU3 u = loop.Max(); loop.Check(u).All(true); loop.Prev(u)) { ChangeCenterMoveY(Chunks, new_chunks, ChunksToRemove, u, diff); } }

	if (diff.Z > 0) { for (VectorU3 u = loop.Min(); loop.Check(u).All(true); loop.Next(u)) { ChangeCenterMoveZ(Chunks, new_chunks, ChunksToRemove, u, diff); } }
	if (diff.Z < 0) { for (VectorU3 u = loop.Max(); loop.Check(u).All(true); loop.Prev(u)) { ChangeCenterMoveZ(Chunks, new_chunks, ChunksToRemove, u, diff); } }

	//Chunks = new_chunks;
	//new_chunks.Clear();

	std::cout << "Moveed: " << ChunkMoved << '\n';
	std::cout << "Skipped: " << ChunkSkipped << '\n';

	Center = center;
	KnowBox = BoxI3(Center - (int)KnowSize, Center + (int)KnowSize);
	CareBox = BoxI3(Center - (int)CareSize, Center + (int)CareSize);

	ChunksToRemoveLock.AssignU();
	ChunksLock.AssignU();

	PutMissingCareChunks();
}



void ChunkContainer::ChunkNeighboutsFind(Chunk & chunk)
{
	for (int z = 0; z < 3; z++)
	{
		for (int y = 0; y < 3; y++)
		{
			for (int x = 0; x < 3; x++)
			{
				if (x != 1 || y != 1 || z != 1)
				{
					// use Referance to Pointer
						chunk.Neighbours.Cube[z][y][x] = FindAbsolutePointer(chunk.Index + VectorI3(x - 1, y - 1, z - 1));
					if (chunk.Neighbours.Cube[z][y][x] != nullptr)
					{
						chunk.Neighbours.Cube[z][y][x] -> Neighbours.Cube[2 - z][2 - y][2 - x] = &chunk;
					}
				}
			}
		}
	}
}
/*void ChunkManager::ChunkNeighboutsNull(Chunk & chunk)
{
	for (int z = 0; z < 3; z++)
	{
		for (int y = 0; y < 3; y++)
		{
			for (int x = 0; x < 3; x++)
			{
				if (x != 1 || y != 1 || z != 1)
				{
					// use Referance to Pointer
					if (chunk.Neighbours.Cube[z][y][x] != nullptr)
					{
						chunk.Neighbours.Cube[z][y][x] -> Neighbours.Cube[2 - z][2 - y][2 - x] = nullptr;
					}
						chunk.Neighbours.Cube[z][y][x] = nullptr;
				}
			}
		}
	}
}*/

void ChunkContainer::PutChunks(Container::Binary<VectorI3> & chunks)
{
	StopWatch sw;

	sw.Start();
	ChunksLock.AccessL();
	ChunksToInsertLock.AssignL();
	Manager.TimeInsertPut.WaitTime.NewValue(sw.ElapsedTime());

	sw.Clear();
	for (unsigned int i = 0; i < chunks.Count(); i++)
	{
		VectorU3 u = AbsoluteToRelative(chunks[i]);
		Chunk * chunk = new Chunk(chunks[i], Manager);
		Chunks[u] = chunk;
		ChunksToInsert.Insert(chunk);

		chunk -> Neighbours = ChunkNeighbour(chunk);
		ChunkNeighboutsFind(*chunk);
	}

	ChunksToInsertLock.AssignU();
	ChunksLock.AccessU();
	Manager.TimeInsertPut.DoTime.NewValue(sw.ElapsedTime());
}

/* const Lock
cannot be const because locking is not const
const means that Members of this Object arent changed
if the Member is a Pointer, then the Pointer cannot be changed
the Object tha the Pointer points to can be changed
so make the ChunkLock a Pointer ?
*/
Container::Binary<VectorI3> ChunkContainer::MissingCareChunks()
{
	StopWatch sw;
	Container::Binary<VectorI3> chunks;

	sw.Start();
	ChunksLock.AccessL();
	Manager.TimeInsertNew.WaitTime.NewValue(sw.ElapsedTime());

	sw.Clear();
	LoopI3 loop(CareBox.Min, Bool3(false), CareBox.Max, Bool3(false));
	for (VectorI3 i = loop.Min(); loop.Check(i).All(true); loop.Next(i))
	{
		VectorU3 u = AbsoluteToRelative(i);
		if (Chunks[u] != nullptr) { continue; }
		chunks.Insert(i);
	}

	ChunksLock.AccessU();
	Manager.TimeInsertNew.DoTime.NewValue(sw.ElapsedTime());

	return chunks;
}

void ChunkContainer::PutMissingCareChunks()
{
	StopWatch sw_total;
	sw_total.Start();

	Container::Binary<VectorI3> chunks = MissingCareChunks();
	PutChunks(chunks);

	std::cout << "Put " << chunks.Count() << " Missing Chunks\n";
	if (chunks.Count() != 0)
	{
		Manager.AuxThreadCollection.AuxThread2.FindLoop = CenterIndexLoop3D();
		Manager.AuxThreadCollection.AuxThread2.Poke();
	}

	Manager.TimeInsert.DoTime.NewValue(sw_total.ElapsedTime());
	Manager.TimeInsert.ThreadName = IdleLoopThread::ThreadName;
}

/* change Insert/Remove
	Insert
		find
			checks which ones need to be made
			adds them to a list
		wait
			only DrawThread can GraphicsCreate()
		done
			move from list to main list
	Remove
		find
			when moving around, some chunks go outside of range
			those get added to a list
		wait
			only DrawThread can GraphicsDelete()
		done
			delete

*/

// how to safely delete ?
void ChunkContainer::UpdateChunksContainer()
{
	StopWatch sw;

	//std::cout << "UpdateChunksContainer:" << __LINE__ << '\n';
	ChunksLock.AccessL(sw, Manager.TimeUpdate);
	//std::cout << "UpdateChunksContainer:" << __LINE__ << '\n';

	sw.Start();

	// Remove Chunks
	{
		StopWatch sw2;
		sw2.Start();
		ChunksToRemoveLock.AssignL();
		for (unsigned int i = 0; i < ChunksToRemove.Count(); i++)
		{
			Chunk * chunk = ChunksToRemove[i];
			if (chunk == nullptr) { ChunksToRemove.RemoveAt(i); i--; continue; }
			//if (chunk -> GraphicsExist) { continue; }
			if (chunk -> InUse()) { continue; }
			delete chunk;
			ChunksToRemove.RemoveAt(i);
			i--;
		}
		ChunksToRemoveLock.AssignU();
		sw2.Stop();
		Manager.TimeUpdateRemove.DoTime.NewValue(sw2.ElapsedTime());
	}

	// Insert Chunks
	{
		bool inserted = false;
		StopWatch sw2;
		ChunksToInsertLock.AssignL(sw2, Manager.TimeUpdateInsert);
		for (unsigned int i = 0; i < ChunksToInsert.Count(); i++)
		{
			Chunk * chunk = ChunksToInsert[i];
			if (chunk == nullptr) { continue; }
			VectorU3 u = AbsoluteToRelative(chunk -> Index);
			if ((u < Chunks.Size()).Any(false)) { continue; }
			//if (Chunks[u] != nullptr) { continue; }
			//Chunks[u] = chunk;

			inserted = true;
			ChunksToInsert.RemoveAt(i);
			i--;
		}
		ChunksToInsertLock.AssignU(sw2, Manager.TimeUpdateInsert);

		if (inserted)
		{
			Manager.AuxThreadCollection.AuxThread2.Poke();
			Manager.AuxThreadCollection.AuxThread3.Poke();
		}
	}

	//std::cout << "UpdateChunksContainer:" << __LINE__ << '\n';
	ChunksLock.AccessU(sw, Manager.TimeUpdate);
	//std::cout << "UpdateChunksContainer:" << __LINE__ << '\n';
}



#include "3D/VoxelHit.hpp"
#include "Axis/3D/Enums.hpp"
#include "Axis/3D/Funcs.hpp"
VoxelHit ChunkContainer::HitVoxel(RayF3 ray)
{
	//::ViewRayPolyHedra = ViewRayPolyHedra;
	//::VoxelBoxPolyHedra = VoxelBoxPolyHedra;
	//::ChunkBoxPolyHedra = ChunkBoxPolyHedra;
	//ShowRay(ray);

	//std::cout << "HitVoxel:" << __LINE__ << '\n';
	ChunksLock.AccessL();
	//std::cout << "HitVoxel:" << __LINE__ << '\n';
	GridCast3D::Hit _hit = VoxelHit::Hit(*this, ray, 10.0f);
	//std::cout << "HitVoxel:" << __LINE__ << '\n';
	ChunksLock.AccessU();
	//std::cout << "HitVoxel:" << __LINE__ << '\n';

	VoxelHit hit;
	//std::cout << "HitVoxel:" << __LINE__ << '\n';
	if (_hit.cardinal == Axis3D::Rel::None) { return hit; }
	//std::cout << "HitVoxel:" << __LINE__ << '\n';
	hit.Side = _hit.cardinal;
	hit.Index = _hit.idx;
	hit.Position = _hit.pos;
	hit.Normal = Axis3D::ToVector(_hit.cardinal);
	//std::cout << "HitVoxel:" << __LINE__ << '\n';

	return hit;
}
