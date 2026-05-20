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



WaitDoTime ChunkManager::TimeInsert("TimeInsert");
WaitDoTime ChunkManager::TimeRemove("TimeRemove");
WaitDoTime ChunkManager::TimeUpdate("TimeUpdate");
WaitDoTime ChunkManager::TimeUpdateInsert("TimeUpdateInsert");
WaitDoTime ChunkManager::TimeUpdateRemove("TimeUpdateRemove");
WaitDoTime ChunkManager::TimeGenerateFind("TimeGenerateFind");
WaitDoTime ChunkManager::TimeGenerate("TimeGenerate");
WaitDoTime ChunkManager::TimeBuffersFind("TimeBuffersFind");
WaitDoTime ChunkManager::TimeBuffers("TimeBuffers");
WaitDoTime ChunkManager::TimeGraphicsCreate("TimeGraphicsCreate");
WaitDoTime ChunkManager::TimeGraphicsDelete("TimeGraphicsDelete");
WaitDoTime ChunkManager::TimeDraw("TimeDraw");





bool ChunkManager::ChunkDataUEntry::IsValid() const
{
	return (Manager != nullptr);
}
VoxelGraphics::MainFaceU & ChunkManager::ChunkDataUEntry::operator[](unsigned int idx)
{
	return Manager -> BufferU_Array[Offset + idx];
}
void  ChunkManager::ChunkDataUEntry::Put(unsigned int offset, const Container::Array<VoxelGraphics::MainFaceU> & data)
{
	Manager -> BufferU.MainBuffer.DataPart((Offset + offset) * sizeof(VoxelGraphics::MainFaceU), data.ToVoid());
}

ChunkManager::ChunkDataUEntry::~ChunkDataUEntry()
{
	if (Manager != nullptr)
	{
		Manager -> BufferU_Remove(*this);
	}
}
ChunkManager::ChunkDataUEntry::ChunkDataUEntry()
	: Manager(nullptr)
	, Offset(0)
	, Length(0)
{ }

bool ChunkManager::BufferU_CheckEntry(ChunkDataUEntry & entry)
{
	if ((entry.Offset + entry.Length) >= BufferU_Array.Length())
	{
		return false;
	}
	for (unsigned int i = 0; i < BufferU_Entrys.Count(); i++)
	{
		ChunkDataUEntry & other = *(BufferU_Entrys[i]);
		if (
			(entry.Offset + entry.Length) > (other.Offset) &&
			(entry.Offset) < (other.Offset + other.Length)
		)
		{
			return false;
		}
	}
	return true;
}
void ChunkManager::BufferU_Insert(ChunkDataUEntry & entry)
{
	if (entry.Length == 0)
	{
		entry.Manager = nullptr;
		entry.Offset = 0;
		return;
	}

	entry.Manager = this;

	entry.Offset = 0;
	if (BufferU_CheckEntry(entry))
	{
		BufferU_Entrys.Insert(&entry);
		std::cout << "insert BufferUEntry of Length: " << entry.Length << " at " << entry.Offset << '\n';
		return;
	}

	for (unsigned int i = 0; i < BufferU_Entrys.Count(); i++)
	{
		ChunkDataUEntry & other = *(BufferU_Entrys[i]);
		entry.Offset = other.Offset + other.Length;
		if (BufferU_CheckEntry(entry))
		{
			BufferU_Entrys.Insert(&entry);
			std::cout << "insert BufferUEntry of Length: " << entry.Length << " at " << entry.Offset << '\n';
			return;
		}
	}

	std::cout << " failed BufferUEntry of Length: " << entry.Length << '\n';

	entry.Offset = 0;
	entry.Manager = nullptr;
}
void ChunkManager::BufferU_Remove(ChunkDataUEntry & entry)
{
	for (unsigned int i = 0; i < BufferU_Entrys.Count(); i++)
	{
		if (BufferU_Entrys[i] == &entry)
		{
			BufferU_Entrys.RemoveAt(i);
			break;
		}
	}
	std::cout << "remove BufferUEntry of Length: " << entry.Length << " at " << entry.Offset << '\n';
	entry.Manager = nullptr;
}





void ChunkManager::Clear()
{
//	std::cout << "Clear:" << __LINE__ << '\n';
	for (unsigned int i = 0; i < Chunks.Length(); i++)
	{
		Chunks[i] -> GraphicsDelete();
		delete Chunks[i];
	}
//	std::cout << "Clear:" << __LINE__ << '\n';
}
/* size
know: all the Chunks that are stored
care: where Chunks are inserted / generated
*/
void ChunkManager::ChangeSize(unsigned int know_size, unsigned int care_size)
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

	ChunksLock.AssignL();
	ChunksToRemoveLock.AssignL();

	VectorI3 diff = center - Center;

	ChunkSkipped = VectorU3(0);
	ChunkMoved = VectorU3(0);

	LoopU3 loop(VectorU3(), Chunks.Size());

	if (diff.X > 0) { for (VectorU3 u = loop.Min(); loop.Check(u).All(true); loop.Next(u)) { ChangeCenterLoopX(u, diff); } }
	if (diff.X < 0) { for (VectorU3 u = loop.Max(); loop.Check(u).All(true); loop.Prev(u)) { ChangeCenterLoopX(u, diff); } }

	if (diff.Y > 0) { for (VectorU3 u = loop.Min(); loop.Check(u).All(true); loop.Next(u)) { ChangeCenterLoopY(u, diff); } }
	if (diff.Y < 0) { for (VectorU3 u = loop.Max(); loop.Check(u).All(true); loop.Prev(u)) { ChangeCenterLoopY(u, diff); } }

	if (diff.Z > 0) { for (VectorU3 u = loop.Min(); loop.Check(u).All(true); loop.Next(u)) { ChangeCenterLoopZ(u, diff); } }
	if (diff.Z < 0) { for (VectorU3 u = loop.Max(); loop.Check(u).All(true); loop.Prev(u)) { ChangeCenterLoopZ(u, diff); } }

//	std::cout << "Skip: " << ChunkSkipped << '\n';
//	std::cout << "Move: " << ChunkMoved << '\n';

	Center = center;
	KnowBox = BoxI3(Center - (int)KnowSize, Center + (int)KnowSize);
	CareBox = BoxI3(Center - (int)CareSize, Center + (int)CareSize);

	ChunksToRemoveLock.AssignU();
	ChunksLock.AssignU();
}

VectorI3 ChunkManager::absolute(VectorU3 u) const { return u + KnowBox.Min; }
VectorU3 ChunkManager::relative(VectorI3 i) const { return i - KnowBox.Min; }

Chunk * ChunkManager::FindLockOrNull(VectorI3 idx)
{
	VectorU3 udx = relative(idx);
	if ((udx < Chunks.Size()).Any(false)) { return nullptr; }
	Chunk * chunk = Chunks[udx];
	if (chunk == nullptr) { return nullptr; }
	chunk -> AccessL();
	return chunk;
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

void ChunkManager::InsertAround()
{
	StopWatch sw;
	sw.Start();

	VectorU3 box_size = CareBox.Size() + 1;

	Array3D<Chunk*> arr(box_size, nullptr);

//	std::cout << "InsertAround:" << __LINE__ << '\n';

	ChunksLock.AccessL();
	for (unsigned int i = 0; i < Chunks.Length(); i++)
	{
		if (Chunks[i] == nullptr) { continue; }
		Chunk & chunk = *Chunks[i];
		if (CareBox.IntersectVecInclusive(chunk.Index).All(true))
		{
			unsigned int j = box_size.Convert(chunk.Index - CareBox.Min);
			arr[j] = &chunk;
		}
	}
	ChunksLock.AccessU();

//	std::cout << "InsertAround:" << __LINE__ << '\n';

	ChunksToInsertLock.AccessL();
	for (unsigned int i = 0; i < ChunksToInsert.Count(); i++)
	{
		if (ChunksToInsert[i] == nullptr) { continue; }
		Chunk & chunk = *ChunksToInsert[i];
		if (CareBox.IntersectVecInclusive(chunk.Index).All(true))
		{
			unsigned int j = box_size.Convert(chunk.Index - CareBox.Min);
			arr[j] = &chunk;
		}
	}
	ChunksToInsertLock.AccessU();

//	std::cout << "InsertAround:" << __LINE__ << '\n';

	ChunksToInsertLock.AssignL();
	LoopI3 loop(CareBox.Min, Bool3(false), CareBox.Max, Bool3(false));
	for (VectorI3 i = loop.Min(); loop.Check(i).All(true); loop.Next(i))
	{
		unsigned int j = box_size.Convert(i - CareBox.Min);
		if (arr[j] == nullptr)
		{
			ChunksToInsert.Insert(new Chunk(i, *this));
		}
	}
	ChunksToInsertLock.AssignU();

//	std::cout << "InsertAround:" << __LINE__ << '\n';
	sw.Stop();
	TimeInsert.DoTime.NewValue(sw.ElapsedTime());
	TimeInsert.ThreadName = ThreadInfo::ThreadName;
}
void ChunkManager::RemoveAround()
{
	StopWatch sw;
	sw.Start();
//	std::cout << "RemoveAround:" << __LINE__ << '\n';
//	ChunksLock.AssignL();
	ChunksLock.AccessL();
//	std::cout << "RemoveAround:" << __LINE__ << '\n';
	ChunksToRemoveLock.AssignL();
//	std::cout << "RemoveAround:" << __LINE__ << '\n';
	sw.Stop();
	TimeRemove.WaitTime.NewValue(sw.ElapsedTime());
	TimeRemove.ThreadName = ThreadInfo::ThreadName;

	sw.Clear();
	sw.Start();

//	std::cout << "RemoveAround:" << __LINE__ << '\n';
	for (unsigned int i = 0; i < Chunks.Length(); i++)
	{
		Chunk * chunk = Chunks[i];
		if (chunk == nullptr) { continue; }
		if (KnowBox.IntersectVecInclusive(chunk -> Index).All(true)) { continue; }

		Chunks[i] = nullptr;
		ChunksToRemove.Insert(chunk);
	}
//	std::cout << "RemoveAround:" << __LINE__ << '\n';
	ChunksToRemoveLock.AssignU();
//	std::cout << "RemoveAround:" << __LINE__ << '\n';
	ChunksLock.AccessU();
//	ChunksLock.AssignU();
//	std::cout << "RemoveAround:" << __LINE__ << '\n';
	sw.Stop();
	TimeRemove.DoTime.NewValue(sw.ElapsedTime());
}

void ChunkManager::UpdateChunksContainer()
{
	StopWatch sw;
//	std::cout << "UpdateChunksContainer:" << __LINE__ << '\n';
	ChunksLock.AssignL(sw, TimeUpdate);
//	ChunksLock.AccessL(sw, TimeUpdate);
//	std::cout << "UpdateChunksContainer:" << __LINE__ << '\n';

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
			if (chunk -> GraphicsExist) { continue; }
			chunk -> AssignL();
			chunk -> AssignU();
			delete chunk;
			ChunksToRemove.RemoveAt(i);
			i--;
		}
		ChunksToRemoveLock.AssignU();
		sw2.Stop();
		TimeUpdateRemove.DoTime.NewValue(sw2.ElapsedTime());
	}

	// Insert Chunks
	{
		StopWatch sw2;
		ChunksToInsertLock.AssignL(sw2, TimeUpdateInsert);
		for (unsigned int i = 0; i < ChunksToInsert.Count(); i++)
		{
			Chunk * chunk = ChunksToInsert[i];
			if (chunk == nullptr) { continue; }
			if (!(chunk -> GraphicsExist)) { continue; }
			VectorU3 u = relative(chunk -> Index);
			if ((u < Chunks.Size()).Any(false)) { continue; }
			if (Chunks[u] != nullptr) { continue; }
			Chunks[u] = chunk;
			ChunksToInsert.RemoveAt(i);
			i--;
		}
		ChunksToInsertLock.AssignU(sw2, TimeUpdateInsert);
	}

//	std::cout << "UpdateChunksContainer:" << __LINE__ << '\n';
//	ChunksLock.AccessU(sw, TimeUpdate);
	ChunksLock.AssignU(sw, TimeUpdate);
//	std::cout << "UpdateChunksContainer:" << __LINE__ << '\n';
}



ChunkNeighbour ChunkManager::FindNeighbours(const Chunk & chunk) const
{
	ChunkNeighbour neighbours;
	neighbours.Here = (Chunk*)&chunk;

	VectorU3 udx;
	udx = relative(chunk.Index - VectorI3(1, 0, 0)); if (Chunks.Check(udx)) { neighbours.PrevX = Chunks[udx]; } else  { neighbours.PrevX = nullptr; }
	udx = relative(chunk.Index - VectorI3(0, 1, 0)); if (Chunks.Check(udx)) { neighbours.PrevY = Chunks[udx]; } else  { neighbours.PrevY = nullptr; }
	udx = relative(chunk.Index - VectorI3(0, 0, 1)); if (Chunks.Check(udx)) { neighbours.PrevZ = Chunks[udx]; } else  { neighbours.PrevZ = nullptr; }
	udx = relative(chunk.Index + VectorI3(1, 0, 0)); if (Chunks.Check(udx)) { neighbours.NextX = Chunks[udx]; } else  { neighbours.NextX = nullptr; }
	udx = relative(chunk.Index + VectorI3(0, 1, 0)); if (Chunks.Check(udx)) { neighbours.NextY = Chunks[udx]; } else  { neighbours.NextY = nullptr; }
	udx = relative(chunk.Index + VectorI3(0, 0, 1)); if (Chunks.Check(udx)) { neighbours.NextZ = Chunks[udx]; } else  { neighbours.NextZ = nullptr; }

	return neighbours;
}
/*const Chunk * ChunkManager::NeighbourLoopChunk(const Chunk & chunk, VectorU3 & udx, AxisRel axis)
{
	unsigned int n = CHUNK_VALUES_PER_SIDE - 1;
	const Chunk * ptr = &chunk;
	//ChunksLock.AccessL();
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
	//ChunksLock.AccessU();
	return ptr;
}*/

void ChunkManager::NeighbourUpdateBufferMain(VectorI3 idx)
{
	Chunk * chunk;
	chunk = Chunks[relative(idx)]; if (chunk != nullptr) { chunk -> MainBufferState = BufferDataState::Needed; }

	VectorU3 udx;
	udx = relative(idx - VectorI3(1, 0, 0)); if (Chunks.Check(udx)) { chunk = Chunks[udx]; if (chunk != nullptr) { chunk -> MainBufferState = BufferDataState::Needed; } }
	udx = relative(idx - VectorI3(0, 1, 0)); if (Chunks.Check(udx)) { chunk = Chunks[udx]; if (chunk != nullptr) { chunk -> MainBufferState = BufferDataState::Needed; } }
	udx = relative(idx - VectorI3(0, 0, 1)); if (Chunks.Check(udx)) { chunk = Chunks[udx]; if (chunk != nullptr) { chunk -> MainBufferState = BufferDataState::Needed; } }
	udx = relative(idx + VectorI3(1, 0, 0)); if (Chunks.Check(udx)) { chunk = Chunks[udx]; if (chunk != nullptr) { chunk -> MainBufferState = BufferDataState::Needed; } }
	udx = relative(idx + VectorI3(0, 1, 0)); if (Chunks.Check(udx)) { chunk = Chunks[udx]; if (chunk != nullptr) { chunk -> MainBufferState = BufferDataState::Needed; } }
	udx = relative(idx + VectorI3(0, 0, 1)); if (Chunks.Check(udx)) { chunk = Chunks[udx]; if (chunk != nullptr) { chunk -> MainBufferState = BufferDataState::Needed; } }

//	if (Here  != nullptr) { Here  -> MainBufferState = BufferDataState::Needed; }
//	if (PrevX != nullptr) { PrevX -> MainBufferState = BufferDataState::Needed; }
//	if (PrevY != nullptr) { PrevY -> MainBufferState = BufferDataState::Needed; }
//	if (PrevZ != nullptr) { PrevZ -> MainBufferState = BufferDataState::Needed; }
//	if (NextX != nullptr) { NextX -> MainBufferState = BufferDataState::Needed; }
//	if (NextY != nullptr) { NextY -> MainBufferState = BufferDataState::Needed; }
//	if (NextZ != nullptr) { NextZ -> MainBufferState = BufferDataState::Needed; }
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
		if (!(chunk -> GenerationDone())) { chunk -> AccessU(); return GridCast3D::Hit(); }
		if ((chunk -> IsEmpty())) { chunk -> AccessU(); continue; }
		GridCast3D::Hit hit = hit_ray(*chunk, data.Ray(), data.Limit());
		chunk -> AccessU();
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
	ChunksLock.AccessL();
//	std::cout << "HitVoxel:" << __LINE__ << '\n';
	GridCast3D::Hit _hit = hit_ray(*this, ray, 10.0f);
//	std::cout << "HitVoxel:" << __LINE__ << '\n';
	ChunksLock.AccessU();
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





Chunk * ChunkManager::FindGenerateChunk()
{
	StopWatch sw;
//	std::cout << "FindGenerateChunk:" << __LINE__ << '\n';
	ChunksLock.AccessL(sw, TimeGenerateFind);
//	std::cout << "FindGenerateChunk:" << __LINE__ << '\n';

	Chunk * found = nullptr;
	float dist;
	for (unsigned int i = 0; i < Chunks.Length(); i++)
	{
		if (Chunks[i] == nullptr)
		{ continue; }

		Chunk & chunk = *Chunks[i];

//		std::cout << "FindGenerateChunk:" << __LINE__ << '\n';
		chunk.AssignL();
//		std::cout << "FindGenerateChunk:" << __LINE__ << '\n';

		if (chunk.GenerationDone())
		{ chunk.AssignU(); continue; }

		if (!CareBox.IntersectVecInclusive(chunk.Index).All(true))
		{ chunk.AssignU(); continue; }

		VectorF3 rel = chunk.Index - Center;
		float d = rel.length2();
		if (found == nullptr || d < dist)
		{
			if (found != nullptr) { found -> AssignU(); }
			found = &chunk;
			dist = d;
		}
		else { chunk.AssignU(); }
	}

//	std::cout << "FindGenerateChunk:" << __LINE__ << '\n';
	ChunksLock.AccessU(sw, TimeGenerateFind);
//	std::cout << "FindGenerateChunk:" << __LINE__ << '\n';

	return found;
}
void ChunkManager::GenerateAround(const Perlin2D & noise2, const Perlin3D & noise3)
{
	//for (unsigned int c = 0; c < count; c++)
	{
//		std::cout << "GenerateAround:" << __LINE__ << '\n';
		Chunk * chunk = FindGenerateChunk();
//		std::cout << "GenerateAround:" << __LINE__ << '\n';
		if (chunk == nullptr) { return; }
//		std::cout << "GenerateAround:" << __LINE__ << '\n';

		StopWatch sw;
		sw.Start();
		chunk -> GenerateTerrain(noise2, noise3);
		chunk -> GenerateDecorationNotes(noise2, noise3);
		chunk -> GenerateDecorationPlace();
		sw.Stop();
		TimeGenerate.DoTime.NewValue(sw.ElapsedTime());
		TimeGenerate.ThreadName = ThreadInfo::ThreadName;

		chunk -> AssignU();
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
	BufferU.Create();
	BufferF.Create();
	Texture.Create();

//	std::cout << "GraphicsCreate:" << __LINE__ << '\n';
	ChunksLock.AccessL();
//	std::cout << "GraphicsCreate:" << __LINE__ << '\n';
	for (unsigned int i = 0; i < Chunks.Length(); i++)
	{
		if (Chunks[i] == nullptr) { continue; }
		Chunks[i] -> GraphicsCreate();
	}
//	std::cout << "GraphicsCreate:" << __LINE__ << '\n';
	ChunksLock.AccessU();
//	std::cout << "GraphicsCreate:" << __LINE__ << '\n';

	BufferU_AttributesBound = false;
	{
		// Container::Void to Container::Array
		// Container::Void constructor(size, data)

		std::cout << " Error: " << GL::GetError() << '\n';
		BufferU.Bind();
		unsigned int size = 1024 * 256;
		std::cout << " Error: " << GL::GetError() << '\n';
		BufferU.MainBuffer.DataFull(size * sizeof(VoxelGraphics::MainFaceU));
		std::cout << " Error: " << GL::GetError() << '\n';
		//void * ptr = BufferU.MainBuffer.DataMap();
		std::cout << " Error: " << GL::GetError() << '\n';

		void * ptr = new VoxelGraphics::MainFaceU[size];
		BufferU_Array = Container::Array<VoxelGraphics::MainFaceU>(size, (VoxelGraphics::MainFaceU*)ptr);

		if (ptr != (void*)BufferU_Array.Memory())
		{ std::cerr << "!!!! POINTER CAST DIFFERANCE !!!!" << '\n'; }
	}

	GraphicsExist = true;
}
void ChunkManager::GraphicsDelete()
{
	if (!GraphicsExist) { return; }

	ShaderU.Delete();
	ShaderF.Delete();
	BufferU.Delete();
	BufferF.Delete();
	Texture.Delete();

//	std::cout << "GraphicsDelete:" << __LINE__ << '\n';
	ChunksLock.AccessL();
//	std::cout << "GraphicsDelete:" << __LINE__ << '\n';
	for (unsigned int i = 0; i < Chunks.Length(); i++)
	{
		if (Chunks[i] == nullptr) { continue; }
		Chunks[i] -> GraphicsDelete();
	}
//	std::cout << "GraphicsDelete:" << __LINE__ << '\n';
	ChunksLock.AccessU();
//	std::cout << "GraphicsDelete:" << __LINE__ << '\n';

	BufferU_Array.Clear();

	GraphicsExist = false;
}
void ChunkManager::GraphicsUpdate()
{
	if (!GraphicsExist) { return; }

//	std::cout << "GraphicsUpdate:" << __LINE__ << '\n';
	{
		StopWatch sw;
		ChunksToRemoveLock.AccessL(sw, TimeGraphicsDelete);
//		std::cout << "GraphicsUpdate:" << __LINE__ << '\n';
		for (unsigned int i = 0; i < ChunksToRemove.Count(); i++)
		{
			Chunk * chunk = ChunksToRemove[i];
			if (chunk == nullptr) { continue; }
			chunk -> GraphicsDelete();
		}
//		std::cout << "GraphicsUpdate:" << __LINE__ << '\n';
		ChunksToRemoveLock.AccessU(sw, TimeGraphicsDelete);
	}
//	std::cout << "GraphicsUpdate:" << __LINE__ << '\n';
	{
		StopWatch sw;
		ChunksToInsertLock.AccessL(sw, TimeGraphicsCreate);
//		std::cout << "GraphicsUpdate:" << __LINE__ << '\n';
		for (unsigned int i = 0; i < ChunksToInsert.Count(); i++)
		{
			Chunk * chunk = ChunksToInsert[i];
			if (chunk == nullptr) { continue; }
			chunk -> GraphicsCreate();
		}
//		std::cout << "GraphicsUpdate:" << __LINE__ << '\n';
		ChunksToInsertLock.AccessU(sw, TimeGraphicsCreate);
	}
//	std::cout << "GraphicsUpdate:" << __LINE__ << '\n';
}



Chunk * ChunkManager::FindGraphicsUpdateChunk()
{
	StopWatch sw;
//	std::cout << "FindGraphicsUpdateChunk:" << __LINE__ << '\n';
	ChunksLock.AccessL(sw, TimeBuffersFind);
//	std::cout << "FindGraphicsUpdateChunk:" << __LINE__ << '\n';

	Chunk * found = nullptr;
	float dist;
	for (unsigned int i = 0; i < Chunks.Length(); i++)
	{
		if (Chunks[i] == nullptr) { continue; }
		Chunk & chunk = *Chunks[i];

//		std::cout << "FindGraphicsUpdateChunk:" << __LINE__ << '\n';
		chunk.AccessL();
//		std::cout << "FindGraphicsUpdateChunk:" << __LINE__ << '\n';

		if (!chunk.GenerationDone())
		{ chunk.AccessU(); continue; }

		if (chunk.MainBufferState != BufferDataState::Needed)
		{ chunk.AccessU(); continue; }

		VectorF3 rel = chunk.Index - Center;
		float d = rel.length2();
		if (found == nullptr || d < dist)
		{
			if (found != nullptr) { found -> AccessU(); }
			found = &chunk;
			dist = d;
		}
		else { chunk.AccessU(); }
	}

//	std::cout << "FindGraphicsUpdateChunk:" << __LINE__ << '\n';
	ChunksLock.AccessU(sw, TimeBuffersFind);
//	std::cout << "FindGraphicsUpdateChunk:" << __LINE__ << '\n';

	return found;
}
void ChunkManager::GraphicsUpdateDataAround()
{
	//for (unsigned int c = 0; c < count; c++)
	{
		//std::cout << "GraphicsUpdateDataAround:" << __LINE__ << '\n';
		Chunk * chunk = FindGraphicsUpdateChunk();
		//std::cout << "GraphicsUpdateDataAround:" << __LINE__ << '\n';
		//if (chunk == nullptr) { break; }
		if (chunk == nullptr) { return; }
		//std::cout << "GraphicsUpdateDataAround:" << __LINE__ << '\n';

		/* Lock
			lock Neighbours so they dont change while making Buffer
			have a ContainerLock instead of muted ?

			deleting
			when chunk is about to be deleten, it is no longer in Chunks
			but in ChunkDisposal

			Generation is also supposed to lock Chunks from changing
			so they might deadlock ?
		*/
		/*
			0	1	2	3
			4	5	6	7
			8	9	A	B
			C	D	E	F
			9 wants 8 A 5 D to make Buffer
			6 wants 1 2 3 5 7 9 A B to generate

			9 locks 9
			9 locks 8
			9 locks A
			6 locks 6
			6 locks 1
			6 locks 2
			6 locks 3
			6 locks 5
			6 locks 7
			6 tries to lock 9, which is locked by 9
			9 tries to lock 5, which is locked by 6

			lock locking ?
			9 locks locking
			9 locks 9
			9 locks 8
			9 locks A
			6 wants to lock, but that is locked so it cant
			9 locks 5
			9 locks D
			9 makes Buffer
			9 unlocks 8
			9 unlocks A
			9 unlocks 5
			9 unlocks D
			9 unlocks locking

			should locking be unlocked before unlocking chunks ?

			this means that 6 has to wait for 9
			which might be slow ?
			generation dosent need to modify neighbours ?
			only the chunk being generated is modified

			checking can be done at the same time
		*/

		ChunksLock.AccessL();
		ChunkNeighbour neighbours = FindNeighbours(*chunk);
		ChunksLock.AccessU();

		StopWatch sw;
		sw.Start();
		chunk -> GraphicsMakeData(neighbours);
		sw.Stop();
		TimeBuffers.DoTime.NewValue(sw.ElapsedTime());
		TimeBuffers.ThreadName = ThreadInfo::ThreadName;

		chunk -> AccessU();
	}
}

void ChunkManager::Draw()
{
	if (!GraphicsExist) { return; }

	StopWatch sw;
//	std::cout << "Draw:" << __LINE__ << '\n';
	ChunksLock.AccessL(sw, TimeDraw);
//	std::cout << "Draw:" << __LINE__ << '\n';

	ShaderU.Bind();
	Texture.Bind();
	for (unsigned int i = 0; i < Chunks.Length(); i++)
	{
		if (Chunks[i] == nullptr) { continue; }
		Chunks[i] -> DrawU();
	}

	BufferU.Bind();
	//if (!BufferU_AttributesBound)
	{
		BufferU.MainBuffer.Init();
		BufferU_AttributesBound = true;
	}

	BufferU.Bind();
	for (unsigned int i = 0; i < BufferU_Entrys.Count(); i++)
	{
		ChunkDataUEntry & entry = *BufferU_Entrys[i];
		GL::DrawArrays(GL::DrawMode::Triangles, entry.Offset * 6, entry.Length * 6);
	}

	/*ShaderF.Bind();
	Texture.Bind();
	for (unsigned int i = 0; i < Chunks.Length(); i++)
	{
		if (Chunks[i] == nullptr) { continue; }
		Chunks[i] -> DrawF();
	}*/

//	std::cout << "Draw:" << __LINE__ << '\n';
	ChunksLock.AccessU(sw, TimeDraw);
//	std::cout << "Draw:" << __LINE__ << '\n';
}
