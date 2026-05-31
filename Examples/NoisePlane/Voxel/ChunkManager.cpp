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



// Code
#include "Telemetry/AuxThreadBase.hpp"
#include "Telemetry/WaitDoTime.hpp"
#include "ContainerLock.hpp"

#include "ValueType/LoopU3.hpp"



WaitDoTime ChunkManager::TimeInsert("TimeInsert");
WaitDoTime ChunkManager::TimeInsertNew("TimeInsertNew");
WaitDoTime ChunkManager::TimeInsertPut("TimeInsertPut");
WaitDoTime ChunkManager::TimeRemove("TimeRemove");
WaitDoTime ChunkManager::TimeUpdate("TimeUpdate");
WaitDoTime ChunkManager::TimeUpdateInsert("TimeUpdateInsert");
WaitDoTime ChunkManager::TimeUpdateRemove("TimeUpdateRemove");
WaitDoTime ChunkManager::TimeGraphicsCreate("TimeGraphicsCreate");
WaitDoTime ChunkManager::TimeGraphicsDelete("TimeGraphicsDelete");
WaitDoTime ChunkManager::TimeDraw("TimeDraw");





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
	InsertAround();
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

	InsertAround();
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

/* insert new directly into Chunks
	Gathering0 and New are slow because they iterate over all chunks
	just loop over it once, insert any gaps
	then dont loop again until Center changes or something else

	Insert new directly into Chunks
	use ChunksToInsert as a list of Chunks that need Graphics/Neighbours Created
*/
// just do this once when Center changes
// doing all this whenever Center changes might be slow
// only need to do it once, whenever Center changes
// use CenterIndexLoop ? then inster Chunks over time
/* Thread
	find chunk that needs to be inserted
	insert that one
	repert

	maybe remember where last chunk was to waste less time
*/
void ChunkManager::InsertAround()
{
	StopWatch sw_total;
	sw_total.Start();

	StopWatch sw;
	Container::Binary<VectorI3> new_chunks;



	sw.Clear(); sw.Start();
	ChunksLock.AccessL();
	sw.Stop(); TimeInsertNew.WaitTime.NewValue(sw.ElapsedTime());

	sw.Clear(); sw.Start();
	LoopI3 loop(CareBox.Min, Bool3(false), CareBox.Max, Bool3(false));
	for (VectorI3 i = loop.Min(); loop.Check(i).All(true); loop.Next(i))
	{
		VectorU3 u = relative(i);
		if (Chunks[u] != nullptr) { continue; }
		new_chunks.Insert(i);
	}

	ChunksLock.AccessU();
	sw.Stop(); TimeInsertNew.DoTime.NewValue(sw.ElapsedTime());



	sw.Clear(); sw.Start();
	ChunksLock.AccessL();
	ChunksToInsertLock.AssignL();
	sw.Stop(); TimeInsertPut.WaitTime.NewValue(sw.ElapsedTime());
	
	sw.Clear(); sw.Start();
	for (unsigned int i = 0; i < new_chunks.Count(); i++)
	{
		VectorU3 u = relative(new_chunks[i]);
		Chunk * chunk = new Chunk(new_chunks[i], *this);
		Chunks[u] = chunk;
		ChunksToInsert.Insert(chunk);

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
	}

	ChunksToInsertLock.AssignU();
	ChunksLock.AccessU();
	sw.Stop(); TimeInsertPut.DoTime.NewValue(sw.ElapsedTime());



	//StopWatch sw_;

	//VectorU3 box_size = CareBox.Size() + 1;

	//Array3D<Chunk*> arr(box_size, nullptr);

//	std::cout << "InsertAround:" << __LINE__ << '\n';

	/*ChunksLock.AccessL(sw_, TimeInsertGather0);
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
	ChunksLock.AccessU(sw_, TimeInsertGather0);*/

//	std::cout << "InsertAround:" << __LINE__ << '\n';

	/*ChunksToInsertLock.AccessL(sw_, TimeInsertGather1);
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
	ChunksToInsertLock.AccessU(sw_, TimeInsertGather1);*/

//	std::cout << "InsertAround:" << __LINE__ << '\n';

	/*ChunksToInsertLock.AssignL(sw_, TimeInsertNew);
	LoopI3 loop(CareBox.Min, Bool3(false), CareBox.Max, Bool3(false));
	for (VectorI3 i = loop.Min(); loop.Check(i).All(true); loop.Next(i))
	{
		unsigned int j = box_size.Convert(i - CareBox.Min);
		if (arr[j] == nullptr)
		{
			ChunksToInsert.Insert(new Chunk(i, *this));
		}
	}
	ChunksToInsertLock.AssignU(sw_, TimeInsertNew);*/

//	std::cout << "InsertAround:" << __LINE__ << '\n';
	sw_total.Stop(); TimeInsert.DoTime.NewValue(sw_total.ElapsedTime());
	TimeInsert.ThreadName = AuxThreadBase::ThreadName;
}
void ChunkManager::RemoveAround()
{
	// this is done in ChangeCenter
	// make a function for removing Chunks
	// make that function ClearNeighbours of that Chunk

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
	TimeRemove.ThreadName = AuxThreadBase::ThreadName;

	sw.Clear();
	sw.Start();

//	std::cout << "RemoveAround:" << __LINE__ << '\n';
	for (unsigned int i = 0; i < Chunks.Length(); i++)
	{
		Chunk * chunk = Chunks[i];
		if (chunk == nullptr) { continue; }
		if (KnowBox.IntersectVecInclusive(chunk -> Index).All(true)) { continue; }

		Chunks[i] = nullptr;

		// Clear Neighbours
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
			//if (Chunks[u] != nullptr) { continue; }
			//Chunks[u] = chunk;

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





ChunkManager::~ChunkManager()
{
	for (unsigned int i = 0; i < Chunks.Length(); i++)
	{
		delete Chunks[i];
	}
}
ChunkManager::ChunkManager()
	: Texture()
	, ShaderU()
	, ShaderLayoutU()
	, BufferU()
	, Chunks()
	, ChunksLock()
	, GraphicsExist(false)
	, AuxThread1(*this)
{
	ShaderU.UniformLayout = &ShaderLayoutU;
	ShaderLayoutU.Shader = &ShaderU;
}



#include "VoxelHit.hpp"
VoxelHit ChunkManager::HitVoxel(Ray3D ray)
{
	//::ViewRayPolyHedra = ViewRayPolyHedra;
	//::VoxelBoxPolyHedra = VoxelBoxPolyHedra;
	//::ChunkBoxPolyHedra = ChunkBoxPolyHedra;
	//ShowRay(ray);
//	std::cout << "HitVoxel:" << __LINE__ << '\n';
	ChunksLock.AccessL();
//	std::cout << "HitVoxel:" << __LINE__ << '\n';
	GridCast3D::Hit _hit = VoxelHit::Hit(*this, ray, 10.0f);
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

	CenterIndexLoop3D	loop = GenerateChunkFindLoop;
	GenerateChunkFindCandidateCount = 0;
	for (loop.New(CareSize); !loop.Done(); loop.Continue())
	{
		Chunk * ptr = Chunks[relative(loop.Index())];
		if (ptr == nullptr) { continue; }
		const Chunk & ref = *ptr;

		ptr -> AccessL();
		if (ref.TerrainDone && ref.DecorationsGenerated) { ptr -> AccessU(); GenerateChunkFindLoop = loop; continue; }
		//if (!CareBox.IntersectVecInclusive(ref.Index).All(true)) { ptr -> AccessU(); continue; }

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
	unsigned int candidate_count = 0;
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

		candidate_count++;
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
	AssambleChunkFindCandidateCount = candidate_count;

	//return found;
	return AccessLockedChunk(found);
}





void ChunkManager::GraphicsCreate()
{
	if (GraphicsExist) { return; }

	Texture.Create();
	ShaderU.Create();
	BufferU.Buffer.Create();
//	ShaderF.Create();
//	BufferF.Create();

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

	Texture.Delete();
	ShaderU.Delete();
	BufferU.Buffer.Delete();
//	ShaderF.Delete();
//	BufferF.Delete();

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



	sw_part.Clear(); sw_part.Start();
	BufferDataHaveQueueMutex.lock();
	for (unsigned int i = 0; i < BufferDataHaveQueue.Count(); i++)
	{
		Chunk * ptr = BufferDataHaveQueue[i];
		if (ptr == nullptr) { continue; }
		const Chunk & ref = *ptr;
		if (!ref.BufferUData_Have) { continue; }
		ptr -> BufferUData_Update();
	}
	BufferDataHaveQueue.Clear();
	BufferDataHaveQueueMutex.unlock();
	sw_part.Stop(); DrawUpdateBind.NewValue(sw_part.ElapsedTime());



	sw_part.Clear(); sw_part.Start();
	BufferU.Draw();
	sw_part.Stop(); DrawBufferDraw.NewValue(sw_part.ElapsedTime());



	//std::cout << ThreadInfo::ThreadName << " Draw " << __LINE__ << '\n';
	ChunksLock.AccessU(sw, TimeDraw);
	//std::cout << ThreadInfo::ThreadName << " Draw " << __LINE__ << '\n';



	sw_total.Stop(); DrawTotal.NewValue(sw_total.ElapsedTime());
}
