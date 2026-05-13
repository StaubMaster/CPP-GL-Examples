#include "ChunkManager.hpp"
#include "Chunk.hpp"
#include "Voxel.hpp"
#include "VoxelOrientation.hpp"
#include "ChunkVoxelIndex.hpp"
#include "ChunkNeighbours.hpp"

#include "ValueType/Bool3.hpp"
#include "ValueType/Box/I3.hpp"
#include "ValueType/LoopI3.hpp"

#include "ValueType/Ray3D.hpp"

#include "GridCast/GridCast3D.hpp"



// Code
#include "Telemetry/ThreadInfo.hpp"
#include "Telemetry/WaitDoTime.hpp"
#include "ContainerLock.hpp"

#include "ValueType/LoopU3.hpp"



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
//	std::cout << "ChangeChunksArraySize:" << __LINE__ << '\n';
	ChunksLock.Changing0();
//	std::cout << "ChangeChunksArraySize:" << __LINE__ << '\n';
	for (unsigned int i = 0; i < Chunks.Length(); i++)
	{
		Chunks[i] -> GraphicsDelete();
		delete Chunks[i];
	}
//	std::cout << "ChangeChunksArraySize:" << __LINE__ << '\n';
//	std::cout << "ChangeChunksArraySize:" << __LINE__ << '\n';
	Corner = Center - (int)size;
//	std::cout << "ChangeChunksArraySize:" << __LINE__ << '\n';
	Chunks.ChangeSize(VectorU3((size * 2) + 1), nullptr);
//	std::cout << "ChangeChunksArraySize:" << __LINE__ << '\n';
	ChunksLock.Changing1();
//	std::cout << "ChangeChunksArraySize:" << __LINE__ << '\n';
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

	LoopU3 loop(VectorU3(), Chunks.Size());

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
	for (unsigned int i = 0; i < Chunks.Length(); i++)
	{
		delete Chunks[i];
	}
	/*for (unsigned int i = 0; i < ChunksArray.Count(); i++)
	{
		delete ChunksArray[i];
	}*/
}
ChunkManager::ChunkManager()
	: ShaderU()
	, ShaderF()
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
			if (chunk.HitVoxel(idx)) { return GridCast3D::Hit(data); }
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
		if (!(chunk -> GenerationDone())) { chunk -> unlock(); return GridCast3D::Hit(); }
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



WaitDoTime ChunkManager::TimeInsert("TimeInsert");
WaitDoTime ChunkManager::TimeInsertNeighbours("TimeInsertNeighbours");
WaitDoTime ChunkManager::TimeRemove("TimeRemove");
WaitDoTime ChunkManager::TimeUpdate("TimeUpdate");
WaitDoTime ChunkManager::TimeUpdateInsert("TimeUpdateInsert");
WaitDoTime ChunkManager::TimeUpdateChange("TimeUpdateChange");
WaitDoTime ChunkManager::TimeUpdateRemove("TimeUpdateRemove");
WaitDoTime ChunkManager::TimeGenerateFind("TimeGenerateFind");
WaitDoTime ChunkManager::TimeGenerate("TimeGenerate");
WaitDoTime ChunkManager::TimeBuffersFind("TimeBuffersFind");
WaitDoTime ChunkManager::TimeBuffers("TimeBuffers");
WaitDoTime ChunkManager::TimeGraphicsCreate("TimeGraphicsCreate");
WaitDoTime ChunkManager::TimeGraphicsDelete("TimeGraphicsDelete");
WaitDoTime ChunkManager::TimeDraw("TimeDraw");



void ChunkManager::Clear()
{ }

void ChunkManager::InsertAround(VectorF3 pos, unsigned int size)
{
	VectorI3 chunk_idx((pos / (float)CHUNK_VALUES_PER_SIDE).roundF());
	BoxI3 box(chunk_idx - (int)size, chunk_idx + (int)size);
	VectorU3 box_size = box.Size() + 1;

	Array3D<Chunk*> arr(box_size, nullptr);

	StopWatch sw;

//	std::cout << "InsertAround:" << __LINE__ << '\n';

	ChunksLock.Checking0();
	for (unsigned int i = 0; i < Chunks.Length(); i++)
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
			ChunksToInsert.Insert(new Chunk(i, *this));
		}
	}
	ChunksToInsertLock.Changing1();

//	std::cout << "InsertAround:" << __LINE__ << '\n';
}
void ChunkManager::RemoveAround(VectorF3 pos, unsigned int size)
{
	StopWatch sw;
	sw.Start();
//	std::cout << "RemoveAround:" << __LINE__ << '\n';
//	ChunksLock.Changing0();
	ChunksLock.Checking0();
//	std::cout << "RemoveAround:" << __LINE__ << '\n';
	ChunksToRemoveLock.Changing0();
//	std::cout << "RemoveAround:" << __LINE__ << '\n';
	sw.Stop();
	TimeRemove.WaitTime.NewValue(sw.ElapsedTime());
	TimeRemove.ThreadName = ThreadInfo::ThreadName;

	sw.Start();

	VectorI3 chunk_idx((pos / (float)CHUNK_VALUES_PER_SIDE).roundF());
	BoxI3 chunk_box(chunk_idx - (int)size, chunk_idx + (int)size);

//	std::cout << "RemoveAround:" << __LINE__ << '\n';
	for (unsigned int i = 0; i < Chunks.Length(); i++)
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
	ChunksLock.Checking1();
//	ChunksLock.Changing1();
//	std::cout << "RemoveAround:" << __LINE__ << '\n';
	sw.Stop();
	TimeRemove.DoTime.NewValue(sw.ElapsedTime());
}

void ChunkManager::UpdateChunksContainer()
{
	StopWatch sw;
//	std::cout << "UpdateChunksContainer:" << __LINE__ << '\n';
	ChunksLock.Changing0(sw, TimeUpdate);
//	ChunksLock.Checking0(sw, TimeUpdate);
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
		for (unsigned int i = 0; i < Chunks.Length(); i++)
		{
			if (Chunks[i] == nullptr) { null_count++; }
		}
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
			VectorU3 u = relative(chunk -> Index);
			if ((u < Chunks.Size()).Any(false)) { continue; }
			if (Chunks[u] != nullptr) { continue; }
			Chunks[u] = chunk;
			ChunksToInsert.Remove(i);
			i--;
		}
		ChunksToInsertLock.Changing1(sw2, TimeUpdateInsert);
	}

//	std::cout << "UpdateChunksContainer:" << __LINE__ << '\n';
//	ChunksLock.Checking1(sw, TimeUpdate);
	ChunksLock.Changing1(sw, TimeUpdate);
//	std::cout << "UpdateChunksContainer:" << __LINE__ << '\n';
}



ChunkNeighbour ChunkManager::FindNeighbours(const Chunk & chunk) const
{
	ChunkNeighbour neighbours;
	neighbours.Here = (Chunk*)&chunk;
	neighbours.PrevX = Chunks[relative(chunk.Index - VectorI3(1, 0, 0))];
	neighbours.PrevY = Chunks[relative(chunk.Index - VectorI3(0, 1, 0))];
	neighbours.PrevZ = Chunks[relative(chunk.Index - VectorI3(0, 0, 1))];
	neighbours.NextX = Chunks[relative(chunk.Index + VectorI3(1, 0, 0))];
	neighbours.NextY = Chunks[relative(chunk.Index + VectorI3(0, 1, 0))];
	neighbours.NextZ = Chunks[relative(chunk.Index + VectorI3(0, 0, 1))];
	return neighbours;
}
/*const Chunk * ChunkManager::NeighbourLoopChunk(const Chunk & chunk, VectorU3 & udx, AxisRel axis)
{
	unsigned int n = CHUNK_VALUES_PER_SIDE - 1;
	const Chunk * ptr = &chunk;
	//ChunksLock.Checking0();
	switch (axis)
	{
		case AxisRel::None: ptr = nullptr; break;
		case AxisRel::PrevX: if (udx.X != 0) { udx.X--; ptr = &chunk; } else { udx.X = n; ptr = Chunks[relative(chunk.Index - VectorI3(1, 0, 0))]; } break;
		case AxisRel::PrevY: if (udx.Y != 0) { udx.Y--; ptr = &chunk; } else { udx.Y = n; ptr = Chunks[relative(chunk.Index - VectorI3(0, 1, 0))]; } break;
		case AxisRel::PrevZ: if (udx.Z != 0) { udx.Z--; ptr = &chunk; } else { udx.Z = n; ptr = Chunks[relative(chunk.Index - VectorI3(0, 0, 1))]; } break;
		case AxisRel::NextX: if (udx.X != n) { udx.X++; ptr = &chunk; } else { udx.X = 0; ptr = Chunks[relative(chunk.Index + VectorI3(1, 0, 0))]; } break;
		case AxisRel::NextY: if (udx.Y != n) { udx.Y++; ptr = &chunk; } else { udx.Y = 0; ptr = Chunks[relative(chunk.Index + VectorI3(0, 1, 0))]; } break;
		case AxisRel::NextZ: if (udx.Z != n) { udx.Z++; ptr = &chunk; } else { udx.Z = 0; ptr = Chunks[relative(chunk.Index + VectorI3(0, 0, 1))]; } break;
		case AxisRel::Here: ptr = &chunk; break;
	}
	//ChunksLock.Checking1();
	return ptr;
}*/
void ChunkManager::NeighbourUpdateBufferMain(VectorI3 idx)
{
	Chunk * chunk;
	chunk = Chunks[relative(idx)]; if (chunk != nullptr) { chunk -> MainBufferState = BufferDataState::Needed; }
	chunk = Chunks[relative(idx - VectorI3(1, 0, 0))]; if (chunk != nullptr) { chunk -> MainBufferState = BufferDataState::Needed; }
	chunk = Chunks[relative(idx - VectorI3(0, 1, 0))]; if (chunk != nullptr) { chunk -> MainBufferState = BufferDataState::Needed; }
	chunk = Chunks[relative(idx - VectorI3(0, 0, 1))]; if (chunk != nullptr) { chunk -> MainBufferState = BufferDataState::Needed; }
	chunk = Chunks[relative(idx + VectorI3(1, 0, 0))]; if (chunk != nullptr) { chunk -> MainBufferState = BufferDataState::Needed; }
	chunk = Chunks[relative(idx + VectorI3(0, 1, 0))]; if (chunk != nullptr) { chunk -> MainBufferState = BufferDataState::Needed; }
	chunk = Chunks[relative(idx + VectorI3(0, 0, 1))]; if (chunk != nullptr) { chunk -> MainBufferState = BufferDataState::Needed; }

//	if (Here  != nullptr) { Here  -> MainBufferState = BufferDataState::Needed; }
//	if (PrevX != nullptr) { PrevX -> MainBufferState = BufferDataState::Needed; }
//	if (PrevY != nullptr) { PrevY -> MainBufferState = BufferDataState::Needed; }
//	if (PrevZ != nullptr) { PrevZ -> MainBufferState = BufferDataState::Needed; }
//	if (NextX != nullptr) { NextX -> MainBufferState = BufferDataState::Needed; }
//	if (NextY != nullptr) { NextY -> MainBufferState = BufferDataState::Needed; }
//	if (NextZ != nullptr) { NextZ -> MainBufferState = BufferDataState::Needed; }
}



Chunk * ChunkManager::FindGenerateChunk(VectorF3 pos, unsigned int size)
{
	StopWatch sw;
//	std::cout << "FindGenerateChunk:" << __LINE__ << '\n';
	ChunksLock.Checking0(sw, TimeGenerateFind);
//	std::cout << "FindGenerateChunk:" << __LINE__ << '\n';

	VectorI3 chunk_idx((pos / (float)CHUNK_VALUES_PER_SIDE).roundF());
	BoxI3 chunk_box(chunk_idx - (int)size, chunk_idx + (int)size);

	Chunk * found = nullptr;
	float dist;
	for (unsigned int i = 0; i < Chunks.Length(); i++)
	{
		if (Chunks[i] == nullptr)
		{ continue; }

		Chunk & chunk = *Chunks[i];

//		std::cout << "FindGenerateChunk:" << __LINE__ << '\n';
		//chunk.lock();
//		std::cout << "FindGenerateChunk:" << __LINE__ << '\n';
		if (!chunk.try_lock())
		{ continue; }
//		std::cout << "FindGenerateChunk:" << __LINE__ << '\n';

		if (chunk.GenerationDone())
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
	ChunksLock.Checking1(sw, TimeGenerateFind);
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

		StopWatch sw;
		sw.Start();
		chunk -> GenerateTerrain(noise2, noise3);
		chunk -> GenerateDecorate(noise2, noise3);
		sw.Stop();
		TimeGenerate.DoTime.NewValue(sw.ElapsedTime());
		TimeGenerate.ThreadName = ThreadInfo::ThreadName;

		chunk -> unlock();
	}
}



/* Graphics
	creating/deleting is slow ?
	allocate all chunks once at the beginnig
	create buffers for all at once ?
*/

void ChunkManager::GraphicsCreate()
{
	if (GraphicsExist) { return; }

	ShaderU.Create();
	ShaderF.Create();
	Texture.Create();

//	std::cout << "GraphicsCreate:" << __LINE__ << '\n';
	ChunksLock.Checking0();
//	std::cout << "GraphicsCreate:" << __LINE__ << '\n';
	for (unsigned int i = 0; i < Chunks.Length(); i++)
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

	ShaderU.Delete();
	ShaderF.Delete();
	Texture.Delete();

//	std::cout << "GraphicsDelete:" << __LINE__ << '\n';
	ChunksLock.Checking0();
//	std::cout << "GraphicsDelete:" << __LINE__ << '\n';
	for (unsigned int i = 0; i < Chunks.Length(); i++)
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
	ChunksLock.Checking0(sw, TimeBuffersFind);
//	std::cout << "FindGraphicsUpdateChunk:" << __LINE__ << '\n';

	Chunk * found = nullptr;
	float dist;
	for (unsigned int i = 0; i < Chunks.Length(); i++)
	{
		if (Chunks[i] == nullptr) { continue; }
		Chunk & chunk = *Chunks[i];

//		std::cout << "FindGraphicsUpdateChunk:" << __LINE__ << '\n';
		//chunk.lock();
//		std::cout << "FindGraphicsUpdateChunk:" << __LINE__ << '\n';
		if (!chunk.try_lock())
		{ continue; }
//		std::cout << "FindGraphicsUpdateChunk:" << __LINE__ << '\n';

		if (!chunk.GenerationDone())
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
	ChunksLock.Checking1(sw, TimeBuffersFind);
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

		StopWatch sw;
		sw.Start();
		chunk -> GraphicsMakeData();
		sw.Stop();
		TimeBuffers.DoTime.NewValue(sw.ElapsedTime());
		TimeBuffers.ThreadName = ThreadInfo::ThreadName;

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

	ShaderU.Bind();
	Texture.Bind();
	for (unsigned int i = 0; i < Chunks.Length(); i++)
	{
		if (Chunks[i] == nullptr) { continue; }
		Chunks[i] -> DrawU();
	}

	/*ShaderF.Bind();
	Texture.Bind();
	for (unsigned int i = 0; i < Chunks.Length(); i++)
	{
		if (Chunks[i] == nullptr) { continue; }
		Chunks[i] -> DrawF();
	}*/

//	std::cout << "Draw:" << __LINE__ << '\n';
	ChunksLock.Checking1(sw, TimeDraw);
//	std::cout << "Draw:" << __LINE__ << '\n';
}
