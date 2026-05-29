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
WaitDoTime ChunkManager::TimeGraphicsCreate("TimeGraphicsCreate");
WaitDoTime ChunkManager::TimeGraphicsDelete("TimeGraphicsDelete");
WaitDoTime ChunkManager::TimeDraw("TimeDraw");





bool MultiBuffe_ChunkU::Entry::IsEmpty() const
{
	return (Offset == 0 && Length == 0);
}
void MultiBuffe_ChunkU::Entry::MakeEmpty()
{
	Offset = 0;
	Length = 0;
}
void MultiBuffe_ChunkU::Entry::Put(const Container::Array<VoxelGraphics::MainFaceU> & data)
{
	Buffer.Remove(*this);
	Length = data.Length();
	Buffer.Insert(*this);
	if (!IsEmpty())
	{
		Buffer.Buffer.MainBuffer.DataPart(Offset * sizeof(VoxelGraphics::MainFaceU), data.ToVoid());
	}
}

MultiBuffe_ChunkU::Entry::~Entry()
{
	Buffer.Remove(*this);
}
MultiBuffe_ChunkU::Entry::Entry(MultiBuffe_ChunkU & buffer)
	: Buffer(buffer)
	, Offset(0)
	, Length(0)
{ }

void MultiBuffe_ChunkU::NewSize(unsigned int size)
{
	Buffer.MainBuffer.DataFull(size);
	Size = size / sizeof(VoxelGraphics::MainFaceU);
}

bool MultiBuffe_ChunkU::CheckEntry(Entry & entry)
{
	if ((entry.Offset + entry.Length) >= Size)
	{
		return false;
	}
	for (unsigned int i = 0; i < Entrys.Count(); i++)
	{
		Entry & other = *(Entrys[i]);
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
void MultiBuffe_ChunkU::Insert(Entry & entry)
{
	if (entry.Length == 0)
	{
		entry.MakeEmpty();
		return;
	}

	entry.Offset = 0;
	if (CheckEntry(entry))
	{
		Entrys.Insert(&entry);
		Offsets.Insert(entry.Offset * 6);
		Lengths.Insert(entry.Length * 6);
		//std::cout << "insert BufferUEntry of Length: " << entry.Length << " at " << entry.Offset << '\n';
		return;
	}

	for (unsigned int i = 0; i < Entrys.Count(); i++)
	{
		Entry & other = *(Entrys[i]);
		entry.Offset = other.Offset + other.Length;
		if (CheckEntry(entry))
		{
			Entrys.Insert(&entry);
			Offsets.Insert(entry.Offset * 6);
			Lengths.Insert(entry.Length * 6);
			//std::cout << "insert BufferUEntry of Length: " << entry.Length << " at " << entry.Offset << '\n';
			return;
		}
	}

	std::cout << " failed BufferUEntry of Length: " << entry.Length << '\n';

	entry.MakeEmpty();
}
void MultiBuffe_ChunkU::Remove(Entry & entry)
{
	if (entry.IsEmpty())
	{
		return;
	}
	for (unsigned int i = 0; i < Entrys.Count(); i++)
	{
		if (Entrys[i] == &entry)
		{
			Entrys.RemoveAt(i);
			Offsets.RemoveAt(i);
			Lengths.RemoveAt(i);
			break;
		}
	}
	//std::cout << "remove BufferUEntry of Length: " << entry.Length << " at " << entry.Offset << '\n';
	entry.MakeEmpty();
}
void MultiBuffe_ChunkU::Draw()
{
	Buffer.Bind();
	Buffer.MainBuffer.Update();
	glMultiDrawArrays((unsigned int)GL::DrawMode::Triangles, Offsets.ToArray().Memory(), Lengths.ToArray().Memory(), Entrys.Count());
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
void ChunkManager::ChangeCenter(VectorI3 center)
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

Chunk * ChunkManager::FindAbsOrNull(VectorI3 idx)
{
	VectorU3 udx = relative(idx);
	if (Chunks.Check(udx))
	{
		return Chunks[udx];
	}
	return nullptr;
}
AccessLockedChunk ChunkManager::FindAccess(VectorI3 idx)
{
	VectorU3 udx = relative(idx);
	if ((udx < Chunks.Size()).Any(false)) { return AccessLockedChunk(); }
	return AccessLockedChunk(Chunks[udx]);
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

		for (int z = 0; z < 3; z++)
		{
			for (int y = 0; y < 3; y++)
			{
				for (int x = 0; x < 3; x++)
				{
					if (x != 1 || y != 1 || z != 1)
					{
						if (chunk -> Neighbours.Cube[z][y][x] != nullptr)
						{
							chunk -> Neighbours.Cube[z][y][x] -> Neighbours.Cube[2 - z][2 - y][2 - x] = nullptr;
						}
							chunk -> Neighbours.Cube[z][y][x] = nullptr;
					}
				}
			}
		}

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

/* how to safely delete

*/
void ChunkManager::UpdateChunksContainer()
{
	StopWatch sw;
//	std::cout << "UpdateChunksContainer:" << __LINE__ << '\n';
	ChunksLock.AccessL(sw, TimeUpdate);
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
			if (chunk -> InUse()) { continue; }
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
		bool inserted = false;
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
			chunk -> Neighbours = ChunkNeighbour(*chunk);

			for (int z = 0; z < 3; z++)
			{
				for (int y = 0; y < 3; y++)
				{
					for (int x = 0; x < 3; x++)
					{
						if (x != 1 || y != 1 || z != 1)
						{
								chunk -> Neighbours.Cube[z][y][x] = FindAbsOrNull(chunk -> Index + VectorI3(x - 1, y - 1, z - 1));
							if (chunk -> Neighbours.Cube[z][y][x] != nullptr)
							{
								chunk -> Neighbours.Cube[z][y][x] -> Neighbours.Cube[2 - z][2 - y][2 - x] = chunk;
							}
						}
					}
				}
			}

			inserted = true;
			ChunksToInsert.RemoveAt(i);
			i--;
		}
		ChunksToInsertLock.AssignU(sw2, TimeUpdateInsert);

		if (inserted)
		{
			GenerateChunkConditionVar.notify_all();
			AssambleChunkConditionVar.notify_all();
		}
	}

//	std::cout << "UpdateChunksContainer:" << __LINE__ << '\n';
	ChunksLock.AccessU(sw, TimeUpdate);
//	std::cout << "UpdateChunksContainer:" << __LINE__ << '\n';
}



void ChunkManager::NeighbourUpdateBufferMain(VectorI3 idx)
{
	Chunk * Here  = FindAbsOrNull(idx);
	Chunk * PrevX = FindAbsOrNull(idx - VectorI3(1, 0, 0));
	Chunk * PrevY = FindAbsOrNull(idx - VectorI3(0, 1, 0));
	Chunk * PrevZ = FindAbsOrNull(idx - VectorI3(0, 0, 1));
	Chunk * NextX = FindAbsOrNull(idx + VectorI3(1, 0, 0));
	Chunk * NextY = FindAbsOrNull(idx + VectorI3(0, 1, 0));
	Chunk * NextZ = FindAbsOrNull(idx + VectorI3(0, 0, 1));

	if (Here  != nullptr) { Here  -> BufferUData_Want = true; }
	if (PrevX != nullptr) { PrevX -> BufferUData_Want = true; }
	if (PrevY != nullptr) { PrevY -> BufferUData_Want = true; }
	if (PrevZ != nullptr) { PrevZ -> BufferUData_Want = true; }
	if (NextX != nullptr) { NextX -> BufferUData_Want = true; }
	if (NextY != nullptr) { NextY -> BufferUData_Want = true; }
	if (NextZ != nullptr) { NextZ -> BufferUData_Want = true; }

	MakeBufferConditionVar.notify_all();
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
	, ShaderLayoutU()
//	, ShaderF()
//	, ShaderLayoutF()
//	, ChunksArray()
//	, ChunksBox()
	, Chunks()
	, ChunksLock()
//	, ChunksChanging()
//	, ChunksChecking()
//	, ChunksCheckingCount()
	, GraphicsExist(false)
{
	ShaderU.UniformLayout = &ShaderLayoutU;
	ShaderLayoutU.Shader = &ShaderU;

//	ShaderF.UniformLayout = &ShaderLayoutF;
//	ShaderLayoutF.Shader = &ShaderF;
}



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

static GridCast3D::Hit hit_ray(const Chunk & chunk, Ray3D ray3D, float limit)
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
		AccessLockedChunk chunk = manager.FindAccess(data.Index());
		if (!chunk.Is()) { return GridCast3D::Hit(); }
		if (!((*chunk).GenerationDone())) { return GridCast3D::Hit(); }
		if (((*chunk).IsEmpty())) { continue; }
		GridCast3D::Hit hit = hit_ray(*chunk, data.Ray(), data.Limit());
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



#include "ValueType/Vector/I2.hpp"

struct CenterIndexLoop2D
{
	unsigned int	Limit;

	bool			Done;
	unsigned int	Size;
	unsigned char	Control;
	VectorI2		Index;

	void New(unsigned int layer)
	{
		Size = layer;
		if (Limit * 2 < Size)
		{
			Done = true;
			return;
		}

		if (Limit >= Size)
		{
			Index = VectorI2(-Size, 0);
		}
		else
		{
			Index = VectorI2(-Limit, +Size - Limit);
		}

		Control = 0;
		Done = false;
	}
	void Continue()
	{
		if (Index.X == 0 && Index.Y == 0) { Done = true; }

		if (Control == 0)
		{
			if (Index.X == 0)
			{
				Control = 1;
				Index.X++;
				Index.Y--;
			}
			else if (Index.Y == +(int)Limit)
			{
				Control = 1;
				Index.X = -Index.X;
			}
			else
			{
				Index.X++;
				Index.Y++;
			}
		}
		else if (Control == 1)
		{
			if (Index.Y == 0)
			{
				Control = 2;
				Index.X--;
				Index.Y--;
			}
			else if (Index.X == +(int)Limit)
			{
				Control = 2;
				Index.Y = -Index.Y;
			}
			else
			{
				Index.X++;
				Index.Y--;
			}
		}
		else if (Control == 2)
		{
			if (Index.X == 0)
			{
				Control = 3;
				Index.X--;
				Index.Y++;
			}
			else if (Index.Y == -(int)Limit)
			{
				Control = 3;
				Index.X = -Index.X;
			}
			else
			{
				Index.X--;
				Index.Y--;
			}
		}
		else
		{
			if (Index.Y == 0)
			{
				Control = 0;
				Index.X++;
				Index.Y++;
				Done = true;
			}
			else if (Index.X == -(int)Limit)
			{
				Control = 0;
				Index.Y = -Index.Y;
				Done = true;
			}
			else
			{
				Index.X--;
				Index.Y++;
			}
		}

		if (Control == 3 && Index.Y == 0) { Done = true; }
	}
};
struct CenterIndexLoop3D
{
unsigned int		Limit;

CenterIndexLoop2D	Layer0;

bool				Layer1Done;
unsigned int		Layer1Size;
unsigned char		Layer1Control;
VectorI2			Layer1Index;

void Layer1New(unsigned int layer)
{
	Layer1Size = layer;

	Layer1Index = VectorI2(-Layer1Size, 0);

	if (Limit >= Layer1Size)
	{
		Layer1Index = VectorI2(-Layer1Size, 0);
	}
	else
	{
		Layer1Index = VectorI2(-Limit, +Layer1Size - Limit);
	}

	Layer1Control = 0;
	Layer1Done = false;
}
void Layer1Loop()
{
	if (Layer1Index.X == 0 && Layer1Index.Y == 0) { Layer1Done = true; }

	if (Layer1Control == 0)
	{
		if (Layer1Index.X == 0)
		{
			Layer1Control = 1;
			Layer1Index.X++;
			Layer1Index.Y--;
		}
		else if (Limit * 2 <= (unsigned int)Layer1Index.Y)
		{
			Layer1Control = 1;
			Layer1Index.X = -Layer1Index.X;
		}
		else
		{
			Layer1Index.X++;
			Layer1Index.Y++;
		}
	}
	else if (Layer1Control == 1)
	{
		if (Layer1Index.Y == 0)
		{
			Layer1Control = 0;
			Layer1Index.X--;
			Layer1Index.Y--;
			Layer1Done = true;
		}
		else if (Layer1Index.X == +(int)Limit)
		{
			Layer1Control = 0;
			Layer1Index.Y = -Layer1Index.Y;
			Layer1Done = true;
		}
		else
		{
			Layer1Index.X++;
			Layer1Index.Y--;
		}
	}
}

bool Done() const
{
	return (Layer0.Done || Layer1Done);
}
VectorI3 Index() const
{
	return VectorI3(Layer0.Index.X, Layer0.Index.Y, Layer1Index.X);
}

void New(unsigned int limit)
{
	Limit = limit;
	Layer0.Limit = Limit;

	Layer1New(0);
	Layer0.New(Layer1Index.Y);
}
void Continue()
{
	if (!Layer0.Done)
	{
		Layer0.Continue();
		if (Layer0.Done)
		{
			if (!Layer1Done)
			{
				Layer1Loop();
				if (Layer1Done)
				{
					Layer1New(Layer1Size + 1);
				}
				Layer0.New(Layer1Index.Y);
			}
		}
	}
}
};



AccessLockedChunk ChunkManager::GenerateChunkFind()
{
	/* loop takes longer the longer it goes on
		save what chunks are fully complete
		then start at the end of those
		reset when Center changes ?
		what if a random chunk needs to be regenerated ?
		just reset and loop over everything again
		it would only need to loop once, which should be fine
	*/

	CenterIndexLoop3D	loop;
	for (loop.New(CareSize); !loop.Done(); loop.Continue())
	{
		Chunk * ptr = Chunks[relative(loop.Index())];
		if (ptr == nullptr) { continue; }
		const Chunk & ref = *ptr;

		ptr -> AccessL();
		if (ref.TerrainDone && ref.DecorationsGenerated) { ptr -> AccessU(); continue; }
		if (!CareBox.IntersectVecInclusive(ref.Index).All(true)) { ptr -> AccessU(); continue; }

		return AccessLockedChunk(ptr);
	}
	return AccessLockedChunk();

//	AccessLockedChunk found;
	Chunk * found = nullptr;
	float dist;
	for (unsigned int i = 0; i < Chunks.Length(); i++)
	{
		Chunk * ptr = Chunks[i];
		if (ptr == nullptr) { continue; }
		const Chunk & ref = *ptr;

		//AccessLockedChunk chunk = ptr -> ToAccess();
		ptr -> AccessL();

		if (ref.TerrainDone && ref.DecorationsGenerated) { ptr -> AccessU(); continue; }
		if (!CareBox.IntersectVecInclusive(ref.Index).All(true)) { ptr -> AccessU(); continue; }

		VectorF3 rel = ref.Index - Center;
		float d = rel.length2();
		//if (!found.Is() || d < dist)
		if (found == nullptr || d < dist)
		{
			if (found != nullptr) { found -> AccessU(); }
			found = ptr;
			dist = d;
		}
		else { ptr -> AccessU(); }
	}

	//return found;
	return AccessLockedChunk(found);
}

AccessLockedChunk ChunkManager::AssambleChunkFind()
{
	/*CenterIndexLoop3D	loop;
	for (loop.New(CareSize); !loop.Done(); loop.Continue())
	{
		Chunk * ptr = Chunks[relative(loop.Index())];
		if (ptr == nullptr) { continue; }
		const Chunk & ref = *ptr;

		ptr -> AccessL();
		if (ref.TerrainDone && ref.DecorationsGenerated) { ptr -> AccessU(); continue; }
		if (!CareBox.IntersectVecInclusive(ref.Index).All(true)) { ptr -> AccessU(); continue; }

		return AccessLockedChunk(ptr);
	}
	return AccessLockedChunk();*/

//	AccessLockedChunk found;
	Chunk * found = nullptr;
	float dist;
	for (unsigned int i = 0; i < Chunks.Length(); i++)
	{
		Chunk * ptr = Chunks[i];
		if (ptr == nullptr) { continue; }
		const Chunk & ref = *ptr;

		//AccessLockedChunk chunk = ptr -> ToAccess();
		ptr -> AccessL();

		if (!ref.TerrainDone || !ref.DecorationsGenerated || ref.DecorationsAssambled) { ptr -> AccessU(); continue; }
		if (!CareBox.IntersectVecInclusive(ref.Index).All(true)) { ptr -> AccessU(); continue; }
		if (!ref.Neighbours.CanAssamble()) { ptr -> AccessU(); continue; }

		VectorF3 rel = ref.Index - Center;
		float d = rel.length2();
		//if (!found.Is() || d < dist)
		if (found == nullptr || d < dist)
		{
			if (found != nullptr) { found -> AccessU(); }
			//found = chunk;
			found = ptr;
			dist = d;
		}
		else { ptr -> AccessU(); }
	}

	//return found;
	return AccessLockedChunk(found);
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
//	ShaderF.Create();
	BufferU.Buffer.Create();
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

	BufferU.Buffer.MainBuffer.AttributesBound = false;
	BufferU.NewSize(1024 * 1024 * 1024);
	// Container::Void to Container::Array
	// Container::Void constructor(size, data)

	GraphicsExist = true;
}
void ChunkManager::GraphicsDelete()
{
	if (!GraphicsExist) { return; }

	ShaderU.Delete();
//	ShaderF.Delete();
	BufferU.Buffer.Delete();
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

	BufferU.Size = 0;

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



AccessLockedChunk ChunkManager::MakeBufferFind()
{
	StopWatch sw;

	//std::cout << ThreadInfo::ThreadName << " FindGraphicsUpdateChunk " << __LINE__ << '\n';

	AccessLockedChunk found;
	float dist;
	for (unsigned int i = 0; i < Chunks.Length(); i++)
	{
		Chunk * ptr = Chunks[i];
		if (ptr == nullptr) { continue; }
		AccessLockedChunk chunk = ptr -> ToAccessTry();
		if (!chunk.Is()) { continue; }
		if (!(*chunk).BufferUData_Want) { continue; }
		if (!(*chunk).GenerationDone()) { continue; }
		if (!(*chunk).Neighbours.CanMakeBuffer()) { continue; }

		VectorF3 rel = (*chunk).Index - Center;
		float d = rel.length2();
		if (!found.Is() || d < dist)
		{
			found = chunk;
			dist = d;
		}
	}

	//std::cout << ThreadInfo::ThreadName << " FindGraphicsUpdateChunk " << __LINE__ << '\n';

	return found;
}



ValueAverager<float> ChunkManager::DrawTotal(64);
ValueAverager<float> ChunkManager::DrawWait(64);
ValueAverager<float> ChunkManager::DrawTextureBind(64);
ValueAverager<float> ChunkManager::DrawShaderBind(64);
ValueAverager<float> ChunkManager::DrawUpdateBind(64);
ValueAverager<float> ChunkManager::DrawBufferDraw(64);

void ChunkManager::Draw()
{
	if (!GraphicsExist) { return; }

	StopWatch sw_total;
	sw_total.Start();

	StopWatch sw_part;



	StopWatch sw;

	sw_part.Clear(); sw_part.Start();
	//std::cout << ThreadInfo::ThreadName << " Draw " << __LINE__ << '\n';
	ChunksLock.AccessL(sw, TimeDraw);
	//std::cout << ThreadInfo::ThreadName << " Draw " << __LINE__ << '\n';
	sw_part.Stop(); DrawWait.NewValue(sw_part.ElapsedTime());



	sw_part.Clear(); sw_part.Start();
	Texture.Bind();
	sw_part.Stop(); DrawTextureBind.NewValue(sw_part.ElapsedTime());



	sw_part.Clear(); sw_part.Start();
	ShaderU.Bind();
	sw_part.Stop(); DrawShaderBind.NewValue(sw_part.ElapsedTime());



	/* Update is slow
		even when nothing is updated, so the loop is slow
		maybe have a Queue of Chunks that need to Update
		then go through that, then cleare it
		a Queue might also help with some other things
	*/
	sw_part.Clear(); sw_part.Start();
	BufferUpdateU_Queue_Mutex.lock();
	for (unsigned int i = 0; i < BufferUpdateU_Queue.Count(); i++)
	{
		Chunk * ptr = BufferUpdateU_Queue[i];
		if (ptr == nullptr) { continue; }
		if (!ptr -> BufferUData_Have) { continue; }
		ptr -> BufferUData_Update();
	}
	BufferUpdateU_Queue_Mutex.unlock();
	BufferUpdateU_Queue.Clear();
	sw_part.Stop(); DrawUpdateBind.NewValue(sw_part.ElapsedTime());



	sw_part.Clear(); sw_part.Start();
	BufferU.Draw();
	sw_part.Stop(); DrawBufferDraw.NewValue(sw_part.ElapsedTime());



	//std::cout << ThreadInfo::ThreadName << " Draw " << __LINE__ << '\n';
	ChunksLock.AccessU(sw, TimeDraw);
	//std::cout << ThreadInfo::ThreadName << " Draw " << __LINE__ << '\n';



	sw_total.Stop(); DrawTotal.NewValue(sw_total.ElapsedTime());
}
