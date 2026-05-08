#include "ChunkManager.hpp"
#include "Chunk.hpp"
#include "Voxel.hpp"
#include "VoxelOrientation.hpp"
#include "ChunkVoxelIndex.hpp"

#include "ValueType/Bool3.hpp"
#include "ValueType/BoxI3.hpp"
#include "ValueType/LoopI3.hpp"

#include "ValueType/Ray3D.hpp"

#include "GridCast/GridCast3D.hpp"



#include <iomanip>

// Code
#include "WaitDoTime.cpp"
#include "ContainerLock.cpp"

#include "ValueType/UndexLoop3D.hpp"



Chunk * ChunkManager::FindLockOrNull(VectorI3 idx)
{
	VectorU3 udx = relative(idx);
	if ((udx < Chunks.Size()).Any(false)) { return nullptr; }
	Chunk * chunk = Chunks[udx];
	if (chunk == nullptr) { return nullptr; }
	chunk -> lock();
	return chunk;
}
Chunk * ChunkManager::FindTryLockOrNull(VectorI3 idx)
{
	VectorU3 udx = relative(idx);
	if ((udx < Chunks.Size()).Any(false)) { return nullptr; }
	Chunk * chunk = Chunks[udx];
	if (chunk == nullptr) { return nullptr; }
	if (!chunk -> try_lock()) { return nullptr; }
	return chunk;
}

VectorI3 ChunkManager::absolute(VectorU3 u) const { return u + Corner; }
VectorU3 ChunkManager::relative(VectorI3 i) const { return i - Corner; }



void ChunkManager::ChangeChunksArraySize(unsigned int size)
{
	std::cout << "ChangeChunksArraySize:" << __LINE__ << '\n';
	ChunksLock.Changing0();
	std::cout << "ChangeChunksArraySize:" << __LINE__ << '\n';
	for (unsigned int i = 0; i < Chunks.Count(); i++)
	{
		Chunks[i] -> GraphicsDelete();
		delete Chunks[i];
	}
	std::cout << "ChangeChunksArraySize:" << __LINE__ << '\n';
	std::cout << "ChangeChunksArraySize:" << __LINE__ << '\n';
	Corner = Center - (int)size;
	std::cout << "ChangeChunksArraySize:" << __LINE__ << '\n';
	Chunks.ReSize(VectorU3((size * 2) + 1));
	std::cout << "ChangeChunksArraySize:" << __LINE__ << '\n';
	for (unsigned int i = 0; i < Chunks.Count(); i++)
	{
		Chunks[i] = nullptr;
	}
	std::cout << "ChangeChunksArraySize:" << __LINE__ << '\n';
	ChunksLock.Changing1();
	std::cout << "ChangeChunksArraySize:" << __LINE__ << '\n';
}

static VectorU3 ChunkSkipped;
static VectorU3 ChunkMoved;

void ChunkManager::ChangeCenterLoopX(VectorU3 u, VectorI3 diff)
{
	unsigned int udx0 = Chunks.Size().Convert(u);
	if (Chunks[udx0] != nullptr) { ChunksToRemove.Insert(Chunks[udx0]); }
	Chunks[udx0] = nullptr;

	if (((int)u.X) + diff.X < 0) { ChunkSkipped.X++; return; }
	if (((int)u.X) + diff.X >= (int)Chunks.Size().X) { ChunkSkipped.X++; return; }

	unsigned int udx1 = Chunks.Size().Convert(VectorU3(u.X + diff.X, u.Y, u.Z));
	Chunks[udx0] = Chunks[udx1];
	Chunks[udx1] = nullptr;
	ChunkMoved.X++;
}
void ChunkManager::ChangeCenterLoopY(VectorU3 u, VectorI3 diff)
{
	unsigned int udx0 = Chunks.Size().Convert(u);
	if (Chunks[udx0] != nullptr) { ChunksToRemove.Insert(Chunks[udx0]); }
	Chunks[udx0] = nullptr;

	if (((int)u.Y) + diff.Y < 0) { ChunkSkipped.Y++; return; }
	if (((int)u.Y) + diff.Y >= (int)Chunks.Size().Y) { ChunkSkipped.Y++; return; }

	unsigned int udx1 = Chunks.Size().Convert(VectorU3(u.X, u.Y + diff.Y, u.Z));
	Chunks[udx0] = Chunks[udx1];
	Chunks[udx1] = nullptr;
	ChunkMoved.Y++;
}
void ChunkManager::ChangeCenterLoopZ(VectorU3 u, VectorI3 diff)
{
	unsigned int udx0 = Chunks.Size().Convert(u);
	if (Chunks[udx0] != nullptr) { ChunksToRemove.Insert(Chunks[udx0]); }
	Chunks[udx0] = nullptr;

	if (((int)u.Z) + diff.Z < 0) { ChunkSkipped.Z++; return; }
	if (((int)u.Z) + diff.Z >= (int)Chunks.Size().Z) { ChunkSkipped.Z++; return; }

	unsigned int udx1 = Chunks.Size().Convert(VectorU3(u.X, u.Y, u.Z + diff.Z));
	Chunks[udx0] = Chunks[udx1];
	Chunks[udx1] = nullptr;
	ChunkMoved.Z++;
}
void ChunkManager::ChangeCenter(VectorI3 center)
{
	if ((Center == center).All(true)) { return; }

	ChunksLock.Changing0();
	ChunksToRemoveLock.Changing0();

	VectorI3 diff = center - Center;
	std::cout << "diff " << diff << '\n';

	ChunkSkipped = VectorU3(0);
	ChunkMoved = VectorU3(0);

	UndexLoop3D loop(VectorU3(), Chunks.Size());

	if (diff.X > 0) { for (VectorU3 u = loop.Min(); loop.Check(u).All(true); loop.Next(u)) { ChangeCenterLoopX(u, diff); } }
	if (diff.X < 0) { for (VectorU3 u = loop.Max(); loop.Check(u).All(true); loop.Prev(u)) { ChangeCenterLoopX(u, diff); } }

	if (diff.Y > 0) { for (VectorU3 u = loop.Min(); loop.Check(u).All(true); loop.Next(u)) { ChangeCenterLoopY(u, diff); } }
	if (diff.Y < 0) { for (VectorU3 u = loop.Max(); loop.Check(u).All(true); loop.Prev(u)) { ChangeCenterLoopY(u, diff); } }

	if (diff.Z > 0) { for (VectorU3 u = loop.Min(); loop.Check(u).All(true); loop.Next(u)) { ChangeCenterLoopZ(u, diff); } }
	if (diff.Z < 0) { for (VectorU3 u = loop.Max(); loop.Check(u).All(true); loop.Prev(u)) { ChangeCenterLoopZ(u, diff); } }

	std::cout << "Skip: " << ChunkSkipped << '\n';
	std::cout << "Move: " << ChunkMoved << '\n';
	
	Center = center;
	Corner += diff;

	ChunksToRemoveLock.Changing1();
	ChunksLock.Changing1();
}



ChunkManager::~ChunkManager()
{
	for (unsigned int i = 0; i < Chunks.Count(); i++)
	{
		delete Chunks[i];
	}
	/*for (unsigned int i = 0; i < ChunksArray.Count(); i++)
	{
		delete ChunksArray[i];
	}*/
}
ChunkManager::ChunkManager()
	: Shader()
//	, ChunksArray()
//	, ChunksBox()
	, Chunks()
	, ChunksLock()
//	, ChunksChanging()
//	, ChunksChecking()
//	, ChunksCheckingCount()
	, GraphicsExist(false)
{ }



#include <math.h>
#include "PolyHedra/Object.hpp"
static PolyHedra * ViewRayPolyHedra;
static PolyHedra * VoxelBoxPolyHedra;
//static PolyHedra * ChunkBoxPolyHedra;
static void ShowRay(Ray3D ray)
{
	if (ViewRayPolyHedra == nullptr) { return; }
	PolyHedraObject obj(ViewRayPolyHedra);
	obj.Trans().Position = ray.Pos;
	obj.Trans().Rotation = EulerAngle3D::PointToZ(ray.Dir);
}
static void ShowVoxel(VectorI3 idx)
{
	if (VoxelBoxPolyHedra == nullptr) { return; }
	PolyHedraObject obj(VoxelBoxPolyHedra);
	obj.Trans().Position = idx;
	obj.ShowWire();
}
/*static void ShowChunk(VectorI3 idx)
{
	PolyHedraObject obj(ChunkBoxPolyHedra);
	obj.Trans().Position = idx * CHUNK_VALUES_PER_SIDE;
	obj.ShowWire();
}*/

static GridCast3D::Hit hit_ray(Chunk & chunk, Ray3D ray3D, float limit)
{
	ShowRay(Ray3D(ray3D.Pos, ray3D.Dir));
	BoxI3 box(VectorI3(-1), VectorI3(CHUNK_VALUES_PER_SIDE));
	GridCast3D::Data data(ray3D, limit, 1.0f);
	do
	{
		ShowRay(data.Ray());
		ShowVoxel(data.Index());
		VectorI3 idx = data.Index() - (chunk.Index * CHUNK_VALUES_PER_SIDE);
		if (box.IntersectVecInclusive(idx).All(false)) { return GridCast3D::Hit(); }
		if (box.IntersectVecExclusive(idx).All(true))
		{
			if (chunk.Hit(idx)) { return GridCast3D::Hit(data); }
		}
	}
	while (data.Iterate());
	return GridCast3D::Hit();
}
static GridCast3D::Hit hit_ray(ChunkManager & manager, Ray3D ray3D, float limit)
{
	GridCast3D::Data data(ray3D, limit, CHUNK_VALUES_PER_SIDE);
	do
	{
		Chunk * chunk = manager.FindLockOrNull(data.Index());
		if (chunk == nullptr) { return GridCast3D::Hit(); }
		if (!(chunk -> Done())) { chunk -> unlock(); return GridCast3D::Hit(); }
		if ((chunk -> IsEmpty())) { chunk -> unlock(); continue; }
		GridCast3D::Hit hit = hit_ray(*chunk, data.Ray(), data.Limit());
		chunk -> unlock();
		if (hit.cardinal != AxisRel::None) { return hit; }
	}
	while (data.Iterate());
	return GridCast3D::Hit();
}

bool VoxelHit::Valid() const { return Side != AxisRel::None; }
VoxelHit::VoxelHit()
	: Side(AxisRel::None)
{ }

VoxelHit ChunkManager::HitVoxel(Ray3D ray)
{
	::ViewRayPolyHedra = ViewRayPolyHedra;
	::VoxelBoxPolyHedra = VoxelBoxPolyHedra;
	//::ChunkBoxPolyHedra = ChunkBoxPolyHedra;
	//ShowRay(ray);
//	std::cout << "HitVoxel:" << __LINE__ << '\n';
	ChunksLock.Checking0();
//	std::cout << "HitVoxel:" << __LINE__ << '\n';
	GridCast3D::Hit _hit = hit_ray(*this, ray, 10.0f);
//	std::cout << "HitVoxel:" << __LINE__ << '\n';
	ChunksLock.Checking1();
//	std::cout << "HitVoxel:" << __LINE__ << '\n';
	VoxelHit hit;
//	std::cout << "HitVoxel:" << __LINE__ << '\n';
	if (_hit.cardinal == AxisRel::None) { return hit; }
//	std::cout << "HitVoxel:" << __LINE__ << '\n';
	hit.Position = _hit.pos;
	switch (_hit.cardinal)
	{
		case AxisRel::PrevX: hit.Normal = VectorF3(-1, 0, 0); break;
		case AxisRel::PrevY: hit.Normal = VectorF3(0, -1, 0); break;
		case AxisRel::PrevZ: hit.Normal = VectorF3(0, 0, -1); break;
		case AxisRel::NextX: hit.Normal = VectorF3(+1, 0, 0); break;
		case AxisRel::NextY: hit.Normal = VectorF3(0, +1, 0); break;
		case AxisRel::NextZ: hit.Normal = VectorF3(0, 0, +1); break;
		default: hit.Normal = VectorF3(0, 0, 0); break;
	}
	hit.Side = _hit.cardinal;
	hit.Index = _hit.idx;
//	std::cout << "HitVoxel:" << __LINE__ << '\n';
	return hit;
}



WaitDoTime	ChunkManager::TimeInsert;
WaitDoTime	ChunkManager::TimeInsertNeighbours;

WaitDoTime	ChunkManager::TimeRemove;

WaitDoTime	ChunkManager::TimeUpdate;
WaitDoTime	ChunkManager::TimeUpdateInsert;
WaitDoTime	ChunkManager::TimeUpdateChange;
WaitDoTime	ChunkManager::TimeUpdateRemove;

WaitDoTime	ChunkManager::TimeGenerate;
WaitDoTime	ChunkManager::TimeGraphics;

WaitDoTime	ChunkManager::TimeGraphicsCreate;
WaitDoTime	ChunkManager::TimeGraphicsDelete;
WaitDoTime	ChunkManager::TimeDraw;



void ChunkManager::Clear()
{ }

/* Inserting
	Find Chunks that need inserting
	new in ChunksToInsert
	{
		Find Neighbours
		Create Graphics
	}
	move from ChunksToInsert to Chunks
*/

/* Removing
	Find Chunks that need removeing
	move from Chunks to ChunksToRemove
	{
		Null Neighbours
		Delete Graphics
	}
	delete from ChunksToRemove
*/

/* Find Neighbours is slow
	it needs to look through all Chunks for each Neighbourhood to Find
	if the centra Chunks were stored in a 3D Array with it might be easier
	Insert around already makes one of those
	use that ?
	what about the ones not in the Neighbourhood ?
	store the Remove Neighbourhood
	Insert Neighbourhood is a part of that
	everything outside should be moved to ChunksToRemove

	for now just have a Limit for how many Neighbours should be found
	also dont try to find Neighbours that are already found ?

	maybe remember the index where it ended and continue there ?
*/

void ChunkManager::InsertAround(VectorF3 pos, unsigned int size)
{
	VectorI3 chunk_idx((pos / (float)CHUNK_VALUES_PER_SIDE).roundF());

	BoxI3 box(chunk_idx - (int)size, chunk_idx + (int)size);
	VectorI3 box_size = box.Size() + 1;

	Chunk ** arr = new Chunk*[box_size.Product()]; // keep this allocated ?
	for (int i = 0; i < box_size.Product(); i++)
	{
		arr[i] = nullptr;
	}

	StopWatch sw;

//	std::cout << "InsertAround:" << __LINE__ << '\n';
	ChunksLock.Checking0();
	for (unsigned int i = 0; i < Chunks.Count(); i++)
	{
		if (Chunks[i] == nullptr) { continue; }
		Chunk & chunk = *Chunks[i];
		if (box.IntersectVecInclusive(chunk.Index).All(true))
		{
			unsigned int j = box_size.Convert(chunk.Index - box.Min);
			arr[j] = &chunk;
		}
	}
	ChunksLock.Checking1();
//	std::cout << "InsertAround:" << __LINE__ << '\n';
	ChunksToInsertLock.Checking0();
	for (unsigned int i = 0; i < ChunksToInsert.Count(); i++)
	{
		if (ChunksToInsert[i] == nullptr) { continue; }
		Chunk & chunk = *ChunksToInsert[i];
		if (box.IntersectVecInclusive(chunk.Index).All(true))
		{
			unsigned int j = box_size.Convert(chunk.Index - box.Min);
			arr[j] = &chunk;
		}
	}
	ChunksToInsertLock.Checking1();
//	std::cout << "InsertAround:" << __LINE__ << '\n';
	ChunksToInsertLock.Changing0();
	LoopI3 loop(box.Min, Bool3(false), box.Max, Bool3(false));
	for (VectorI3 i = loop.Min(); loop.Check(i).All(true); loop.Next(i))
	{
		unsigned int j = box_size.Convert(i - box.Min);
		if (arr[j] == nullptr)
		{
			ChunksToInsert.Insert(new Chunk(i));
		}
	}
	ChunksToInsertLock.Changing1();
//	std::cout << "InsertAround:" << __LINE__ << '\n';
	delete[] arr;
//	std::cout << "InsertAround:" << __LINE__ << '\n';
}
void ChunkManager::RemoveAround(VectorF3 pos, unsigned int size)
{
	StopWatch sw;
	sw.Start();
//	std::cout << "RemoveAround:" << __LINE__ << '\n';
	ChunksLock.Changing0();
//	std::cout << "RemoveAround:" << __LINE__ << '\n';
	ChunksToRemoveLock.Changing0();
//	std::cout << "RemoveAround:" << __LINE__ << '\n';
	sw.Stop();
	TimeRemove.WaitTime.NewValue(sw.ElapsedTime());

	sw.Start();

	VectorI3 chunk_idx((pos / (float)CHUNK_VALUES_PER_SIDE).roundF());
	BoxI3 chunk_box(chunk_idx - (int)size, chunk_idx + (int)size);

//	std::cout << "RemoveAround:" << __LINE__ << '\n';
	for (unsigned int i = 0; i < Chunks.Count(); i++)
	{
		Chunk * chunk = Chunks[i];
		if (chunk == nullptr) { continue; }
		if (chunk_box.IntersectVecInclusive(chunk -> Index).All(true)) { continue; }

		Chunks[i] = nullptr;
		ChunksToRemove.Insert(chunk);
	}
//	std::cout << "RemoveAround:" << __LINE__ << '\n';
	ChunksToRemoveLock.Changing1();
//	std::cout << "RemoveAround:" << __LINE__ << '\n';
	ChunksLock.Changing1();
//	std::cout << "RemoveAround:" << __LINE__ << '\n';
	sw.Stop();
	TimeRemove.DoTime.NewValue(sw.ElapsedTime());
}

void ChunkManager::FindNeighbours(unsigned int & idx)
{
	StopWatch sw;
//	std::cout << "FindNeighbours:" << __LINE__ << '\n';
	ChunksToInsertLock.Checking0(sw, TimeInsertNeighbours);
//	std::cout << "FindNeighbours:" << __LINE__ << '\n';
	for (unsigned int i = 0; i < ChunksToInsert.Count(); i++, idx++)
	{
		if (idx >= ChunksToInsert.Count()) { idx = 0; }
		if (ChunksToInsert[idx] == nullptr) { continue; }
		if (ChunksToInsert[idx] -> Neighbours.Done()) { continue; }
		FindNeighbours(*ChunksToInsert[idx]);
		break;
	}
	idx++;
//	std::cout << "FindNeighbours:" << __LINE__ << '\n';
	ChunksToInsertLock.Checking1(sw, TimeInsertNeighbours);
//	std::cout << "FindNeighbours:" << __LINE__ << '\n';
}
void ChunkManager::NullNeighbours(unsigned int & idx)
{
	//StopWatch sw;
//	std::cout << "NullNeighbours:" << __LINE__ << '\n';
	ChunksToRemoveLock.Checking0();
//	std::cout << "NullNeighbours:" << __LINE__ << '\n';
	for (unsigned int i = 0; i < ChunksToRemove.Count(); i++, idx++)
	{
		if (idx >= ChunksToRemove.Count()) { idx = 0; }
		if (ChunksToRemove[idx] == nullptr) { continue; }
		if (!ChunksToRemove[idx] -> Neighbours.Done()) { continue; }
		NullNeighbours(*ChunksToRemove[idx]);
		break;
	}
	idx++;
//	std::cout << "NullNeighbours:" << __LINE__ << '\n';
	ChunksToRemoveLock.Checking1();
//	std::cout << "NullNeighbours:" << __LINE__ << '\n';
}

void ChunkManager::FindNeighbours(Chunk & chunk)
{
	VectorI3 iNextX = chunk.Index + VectorI3(+1,  0,  0);
	VectorI3 iNextY = chunk.Index + VectorI3( 0, +1,  0);
	VectorI3 iNextZ = chunk.Index + VectorI3( 0,  0, +1);
	VectorI3 iPrevX = chunk.Index + VectorI3(-1,  0,  0);
	VectorI3 iPrevY = chunk.Index + VectorI3( 0, -1,  0);
	VectorI3 iPrevZ = chunk.Index + VectorI3( 0,  0, -1);
	for (unsigned int i = 0; i < Chunks.Count(); i++)
	{
		if (Chunks[i] == nullptr) { continue; }
		if ((Chunks[i] -> Index == iNextX).All(true)) { chunk.Neighbours.Change(AxisRel::NextX, Chunks[i]); }
		if ((Chunks[i] -> Index == iNextY).All(true)) { chunk.Neighbours.Change(AxisRel::NextY, Chunks[i]); }
		if ((Chunks[i] -> Index == iNextZ).All(true)) { chunk.Neighbours.Change(AxisRel::NextZ, Chunks[i]); }
		if ((Chunks[i] -> Index == iPrevX).All(true)) { chunk.Neighbours.Change(AxisRel::PrevX, Chunks[i]); }
		if ((Chunks[i] -> Index == iPrevY).All(true)) { chunk.Neighbours.Change(AxisRel::PrevY, Chunks[i]); }
		if ((Chunks[i] -> Index == iPrevZ).All(true)) { chunk.Neighbours.Change(AxisRel::PrevZ, Chunks[i]); }
	}
	for (unsigned int i = 0; i < ChunksToInsert.Count(); i++)
	{
		if (ChunksToInsert[i] == nullptr) { continue; }
		if ((ChunksToInsert[i] -> Index == iNextX).All(true)) { chunk.Neighbours.Change(AxisRel::NextX, ChunksToInsert[i]); }
		if ((ChunksToInsert[i] -> Index == iNextY).All(true)) { chunk.Neighbours.Change(AxisRel::NextY, ChunksToInsert[i]); }
		if ((ChunksToInsert[i] -> Index == iNextZ).All(true)) { chunk.Neighbours.Change(AxisRel::NextZ, ChunksToInsert[i]); }
		if ((ChunksToInsert[i] -> Index == iPrevX).All(true)) { chunk.Neighbours.Change(AxisRel::PrevX, ChunksToInsert[i]); }
		if ((ChunksToInsert[i] -> Index == iPrevY).All(true)) { chunk.Neighbours.Change(AxisRel::PrevY, ChunksToInsert[i]); }
		if ((ChunksToInsert[i] -> Index == iPrevZ).All(true)) { chunk.Neighbours.Change(AxisRel::PrevZ, ChunksToInsert[i]); }
	}
	chunk.Neighbours.Change(AxisRel::Here, &chunk);
}
void ChunkManager::NullNeighbours(Chunk & chunk)
{
	chunk.Neighbours.Change(AxisRel::Here, nullptr);
}

void ChunkManager::UpdateChunksContainer()
{
	StopWatch sw;
//	std::cout << "UpdateChunksContainer:" << __LINE__ << '\n';
	ChunksLock.Changing0(sw, TimeUpdate);
//	std::cout << "UpdateChunksContainer:" << __LINE__ << '\n';

	sw.Start();

	// Remove Chunks
	{
		StopWatch sw2;
		sw2.Start();
		ChunksToRemoveLock.Changing0();
		for (unsigned int i = 0; i < ChunksToRemove.Count(); i++)
		{
			Chunk * chunk = ChunksToRemove[i];
			if (chunk == nullptr) { ChunksToRemove.Remove(i); i--; continue; }
			if (chunk -> GraphicsExist) { continue; }
			if (chunk -> Neighbours.Done()) { continue; }
			chunk -> lock();
			chunk -> unlock();
			delete chunk;
			ChunksToRemove.Remove(i);
			i--;
		}
		ChunksToRemoveLock.Changing1();
		sw2.Stop();
		TimeUpdateRemove.DoTime.NewValue(sw2.ElapsedTime());
	}

	{
		StopWatch sw2;
		sw2.Start();
		unsigned int null_count = 0;
		for (unsigned int i = 0; i < Chunks.Count(); i++)
		{
			if (Chunks[i] == nullptr) { null_count++; }
		}

		/*if (null_count > ChunksToInsert.Count())
		{
			unsigned int null_remove = null_count - ChunksToInsert.Count();
			for (unsigned int i = 0; i < Chunks.Count() && null_remove > 0; i++)
			{
				if (Chunks[i] != nullptr) { continue; }
				Chunks.Remove(i);
				i--;
				null_remove--;
			}
		}*/
		/*if (null_count < ChunksToInsert.Count())
		{
			unsigned int null_insert = ChunksToInsert.Count() - null_count;
			for (unsigned int i = 0; i < null_insert; i++)
			{
				Chunks.Insert(nullptr);
			}
		}*/

		/*for (unsigned int i = 0; i < Chunks.Count(); i++)
		{
			if (Chunks[i] != nullptr) { continue; }
			Chunks.Remove(i);
			i--;
		}*/
		sw2.Stop();
		TimeUpdateChange.DoTime.NewValue(sw2.ElapsedTime());
	}

	// Insert Chunks
	{
		StopWatch sw2;
		ChunksToInsertLock.Changing0(sw2, TimeUpdateInsert);
		for (unsigned int i = 0; i < ChunksToInsert.Count(); i++)
		{
			Chunk * chunk = ChunksToInsert[i];
			if (chunk == nullptr) { continue; }
			if (!(chunk -> GraphicsExist)) { continue; }
			if (!(chunk -> Neighbours.Done())) { continue; }
			VectorU3 u = relative(chunk -> Index);
			if ((u < Chunks.Size()).Any(false)) { continue; }
			if (Chunks[u] != nullptr) { continue; }
			Chunks[u] = chunk;
			ChunksToInsert.Remove(i);
			i--;
		}
		/*unsigned int j = 0;
		for (unsigned i = 0; i < ChunksToInsert.Count(); i++)
		{
			Chunk * chunk = ChunksToInsert[i];
			if (chunk == nullptr) { continue; }
			if (!(chunk -> GraphicsExist)) { continue; }
			if (!(chunk -> Neighbours.Done())) { continue; }
			for (; j < Chunks.Count(); j++)
			{
				if (Chunks[j] == nullptr) { break; }
			}
			if (j < Chunks.Count())
			{
				Chunks[j] = chunk;
				ChunksToInsert.Remove(i);
				i--;
			}
		}*/
		ChunksToInsertLock.Changing1(sw2, TimeUpdateInsert);
	}

//	std::cout << "UpdateChunksContainer:" << __LINE__ << '\n';
	ChunksLock.Changing1(sw, TimeUpdate);
//	std::cout << "UpdateChunksContainer:" << __LINE__ << '\n';
}



Chunk * ChunkManager::FindGenerateChunk(VectorF3 pos, unsigned int size)
{
	StopWatch sw;
//	std::cout << "FindGenerateChunk:" << __LINE__ << '\n';
	ChunksLock.Checking0(sw, TimeGenerate);
//	std::cout << "FindGenerateChunk:" << __LINE__ << '\n';

	VectorI3 chunk_idx((pos / (float)CHUNK_VALUES_PER_SIDE).roundF());
	BoxI3 chunk_box(chunk_idx - (int)size, chunk_idx + (int)size);

	Chunk * found = nullptr;
	float dist;
	for (unsigned int i = 0; i < Chunks.Count(); i++)
	{
		if (Chunks[i] == nullptr)
		{ continue; }

		Chunk & chunk = *Chunks[i];

//		std::cout << "FindGenerateChunk:" << __LINE__ << '\n';
		chunk.lock();
//		std::cout << "FindGenerateChunk:" << __LINE__ << '\n';
		//if (!chunk.try_lock())
		//{ continue; }

		if (chunk.Done())
		{ chunk.unlock(); continue; }

		if (!chunk_box.IntersectVecInclusive(chunk.Index).All(true))
		{ chunk.unlock(); continue; }

		VectorF3 rel = ((chunk.Index + VectorF3(0.5f)) * CHUNK_VALUES_PER_SIDE) - pos;
		float d = rel.length2();
		if (found == nullptr || d < dist)
		{
			if (found != nullptr) { found -> unlock(); }
			found = &chunk;
			dist = d;
		}
		else { chunk.unlock(); }
	}

//	std::cout << "FindGenerateChunk:" << __LINE__ << '\n';
	ChunksLock.Checking1(sw, TimeGenerate);
//	std::cout << "FindGenerateChunk:" << __LINE__ << '\n';

	return found;
}
void ChunkManager::GenerateAround(VectorF3 pos, unsigned int size, const Perlin2D & noise2, const Perlin3D & noise3)
{
	//for (unsigned int c = 0; c < count; c++)
	{
//		std::cout << "GenerateAround:" << __LINE__ << '\n';
		Chunk * chunk = FindGenerateChunk(pos, size);
//		std::cout << "GenerateAround:" << __LINE__ << '\n';
		//if (chunk == nullptr) { break; }
		if (chunk == nullptr) { return; }
//		std::cout << "GenerateAround:" << __LINE__ << '\n';
		chunk -> Generate(noise2, noise3);
		chunk -> Neighbours.UpdateBufferMain();
		chunk -> unlock();
	}
}





void ChunkManager::GraphicsCreate()
{
	if (GraphicsExist) { return; }

	Shader.Create();
	Texture.Create();

//	std::cout << "GraphicsCreate:" << __LINE__ << '\n';
	ChunksLock.Checking0();
//	std::cout << "GraphicsCreate:" << __LINE__ << '\n';
	for (unsigned int i = 0; i < Chunks.Count(); i++)
	{
		if (Chunks[i] == nullptr) { continue; }
		Chunks[i] -> GraphicsCreate();
	}
//	std::cout << "GraphicsCreate:" << __LINE__ << '\n';
	ChunksLock.Checking1();
//	std::cout << "GraphicsCreate:" << __LINE__ << '\n';

	GraphicsExist = true;
}
void ChunkManager::GraphicsDelete()
{
	if (!GraphicsExist) { return; }

	Shader.Delete();
	Texture.Delete();

//	std::cout << "GraphicsDelete:" << __LINE__ << '\n';
	ChunksLock.Checking0();
//	std::cout << "GraphicsDelete:" << __LINE__ << '\n';
	for (unsigned int i = 0; i < Chunks.Count(); i++)
	{
		if (Chunks[i] == nullptr) { continue; }
		Chunks[i] -> GraphicsDelete();
	}
//	std::cout << "GraphicsDelete:" << __LINE__ << '\n';
	ChunksLock.Checking1();
//	std::cout << "GraphicsDelete:" << __LINE__ << '\n';

	GraphicsExist = false;
}
void ChunkManager::GraphicsUpdate()
{
	if (!GraphicsExist) { return; }

	// lock Chunks ?

//	std::cout << "GraphicsUpdate:" << __LINE__ << '\n';
	{
		StopWatch sw;
		ChunksToRemoveLock.Checking0(sw, TimeGraphicsDelete);
//		std::cout << "GraphicsUpdate:" << __LINE__ << '\n';
		for (unsigned int i = 0; i < ChunksToRemove.Count(); i++)
		{
			Chunk * chunk = ChunksToRemove[i];
			if (chunk == nullptr) { continue; }
			chunk -> GraphicsDelete();
		}
//		std::cout << "GraphicsUpdate:" << __LINE__ << '\n';
		ChunksToRemoveLock.Checking1(sw, TimeGraphicsDelete);
	}
//	std::cout << "GraphicsUpdate:" << __LINE__ << '\n';
	{
		StopWatch sw;
		ChunksToInsertLock.Checking0(sw, TimeGraphicsCreate);
//		std::cout << "GraphicsUpdate:" << __LINE__ << '\n';
		for (unsigned int i = 0; i < ChunksToInsert.Count(); i++)
		{
			Chunk * chunk = ChunksToInsert[i];
			if (chunk == nullptr) { continue; }
			chunk -> GraphicsCreate();
		}
//		std::cout << "GraphicsUpdate:" << __LINE__ << '\n';
		ChunksToInsertLock.Checking1(sw, TimeGraphicsCreate);
	}
//	std::cout << "GraphicsUpdate:" << __LINE__ << '\n';
}



Chunk * ChunkManager::FindGraphicsUpdateChunk(VectorF3 pos)
{
	StopWatch sw;
//	std::cout << "FindGraphicsUpdateChunk:" << __LINE__ << '\n';
	ChunksLock.Checking0(sw, TimeGraphics);
//	std::cout << "FindGraphicsUpdateChunk:" << __LINE__ << '\n';

	Chunk * found = nullptr;
	float dist;
	for (unsigned int i = 0; i < Chunks.Count(); i++)
	{
		if (Chunks[i] == nullptr) { continue; }
		Chunk & chunk = *Chunks[i];

//		std::cout << "FindGraphicsUpdateChunk:" << __LINE__ << '\n';
		chunk.lock();
//		std::cout << "FindGraphicsUpdateChunk:" << __LINE__ << '\n';
		//if (!chunk.try_lock())
		//{ continue; }

		if (!chunk.Done())
		{ chunk.unlock(); continue; }

		if (chunk.MainBufferState != BufferDataState::Needed)
		{ chunk.unlock(); continue; }

		VectorF3 rel = ((chunk.Index + VectorF3(0.5f)) * CHUNK_VALUES_PER_SIDE) - pos;
		float d = rel.length2();
		if (found == nullptr || d < dist)
		{
			if (found != nullptr) { found -> unlock(); }
			found = &chunk;
			dist = d;
		}
		else { chunk.unlock(); }
	}

//	std::cout << "FindGraphicsUpdateChunk:" << __LINE__ << '\n';
	ChunksLock.Checking1(sw, TimeGraphics);
//	std::cout << "FindGraphicsUpdateChunk:" << __LINE__ << '\n';

	return found;
}
void ChunkManager::GraphicsUpdateDataAround(VectorF3 pos)
{
	//for (unsigned int c = 0; c < count; c++)
	{
		//std::cout << "GraphicsUpdateDataAround:" << __LINE__ << '\n';
		Chunk * chunk = FindGraphicsUpdateChunk(pos);
		//std::cout << "GraphicsUpdateDataAround:" << __LINE__ << '\n';
		//if (chunk == nullptr) { break; }
		if (chunk == nullptr) { return; }
		//std::cout << "GraphicsUpdateDataAround:" << __LINE__ << '\n';
		chunk -> GraphicsUpdateMainData();
		chunk -> unlock();
	}
}

void ChunkManager::Draw()
{
	if (!GraphicsExist) { return; }

	StopWatch sw;
//	std::cout << "Draw:" << __LINE__ << '\n';
	ChunksLock.Checking0(sw, TimeDraw);
//	std::cout << "Draw:" << __LINE__ << '\n';

	Shader.Bind();
	Texture.Bind();
	for (unsigned int i = 0; i < Chunks.Count(); i++)
	{
		if (Chunks[i] == nullptr) { continue; }
		Chunks[i] -> Draw();
	}

//	std::cout << "Draw:" << __LINE__ << '\n';
	ChunksLock.Checking1(sw, TimeDraw);
//	std::cout << "Draw:" << __LINE__ << '\n';
}
