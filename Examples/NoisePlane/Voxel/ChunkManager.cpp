#include "ChunkManager.hpp"
#include "Chunk.hpp"
#include "Voxel.hpp"
#include "VoxelOrientation.hpp"
#include "VoxelIndex.hpp"

#include "ValueType/Bool3.hpp"
#include "ValueType/BoxI3.hpp"
#include "ValueType/LoopI3.hpp"

#include "ValueType/Ray3D.hpp"

#include "GridCast/GridCast3D.hpp"



#include <iomanip>
WaitDoTime::WaitDoTime()
	: DoTime(64)
	, WaitTime(64)
{ }
std::ostream & operator<<(std::ostream & o, const WaitDoTime & obj)
{
	o << '{';
	o << std::fixed << std::setw(5) << std::setfill(' ') << std::setprecision(4) << obj.WaitTime.Min() << 's';
	o << ' ';
	o << std::fixed << std::setw(5) << std::setfill(' ') << std::setprecision(4) << obj.WaitTime.Average() << 's';
	o << ' ';
	o << std::fixed << std::setw(5) << std::setfill(' ') << std::setprecision(4) << obj.WaitTime.Max() << 's';
	o << '|';
	o << std::fixed << std::setw(5) << std::setfill(' ') << std::setprecision(4) << obj.DoTime.Min() << 's';
	o << ' ';
	o << std::fixed << std::setw(5) << std::setfill(' ') << std::setprecision(4) << obj.DoTime.Average() << 's';
	o << ' ';
	o << std::fixed << std::setw(5) << std::setfill(' ') << std::setprecision(4) << obj.DoTime.Max() << 's';
	o << '}';
	return o;
}



void ContainerLock::Checking0()
{
	Checking.lock();
	CheckingCount++;
	Checking.unlock();
}
void ContainerLock::Checking1()
{
	CheckingCount--;
}
void ContainerLock::Changing0()
{
	Changing.lock();
	Checking.lock();
	while (CheckingCount.load() != 0) { }
}
void ContainerLock::Changing1()
{
	Checking.unlock();
	Changing.unlock();
}

void ContainerLock::Checking0(StopWatch & watch, WaitDoTime & time)
{
	watch.ReStart();

	Checking.lock();
	CheckingCount++;
	Checking.unlock();

	watch.Stop();
	time.WaitTime.NewValue(watch.ElapsedTime());
	watch.ReStart();
}
void ContainerLock::Checking1(StopWatch & watch, WaitDoTime & time)
{
	CheckingCount--;

	watch.Stop();
	time.DoTime.NewValue(watch.ElapsedTime());
}
void ContainerLock::Changing0(StopWatch & watch, WaitDoTime & time)
{
	watch.ReStart();

	Changing.lock();
	Checking.lock();
	while (CheckingCount.load() != 0) { }

	watch.Stop();
	time.WaitTime.NewValue(watch.ElapsedTime());
	watch.ReStart();
}
void ContainerLock::Changing1(StopWatch & watch, WaitDoTime & time)
{
	Checking.unlock();
	Changing.unlock();

	watch.Stop();
	time.DoTime.NewValue(watch.ElapsedTime());
}



ChunkManager::~ChunkManager() { }
ChunkManager::ChunkManager()
	: Shader()
	, Chunks()
	, ChunksLock()
//	, ChunksChanging()
//	, ChunksChecking()
//	, ChunksCheckingCount()
	, GraphicsExist(false)
{ }



// treat Delete like null ?
// make a Function to check that ?
/*static bool Valid(const Chunk * chunk)
{
	if (chunk == nullptr) { return false; }
	if (chunk -> Delete) { return false; }
	return true;
}*/

unsigned int ChunkManager::FindChunkUndex(Chunk * chunk)
{
//	ChunksChecking.lock();
//	ChunksCheckingCount++;
//	ChunksChecking.unlock();
	std::cout << "FindChunkUndex:" << __LINE__ << '\n';
	ChunksLock.Checking0();
	for (unsigned int i = 0; i < Chunks.Count(); i++)
	{
		if (Chunks[i] == chunk)
		{
			ChunksLock.Checking1();
			//ChunksCheckingCount--;
			return i;
		}
	}
	ChunksLock.Checking1();
//	ChunksCheckingCount--;
	return 0xFFFFFFFF;
}
unsigned int ChunkManager::FindChunkUndex(VectorI3 idx)
{
//	ChunksChecking.lock();
//	ChunksCheckingCount++;
//	ChunksChecking.unlock();
	std::cout << "FindChunkUndex:" << __LINE__ << '\n';
	ChunksLock.Checking0();
	for (unsigned int i = 0; i < Chunks.Count(); i++)
	{
		if (((*Chunks[i]).Index == idx).All(true))
		{
			ChunksLock.Checking1();
			//ChunksCheckingCount--;
			return i;
		}
	}
	ChunksLock.Checking1();
//	ChunksCheckingCount--;
	return 0xFFFFFFFF;
}
Chunk * ChunkManager::FindChunkOrNull(VectorI3 idx)
{
//	ChunksChecking.lock();
//	ChunksCheckingCount++;
//	ChunksChecking.unlock();
	std::cout << "FindChunkOrNull:" << __LINE__ << '\n';
	ChunksLock.Checking0();
	for (unsigned int i = 0; i < Chunks.Count(); i++)
	{
		if (((*Chunks[i]).Index == idx).All(true))
		{
			ChunksLock.Checking1();
			//ChunksCheckingCount--;
			return Chunks[i];
		}
	}
	ChunksLock.Checking1();
//	ChunksCheckingCount--;
	return nullptr;
}

VoxelIndex ChunkManager::FindVoxelIndex(VoxelIndex idx)
{
	idx.ChunkMan = FindChunkUndex(idx.Chunk);
	return idx;
}
VoxelIndex ChunkManager::FindVoxelIndex(VectorI3 idx)
{
	return FindVoxelIndex(VoxelIndex(idx));
}

const Voxel * ChunkManager::FindVoxelOrNull(VoxelIndex idx)
{
	if (!idx.Valid()) { return nullptr; }
	Chunk * chunk = Chunks[idx.ChunkMan];
	if (chunk == nullptr)   {  return nullptr; }
	if (!(chunk -> Done())) {  return nullptr; }
	if (chunk -> IsEmpty()) {  return nullptr; }
	return nullptr;
//	return &(*chunk)[idx.Voxel];
}
const Voxel * ChunkManager::FindVoxelOrNull(VectorI3 idx)
{
	return FindVoxelOrNull(FindVoxelIndex(idx));
}



//#include <math.h>
//#include "PolyHedra/Object.hpp"
//static PolyHedra *	ViewRayPolyHedra;
//static PolyHedra *	VoxelBoxPolyHedra;
//static PolyHedra *	ChunkBoxPolyHedra;
/*static void ShowRay(Ray3D ray)
{
	if (ViewRayPolyHedra == nullptr) { return; }
	PolyHedraObject obj(ViewRayPolyHedra);
	obj.Trans().Position = ray.Pos;
	obj.Trans().Rotation = EulerAngle3D::PointToZ(ray.Dir);
}*/
/*static void ShowVoxel(VectorI3 idx)
{
	if (VoxelBoxPolyHedra == nullptr) { return; }
	PolyHedraObject obj(VoxelBoxPolyHedra);
	obj.Trans().Position = idx;
	obj.ShowWire();
}*/
/*static void ShowChunk(VectorI3 idx)
{
	PolyHedraObject obj(ChunkBoxPolyHedra);
	obj.Trans().Position = idx * CHUNK_VALUES_PER_SIDE;
	obj.ShowWire();
}*/

/*static GridCast3D::Hit hit_ray(const Chunk & chunk, Ray3D ray3D, float limit)
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
}*/
/*static GridCast3D::Hit hit_ray(const ChunkManager & manager, Ray3D ray3D, float limit)
{
	GridCast3D::Data data(ray3D, limit, CHUNK_VALUES_PER_SIDE);
	do
	{
		Chunk * chunk = manager.FindChunkOrNull(data.Index());
		if (chunk == nullptr) { return GridCast3D::Hit(); }
		if (!(chunk -> Done())) { return GridCast3D::Hit(); }
		if (!(chunk -> IsEmpty()))
		{
			GridCast3D::Hit hit = hit_ray(*chunk, data.Ray(), data.Limit());
			if (hit.cardinal != AxisRel::None) { return hit; }
		}
	}
	while (data.Iterate());
	return GridCast3D::Hit();
}*/

bool VoxelHit::Valid() const { return Side != AxisRel::None; }
VoxelHit::VoxelHit()
	: Side(AxisRel::None)
{ }

VoxelHit ChunkManager::HitVoxel(Ray3D ray) const
{
	return VoxelHit();

//	::ViewRayPolyHedra = ViewRayPolyHedra;
//	::VoxelBoxPolyHedra = VoxelBoxPolyHedra;
//	::ChunkBoxPolyHedra = ChunkBoxPolyHedra;

	//ShowRay(ray);
//	GridCast3D::Hit _hit = hit_ray(*this, ray, 10.0f);
	GridCast3D::Hit _hit; (void)ray;

	VoxelHit hit;
	if (_hit.cardinal == AxisRel::None) { return hit; }

	//hit.Position = ray.Pos + (ray.Dir * _hit.dist);
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
	return hit;
}



bool ChunkManager::ClearVoxel(VoxelIndex idx, Voxel & vox)
{
	return false;
	if (!idx.Valid()) { return false; }
	return Chunks[idx.ChunkMan] -> ClearVoxel(idx.Voxel, vox);
}
bool ChunkManager::ClearVoxel(VectorI3 idx, Voxel & vox)
{
	return ClearVoxel(FindVoxelIndex(idx), vox);
}

bool ChunkManager::PlaceVoxel(VoxelIndex idx, Voxel & vox)
{
	return false;
	if (!idx.Valid()) { return false; }
	return Chunks[idx.ChunkMan] -> PlaceVoxel(idx.Voxel, vox);
}
bool ChunkManager::PlaceVoxel(VectorI3 idx, Voxel & vox)
{
	return PlaceVoxel(FindVoxelIndex(idx), vox);
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
{
	//ChunksChanging.lock();

	// move all chunks to the ToRemove List ?

	/*for (unsigned int i = 0; i < Chunks.Count(); i++)
	{
		delete Chunks[i];
	}
	Chunks.Clear();*/

	/*for (unsigned int i = 0; i < ChunksToInsert.Count(); i++)
	{
		delete ChunksToInsert[i];
	}
	ChunksToInsert.Clear();*/

	//ChunksChanging.unlock();
}

void ChunkManager::InsertAround(VectorF3 pos, unsigned int size)
{
	VectorI3 chunk_idx(pos.roundF() / (float)CHUNK_VALUES_PER_SIDE);

	BoxI3 box(chunk_idx - (int)size, chunk_idx + (int)size);
	VectorI3 box_size = box.Size() + 1;

	Chunk ** arr = new Chunk*[box_size.Product()]; // keep this allocated ?
	for (int i = 0; i < box_size.Product(); i++)
	{
		arr[i] = nullptr;
	}

	StopWatch sw;

	//if (!ChunksChanging.try_lock()) { return; }

	// check Chunks (dont need to change)
	// check ChunkToInsert (dont need to change)

//	sw.Start();
//	ChunksLock.Changing0();
//	ChunksChanging.lock();
//	ChunksChecking.lock();
//	ChunksCheckingCount++;
//	ChunksChecking.unlock();
//	ChunksToInsertChanging.lock();
//	sw.Stop();
//	TimeInsert.WaitTime.NewValue(sw.ElapsedTime());

//	sw.Start();
	std::cout << "InsertAround:" << __LINE__ << '\n';
//	std::cout << "line:" << __LINE__ << '\n';
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
//	std::cout << "line:" << __LINE__ << '\n';
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
//	std::cout << "line:" << __LINE__ << '\n';
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
//	std::cout << "line:" << __LINE__ << '\n';
	delete[] arr;
//	std::cout << "line:" << __LINE__ << '\n';
	ChunksToInsertLock.Checking0(sw, TimeInsertNeighbours);
	for (unsigned int i = 0; i < ChunksToInsert.Count(); i++)
	{
		if (ChunksToInsert[i] == nullptr) { continue; }
		FindNeighbours(*ChunksToInsert[i]);
	}
	ChunksToInsertLock.Checking1(sw, TimeInsertNeighbours);
//	std::cout << "line:" << __LINE__ << '\n';

//	ChunksToInsertChanging.unlock();
//	ChunksCheckingCount--;
//	ChunksChanging.unlock();
//	ChunksLock.Changing1();
//	sw.Stop();
//	TimeInsert.DoTime.NewValue(sw.ElapsedTime());
}
void ChunkManager::RemoveAround(VectorF3 pos, unsigned int size)
{
	StopWatch sw;
	//if (!ChunksChanging.try_lock()) { return; }

	// dosent resize ChunksContainer
	// dosent change Chunk
	// changes ChunkPointer in ChunksContainer to null
	// changes ChunksToRemove

	sw.Start();
	std::cout << "RemoveAround:" << __LINE__ << '\n';
	ChunksLock.Changing0();
//	ChunksChanging.lock();
//	ChunksChecking.lock();
//	ChunksCheckingCount++;
//	ChunksChecking.unlock();
	std::cout << "RemoveAround:" << __LINE__ << '\n';
	ChunksToRemoveLock.Changing0();
	std::cout << "RemoveAround:" << __LINE__ << '\n';
	sw.Stop();
	TimeRemove.WaitTime.NewValue(sw.ElapsedTime());

	sw.Start();

	VectorI3 chunk_idx(pos.roundF() / (float)CHUNK_VALUES_PER_SIDE);
	BoxI3 chunk_box(chunk_idx - (int)size, chunk_idx + (int)size);

	std::cout << "RemoveAround:" << __LINE__ << '\n';
	for (unsigned int i = 0; i < Chunks.Count(); i++)
	{
		Chunk * chunk = Chunks[i];
		if (chunk == nullptr) { continue; }
		if (chunk_box.IntersectVecInclusive(chunk -> Index).All(true)) { continue; }

		Chunks[i] = nullptr;
		NullNeighbours(*chunk);
		ChunksToRemove.Insert(chunk);
	}

	std::cout << "RemoveAround:" << __LINE__ << '\n';
	ChunksToRemoveLock.Changing1();
//	ChunksChanging.unlock();
//	ChunksCheckingCount--;
	std::cout << "RemoveAround:" << __LINE__ << '\n';
	ChunksLock.Changing1();
	std::cout << "RemoveAround:" << __LINE__ << '\n';
	sw.Stop();
	TimeRemove.DoTime.NewValue(sw.ElapsedTime());
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

/* Removing
Thread0					Thread1
	|						|
	| member function		|
	|						| ToRemove
	|						| lock
	|						| unlock
	|						| delete
	| lock					|
	segfault

use Counting Pointer ?
when to count ?
whenever a Member function is called ?
usa an atomic int

lock before member function ?
this would segfault after chunk is deleted



when Objects are deleted
ChunksContainer is also locked



allways lock from the outside
to be accessible from the outside, it must be in the ChunksContainer
so it wont be deleted

if it is in the ToRemoveContainer
then it is not accessible from the outside
an all that access from the inside should already have it locked
*/

void ChunkManager::UpdateChunksContainer()
{
	StopWatch sw;
	std::cout << "line:" << __LINE__ << '\n';
	//if (!ChunksChanging.try_lock()) { return; }

//	sw.Start();
//	ChunksChanging.lock();
//	ChunksChecking.lock();
//	std::cout << "Checking Count ....\n";
//	while (ChunksCheckingCount.load() != 0) { }
//	std::cout << "Checking Count done\n";
	ChunksLock.Changing0(sw, TimeUpdate);
//	sw.Stop();
//	WaitTimeUpdate.NewValue(sw.ElapsedTime());

	sw.Start();

	// Remove Chunks
	{
		StopWatch sw2;
		sw2.Start();
		ChunksToRemoveLock.Changing0();
		for (unsigned int i = 0; i < ChunksToRemove.Count(); i++)
		{
			Chunk * chunk = ChunksToRemove[i];
			if (chunk != nullptr) { continue; }
			if (chunk -> GraphicsExist) { continue; }
			chunk -> Changing.lock();
			chunk -> Changing.unlock();
			delete chunk;
			ChunksToRemove.Remove(i);
			i--;
		}
		ChunksToRemoveLock.Changing1();
		sw2.Stop();
		TimeUpdateRemove.DoTime.NewValue(sw2.ElapsedTime());
	}

	// replace nullptrs
	// if nullptrs left over, remove those
	// if need more, insert those

	{
		StopWatch sw2;
		sw2.Start();
		for (unsigned int i = 0; i < Chunks.Count(); i++)
		{
			if (Chunks[i] != nullptr) { continue; }
			Chunks.Remove(i);
			i--;
		}
		sw2.Stop();
		TimeUpdateChange.DoTime.NewValue(sw2.ElapsedTime());
	}

	// Insert Chunks
	{
		StopWatch sw2;
		//sw2.Start();
		//ChunksToInsertChanging.lock();
		ChunksToInsertLock.Changing0(sw2, TimeUpdateInsert);
		for (unsigned int i = 0; i < ChunksToInsert.Count(); i++)
		{
			Chunk * chunk = ChunksToInsert[i];
			if (chunk == nullptr) { continue; }
			if (!(chunk -> GraphicsExist)) { continue; }
			Chunks.Insert(chunk);
			ChunksToInsert.Remove(i);
			i--;
		}
		ChunksToInsertLock.Changing1(sw2, TimeUpdateInsert);
		//ChunksToInsertChanging.unlock();
		//sw2.Stop();
		//TimeChunksInsert.DoTime.NewValue(sw2.ElapsedTime());
	}

	ChunksLock.Changing1(sw, TimeUpdate);
//	ChunksChecking.unlock();
//	ChunksChanging.unlock();
//	sw.Stop();
//	TimeUpdate.NewValue(sw.ElapsedTime());
}



Chunk * ChunkManager::FindGenerateChunk(VectorF3 pos, unsigned int size)
{
	StopWatch sw;
	//if (!ChunksChanging.try_lock()) { return nullptr; }

//	sw.Start();
//	ChunksChanging.lock();
//	ChunksChecking.lock();
//	ChunksCheckingCount++;
//	ChunksChecking.unlock();
	std::cout << "FindGenerateChunk:" << __LINE__ << '\n';
	ChunksLock.Checking0(sw, TimeGenerate);
	std::cout << "FindGenerateChunk:" << __LINE__ << '\n';
//	sw.Stop();
//	WaitTimeGenerate.NewValue(sw.ElapsedTime());

	sw.ReStart();


	VectorI3 chunk_idx(pos.roundF() / (float)CHUNK_VALUES_PER_SIDE);
	BoxI3 chunk_box(chunk_idx - (int)size, chunk_idx + (int)size);

	Chunk * found = nullptr;
	float dist;
	for (unsigned int i = 0; i < Chunks.Count(); i++)
	{
		if (Chunks[i] == nullptr)
		{ continue; }

		Chunk & chunk = *Chunks[i];

		if (!chunk.Changing.try_lock())
		{ continue; }

		if (chunk.Done())
		{ chunk.Changing.unlock(); continue; }

		if (!chunk_box.IntersectVecInclusive(chunk.Index).All(true))
		{ chunk.Changing.unlock(); continue; }

		VectorF3 rel = ((chunk.Index + VectorF3(0.5f)) * CHUNK_VALUES_PER_SIDE) - pos;
		float d = rel.length2();
		if (found == nullptr || d < dist)
		{
			if (found != nullptr) { found -> Changing.unlock(); }
			found = &chunk;
			dist = d;
		}
		else { chunk.Changing.unlock(); }
	}

	std::cout << "FindGenerateChunk:" << __LINE__ << '\n';
	ChunksLock.Checking1(sw, TimeGenerate);
	std::cout << "FindGenerateChunk:" << __LINE__ << '\n';

//	ChunksCheckingCount--;
//	ChunksChanging.unlock();
//	sw.Stop();
//	TimeGenerate.NewValue(sw.ElapsedTime());

	return found;
}
void ChunkManager::GenerateAround(const Perlin2D & noise2, const Perlin3D & noise3, VectorF3 pos, unsigned int size, unsigned int count)
{
	for (unsigned int c = 0; c < count; c++)
	{
		Chunk * chunk = FindGenerateChunk(pos, size);
		if (chunk == nullptr) { break; }
		chunk -> Generate(noise2, noise3);
		chunk -> Neighbours.UpdateBufferMain();
		chunk -> Changing.unlock();
	}
}





void ChunkManager::GraphicsCreate()
{
	if (GraphicsExist) { return; }

	Shader.Create();
	Texture.Create();
	for (unsigned int i = 0; i < Chunks.Count(); i++)
	{
		(*Chunks[i]).GraphicsCreate();
	}

	GraphicsExist = true;
}
void ChunkManager::GraphicsDelete()
{
	if (!GraphicsExist) { return; }

	Shader.Delete();
	Texture.Delete();
	for (unsigned int i = 0; i < Chunks.Count(); i++)
	{
		(*Chunks[i]).GraphicsDelete();
	}

	GraphicsExist = false;
}
void ChunkManager::GraphicsUpdate()
{
	if (!GraphicsExist) { return; }

	// lock Chunks ?

	std::cout << "GraphicsUpdate:" << __LINE__ << '\n';
	{
		StopWatch sw;
		ChunksToRemoveLock.Changing0(sw, TimeGraphicsDelete);
		for (unsigned int i = 0; i < ChunksToRemove.Count(); i++)
		{
			Chunk * chunk = ChunksToRemove[i];
			if (chunk == nullptr) { continue; }
			chunk -> GraphicsDelete();
		}
		ChunksToRemoveLock.Changing1(sw, TimeGraphicsDelete);
	}
	std::cout << "GraphicsUpdate:" << __LINE__ << '\n';
	{
		StopWatch sw;
		ChunksToInsertLock.Changing0(sw, TimeGraphicsCreate);
		for (unsigned int i = 0; i < ChunksToInsert.Count(); i++)
		{
			Chunk * chunk = ChunksToInsert[i];
			if (chunk == nullptr) { continue; }
			chunk -> GraphicsCreate();
		}
		ChunksToInsertLock.Changing1(sw, TimeGraphicsCreate);
	}
	std::cout << "GraphicsUpdate:" << __LINE__ << '\n';
}



Chunk * ChunkManager::FindGraphicsUpdateChunk(VectorF3 pos)
{
	StopWatch sw;
	std::cout << "line:" << __LINE__ << '\n';
//	if (!ChunksChanging.try_lock()) { return nullptr; }

//	sw.Start();
//	ChunksChanging.lock();
//	ChunksChecking.lock();
//	ChunksCheckingCount++;
//	ChunksChecking.unlock();
	ChunksLock.Checking0(sw, TimeGraphics);
//	sw.Stop();
//	WaitTimeBuffer.NewValue(sw.ElapsedTime());

//	sw.ReStart();

	Chunk * found = nullptr;
	float dist;
	for (unsigned int i = 0; i < Chunks.Count(); i++)
	{
		if (Chunks[i] == nullptr)
		{ continue; }

		Chunk & chunk = *Chunks[i];

		if (!chunk.Changing.try_lock())
		{ continue; }

		if (!chunk.Done())
		{ chunk.Changing.unlock(); continue; }

		if (chunk.MainBufferState != Chunk::BufferDataState::Needed)
		{ chunk.Changing.unlock(); continue; }

		VectorF3 rel = ((chunk.Index + VectorF3(0.5f)) * CHUNK_VALUES_PER_SIDE) - pos;
		float d = rel.length2();
		if (found == nullptr || d < dist)
		{
			if (found != nullptr) { found -> Changing.unlock(); }
			found = &chunk;
			dist = d;
		}
		else { chunk.Changing.unlock(); }
	}

	ChunksLock.Checking1(sw, TimeGraphics);
//	ChunksCheckingCount--;
//	ChunksChanging.unlock();
//	sw.Stop();
//	TimeBuffer.NewValue(sw.ElapsedTime());

	return found;
}
void ChunkManager::GraphicsUpdateDataAround(VectorF3 pos, unsigned int count)
{
	for (unsigned int c = 0; c < count; c++)
	{
		Chunk * chunk = FindGraphicsUpdateChunk(pos);
		if (chunk == nullptr) { break; }
		chunk -> GraphicsUpdateMainData();
		chunk -> Changing.unlock();
	}
}

void ChunkManager::Draw()
{
	if (!GraphicsExist) { return; }

//	ChunksChanging.lock();
//	ChunksChecking.lock();
//	ChunksCheckingCount++;
//	ChunksChecking.unlock();
	StopWatch sw;

	std::cout << "line:" << __LINE__ << '\n';
	ChunksLock.Checking0(sw, TimeDraw);

	Shader.Bind();
	Texture.Bind();
	for (unsigned int i = 0; i < Chunks.Count(); i++)
	{
		if (Chunks[i] == nullptr) { continue; }
		Chunks[i] -> Draw();
	}

	ChunksLock.Checking1(sw, TimeDraw);
//	ChunksCheckingCount--;
//	ChunksChanging.unlock();
}
