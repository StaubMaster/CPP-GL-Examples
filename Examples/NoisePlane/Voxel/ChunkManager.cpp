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



void ChunkManager::UpdateChunksArray()
{
	for (unsigned int i = 0; i < ChunksCount.Product(); i++)
	{
		if (ChunksArray[i] != nullptr) { continue; }
		ChunksArray[i] = new Chunk(ChunksCount.Convert(i) + ChunksCorner);
		ChunksArray[i] -> GraphicsCreate();
		ChunksArray[i] -> Neighbours.Change(AxisRel::Here, ChunksArray[i]);
	}
}
void ChunkManager::UpdateChunksArrayGenerate(const Perlin2D & noise2, const Perlin3D & noise3)
{
	for (unsigned int i = 0; i < ChunksCount.Product(); i++)
	{
		if (ChunksArray[i] == nullptr) { continue; }
		ChunksArray[i] -> Generate(noise2, noise3);
		ChunksArray[i] -> GraphicsUpdateMainData();
	}
}
void ChunkManager::UpdateChunksArrayDraw()
{
	Shader.Bind();
	Texture.Bind();
	for (unsigned int i = 0; i < ChunksCount.Product(); i++)
	{
		if (ChunksArray[i] == nullptr) { continue; }
		ChunksArray[i] -> Draw();
	}
}

static VectorU3 ChunkSkipped;
static VectorU3 ChunkMoved;

void ChunkManager::UpdateChunksCenterLoopX(VectorU3 u, VectorI3 diff)
{
	unsigned int udx0 = ChunksCount.Convert(u);
	delete ChunksArray[udx0];
	ChunksArray[udx0] = nullptr;

	if (((int)u.X) + diff.X < 0) { ChunkSkipped.X++; return; }
	if (((int)u.X) + diff.X >= (int)ChunksCount.X) { ChunkSkipped.X++; return; }

	unsigned int udx1 = ChunksCount.Convert(VectorU3(u.X + diff.X, u.Y, u.Z));
	ChunksArray[udx0] = ChunksArray[udx1];
	ChunksArray[udx1] = nullptr;
	ChunkMoved.X++;
}
void ChunkManager::UpdateChunksCenterLoopY(VectorU3 u, VectorI3 diff)
{
	unsigned int udx0 = ChunksCount.Convert(u);
	delete ChunksArray[udx0];
	ChunksArray[udx0] = nullptr;

	if (((int)u.Y) + diff.Y < 0) { ChunkSkipped.Y++; return; }
	if (((int)u.Y) + diff.Y >= (int)ChunksCount.Y) { ChunkSkipped.Y++; return; }

	unsigned int udx1 = ChunksCount.Convert(VectorU3(u.X, u.Y + diff.Y, u.Z));
	ChunksArray[udx0] = ChunksArray[udx1];
	ChunksArray[udx1] = nullptr;
	ChunkMoved.Y++;
}
void ChunkManager::UpdateChunksCenterLoopZ(VectorU3 u, VectorI3 diff)
{
	unsigned int udx0 = ChunksCount.Convert(u);
	delete ChunksArray[udx0];
	ChunksArray[udx0] = nullptr;

	if (((int)u.Z) + diff.Z < 0) { ChunkSkipped.Z++; return; }
	if (((int)u.Z) + diff.Z >= (int)ChunksCount.Z) { ChunkSkipped.Z++; return; }

	unsigned int udx1 = ChunksCount.Convert(VectorU3(u.X, u.Y, u.Z + diff.Z));
	ChunksArray[udx0] = ChunksArray[udx1];
	ChunksArray[udx1] = nullptr;
	ChunkMoved.Z++;
}

void ChunkManager::UpdateChunksCenter(VectorI3 center)
{
	if ((ChunksCenter == center).All(true)) { return; }

	// diff = center - Center

	//	0	1	2	3	4	5	6	7
	//			0	1	2	3	4	5	6	7
	// diff +2
	// remove [0;1]
	// move   [2;7] to [0;5]
	// insert [6;7]

	//			0	1	2	3	4	5	6	7
	//	0	1	2	3	4	5	6	7
	// diff -2
	// remove [6;7]
	// move   [0;5] to [2;7]
	// insert [0;1]

	// n - diff < 0; ignore
	// n - diff > limit; ignore
	// [n] = [n + diff]
	// when moving, delete the one currently at that postion
	// then moving, make the old one null

	// iterate in moving direction
	VectorI3 diff = center - ChunksCenter;
	std::cout << "diff " << diff << '\n';

	ChunkSkipped = VectorU3(0);
	ChunkMoved = VectorU3(0);

	UndexLoop3D loop(VectorU3(), ChunksCount);

	if (diff.X > 0) { for (VectorU3 u = loop.Min(); loop.Check(u).All(true); loop.Next(u)) { UpdateChunksCenterLoopX(u, diff); } }
	if (diff.X < 0) { for (VectorU3 u = loop.Max(); loop.Check(u).All(true); loop.Prev(u)) { UpdateChunksCenterLoopX(u, diff); } }

	if (diff.Y > 0) { for (VectorU3 u = loop.Min(); loop.Check(u).All(true); loop.Next(u)) { UpdateChunksCenterLoopY(u, diff); } }
	if (diff.Y < 0) { for (VectorU3 u = loop.Max(); loop.Check(u).All(true); loop.Prev(u)) { UpdateChunksCenterLoopY(u, diff); } }

	if (diff.Z > 0) { for (VectorU3 u = loop.Min(); loop.Check(u).All(true); loop.Next(u)) { UpdateChunksCenterLoopZ(u, diff); } }
	if (diff.Z < 0) { for (VectorU3 u = loop.Max(); loop.Check(u).All(true); loop.Prev(u)) { UpdateChunksCenterLoopZ(u, diff); } }

	std::cout << "Skip: " << ChunkSkipped << '\n';
	std::cout << "Move: " << ChunkMoved << '\n';

	ChunksCenter = center;
	ChunksCorner += diff;
}
void ChunkManager::ChangeChunksSize(unsigned int size)
{
	std::cout << "line:" << __LINE__ << '\n';
	ChunksLock.Changing0();
	std::cout << "line:" << __LINE__ << '\n';
	for (unsigned int i = 0; i < ChunksCount.Product(); i++)
	{
		delete ChunksArray[i];
	}
	std::cout << "line:" << __LINE__ << '\n';
	delete[] ChunksArray;
	std::cout << "line:" << __LINE__ << '\n';

	// Size = 2
	// Center = c

	// +2 +1 c +1 +2
	// Count = 5
	// Box = [ c-2 ; c+2 ]
	// Corner = c-2

	std::cout << "line:" << __LINE__ << '\n';
	ChunksCorner = ChunksCenter - (int)size;

	std::cout << "line:" << __LINE__ << '\n';
	ChunksCount = VectorU3((size * 2) + 1);
	ChunksBox = BoxI3(ChunksCenter - (int)size, ChunksCenter + (int)size);

	std::cout << "line:" << __LINE__ << '\n';
	ChunksArray = new Chunk*[ChunksCount.Product()];
	for (unsigned int i = 0; i < ChunksCount.Product(); i++)
	{
		ChunksArray[i] = nullptr;
	}
	std::cout << "line:" << __LINE__ << '\n';

	ChunksLock.Changing1();
}



ChunkManager::~ChunkManager()
{
	for (unsigned int i = 0; i < Chunks.Count(); i++)
	{
		delete Chunks[i];
	}
	for (unsigned int i = 0; i < ChunksCount.Product(); i++)
	{
		delete ChunksArray[i];
	}
	delete[] ChunksArray;
}
ChunkManager::ChunkManager()
	: Shader()
	, ChunksArray(nullptr)
	, ChunksCount()
	, ChunksCenter()
	, ChunksBox()
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
//	std::cout << "InsertAround:" << __LINE__ << '\n';
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
//	std::cout << "RemoveAround:" << __LINE__ << '\n';
	ChunksLock.Changing0();
//	ChunksChanging.lock();
//	ChunksChecking.lock();
//	ChunksCheckingCount++;
//	ChunksChecking.unlock();
//	std::cout << "RemoveAround:" << __LINE__ << '\n';
	ChunksToRemoveLock.Changing0();
//	std::cout << "RemoveAround:" << __LINE__ << '\n';
	sw.Stop();
	TimeRemove.WaitTime.NewValue(sw.ElapsedTime());

	sw.Start();

	VectorI3 chunk_idx(pos.roundF() / (float)CHUNK_VALUES_PER_SIDE);
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
//	ChunksChanging.unlock();
//	ChunksCheckingCount--;
//	std::cout << "RemoveAround:" << __LINE__ << '\n';
	ChunksLock.Changing1();
//	std::cout << "RemoveAround:" << __LINE__ << '\n';
	sw.Stop();
	TimeRemove.DoTime.NewValue(sw.ElapsedTime());
}

void ChunkManager::FindNeighbours(unsigned int & idx)
{
	StopWatch sw;
	ChunksToInsertLock.Checking0(sw, TimeInsertNeighbours);
	for (unsigned int i = 0; i < ChunksToInsert.Count(); i++, idx++)
	{
		if (idx >= ChunksToInsert.Count()) { idx = 0; }
		if (ChunksToInsert[idx] == nullptr) { continue; }
		if (ChunksToInsert[idx] -> Done()) { continue; }
		FindNeighbours(*ChunksToInsert[idx]);
		break;
	}
	idx++;
	ChunksToInsertLock.Checking1(sw, TimeInsertNeighbours);
}
void ChunkManager::NullNeighbours(unsigned int & idx)
{
	//StopWatch sw;
	ChunksToRemoveLock.Checking0();
	for (unsigned int i = 0; i < ChunksToRemove.Count(); i++, idx++)
	{
		if (idx >= ChunksToRemove.Count()) { idx = 0; }
		if (ChunksToRemove[idx] == nullptr) { continue; }
		if (!ChunksToRemove[idx] -> Done()) { continue; }
		NullNeighbours(*ChunksToRemove[idx]);
		break;
	}
	idx++;
	ChunksToRemoveLock.Checking1();
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
//	std::cout << "line:" << __LINE__ << '\n';
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
			if (chunk == nullptr) { ChunksToRemove.Remove(i); i--; continue; }
			if (chunk -> GraphicsExist) { continue; }
			if (chunk -> Neighbours.Done()) { continue; }
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
			if (!(chunk -> Neighbours.Done())) { continue; }
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
//	std::cout << "FindGenerateChunk:" << __LINE__ << '\n';
	ChunksLock.Checking0(sw, TimeGenerate);
//	std::cout << "FindGenerateChunk:" << __LINE__ << '\n';
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

//	std::cout << "FindGenerateChunk:" << __LINE__ << '\n';
	ChunksLock.Checking1(sw, TimeGenerate);
//	std::cout << "FindGenerateChunk:" << __LINE__ << '\n';

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

//	std::cout << "GraphicsUpdate:" << __LINE__ << '\n';
	{
		StopWatch sw;
		ChunksToRemoveLock.Checking0(sw, TimeGraphicsDelete);
		for (unsigned int i = 0; i < ChunksToRemove.Count(); i++)
		{
			Chunk * chunk = ChunksToRemove[i];
			if (chunk == nullptr) { continue; }
			chunk -> GraphicsDelete();
		}
		ChunksToRemoveLock.Checking1(sw, TimeGraphicsDelete);
	}
//	std::cout << "GraphicsUpdate:" << __LINE__ << '\n';
	{
		StopWatch sw;
		ChunksToInsertLock.Checking0(sw, TimeGraphicsCreate);
		for (unsigned int i = 0; i < ChunksToInsert.Count(); i++)
		{
			Chunk * chunk = ChunksToInsert[i];
			if (chunk == nullptr) { continue; }
			chunk -> GraphicsCreate();
		}
		ChunksToInsertLock.Checking1(sw, TimeGraphicsCreate);
	}
//	std::cout << "GraphicsUpdate:" << __LINE__ << '\n';
}



Chunk * ChunkManager::FindGraphicsUpdateChunk(VectorF3 pos)
{
	StopWatch sw;
//	std::cout << "line:" << __LINE__ << '\n';
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

//	std::cout << "line:" << __LINE__ << '\n';
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
