#include "Manager.hpp"
#include "Neighbours.hpp"
#include "Chunk.hpp"

#include "Voxel.hpp"

#include "Axis/Orientation.hpp"

#include "ChunkVoxelIndex.hpp"

#include "ValueType/Bool/3.hpp"
#include "ValueType/Box/I3.hpp"
#include "ValueType/Loop/I3.hpp"

#include "ValueType/Ray/F3.hpp"



// Code
#include "AuxThreadBase.hpp"
#include "Telemetry/WaitDoTime.hpp"

#include "ContainerLock/Lock.hpp"
#include "ContainerLock/AccessTypeGuard.hpp"
#include "ContainerLock/AssignTypeGuard.hpp"

#include "ValueType/Loop/U3.hpp"



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
		//Chunks[i] -> GraphicsDelete();
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
	if (Chunks.Check(udx))
	{
		Chunk * chunk = Chunks[udx];
		if (chunk != nullptr)
		{
			return chunk -> ToAccess();
		}
	}
	return AccessLockedChunk();
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

	std::cout << "newChunk: " << new_chunks.Count() << '\n';
	if (new_chunks.Count() != 0)
	{
		AuxThread2.FindLoop = CenterIndexLoop3D();
		AuxThread2.Poke();
	}

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

	//std::cout << "UpdateChunksContainer:" << __LINE__ << '\n';
	ChunksLock.AccessL(sw, TimeUpdate);
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
			AuxThread2.Poke();
			AuxThread3.Poke();
		}
	}

	//std::cout << "UpdateChunksContainer:" << __LINE__ << '\n';
	ChunksLock.AccessU(sw, TimeUpdate);
	//std::cout << "UpdateChunksContainer:" << __LINE__ << '\n';
}





ChunkManager::~ChunkManager()
{
	for (unsigned int i = 0; i < Chunks.Length(); i++)
	{
		delete Chunks[i];
	}
}
ChunkManager::ChunkManager()
	: Chunks()
	, ChunksLock()
	, AuxThread1(*this)
	, AuxThread2(*this)
	, AuxThread3(*this)
	, GraphicsExist(false)
	, Texture()
	, ShaderU()
	, ShaderF()
	, ShaderLayoutU()
	, ShaderLayoutF()
	, BufferU()
	, BufferF()
	, BufferLayoutU()
	, BufferLayoutF()
{ }



#include "VoxelHit.hpp"
VoxelHit ChunkManager::HitVoxel(RayF3 ray)
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
	if (_hit.cardinal == AxisRel::None) { return hit; }
	//std::cout << "HitVoxel:" << __LINE__ << '\n';
	hit.Side = _hit.cardinal;
	hit.Index = _hit.idx;
	hit.Position = _hit.pos;
	hit.Normal = AxisToVector(_hit.cardinal);
	//std::cout << "HitVoxel:" << __LINE__ << '\n';

	return hit;
}



#include "Graphics/Shader/Code.hpp"
#include "DirectoryInfo.hpp"
void ChunkManager::ChangeMedia(const DirectoryInfo & dir)
{
	ShaderU.Change({
		dir.File("Shaders/Voxel/VoxelU.vert"),
		dir.File("Shaders/Voxel/Voxel.frag"),
	});
	ShaderU.UniformLayout = &ShaderLayoutU;
	ShaderLayoutU.Shader = &ShaderU;

	ShaderF.Change({
		dir.File("Shaders/Voxel/VoxelF.vert"),
		dir.File("Shaders/Voxel/Voxel.frag"),
	});
	ShaderF.UniformLayout = &ShaderLayoutF;
	ShaderLayoutF.Shader = &ShaderF;

	BufferLayoutU.Voxel.Change(0);
	BufferLayoutU.Texture.Change(1);
	BufferLayoutU.Chunk.Change(2);
	BufferU.Buffer.Layout = &BufferLayoutU;

	BufferLayoutF.Pos.Change(0);
	BufferLayoutF.Tex.Change(1);
	BufferLayoutF.Normal.Change(2);
	BufferF.Buffer.Layout = &BufferLayoutF;
}

void ChunkManager::GraphicsCreate()
{
	if (GraphicsExist) { return; }

	Texture.Create();
	ShaderU.Create();
	ShaderF.Create();
	BufferU.Create();
	BufferF.Create();

	BufferU.Init();
	unsigned int count_u = 1024 * 1024 * 1024 / sizeof(VoxelGraphicsDataU::Vertex);
	BufferU.NewSize(sizeof(VoxelGraphicsDataU::Vertex), count_u);

	BufferF.Init();
	unsigned int count_f = 1024 * 1024 * 1024 / sizeof(VoxelGraphicsDataF::Vertex);
	BufferF.NewSize(sizeof(VoxelGraphicsDataF::Vertex), count_f);

	GraphicsExist = true;
}
void ChunkManager::GraphicsDelete()
{
	if (!GraphicsExist) { return; }

	Texture.Delete();
	ShaderU.Delete();
	ShaderF.Delete();
	BufferU.Delete();
	BufferF.Delete();

	BufferU.Buffer.Count = 0;
	BufferF.Buffer.Count = 0;

	GraphicsExist = false;
}



unsigned int ChunkManager::BufferHave::QueueCount()
{
	QueueMutex.lock();
	unsigned int c = Queue.Count();
	QueueMutex.unlock();
	return c;
}
void ChunkManager::BufferHave::QueuePut(Chunk * chunk)
{
	if (chunk == nullptr) { return; }

	QueueMutex.lock();

	/*for (unsigned int i = 0; i < Queue.Count(); i++)
	{
		if (Queue[i] == chunk)
		{
			QueueMutex.unlock();
			return;
		}
	}*/
	chunk -> BufferData_Have = true;
	Queue.Insert(chunk);

	QueueMutex.unlock();
}



ValueAccumulator<float> ChunkManager::DrawTotal(64);
ValueAccumulator<float> ChunkManager::DrawWait(64);
ValueAccumulator<float> ChunkManager::DrawTextureBind(64);
ValueAccumulator<float> ChunkManager::DrawShaderBind(64);
ValueAccumulator<float> ChunkManager::DrawUpdateBind(64);
ValueAccumulator<float> ChunkManager::DrawBufferDraw(64);

#include <iostream>
void ChunkManager::Draw()
{
	if (!GraphicsExist) { return; }

	StopWatch sw_total;
	sw_total.Start();

	StopWatch sw_part;



	StopWatch sw;

	sw_part.Clear();
	//std::cout << ThreadInfo::ThreadName << " Draw " << __LINE__ << '\n';
	ChunksLock.AccessL(sw, TimeDraw);
	//std::cout << ThreadInfo::ThreadName << " Draw " << __LINE__ << '\n';
	DrawWait.NewValue(sw_part.ElapsedTime());



	sw_part.Clear();
	Texture.Bind();
	DrawTextureBind.NewValue(sw_part.ElapsedTime());



	sw_part.Clear();
	BufferDataHave.QueueMutex.lock();
	for (unsigned int i = 0; i < BufferDataHave.Queue.Count(); i++)
	{
		Chunk * ptr = BufferDataHave.Queue[i];
		if (ptr == nullptr) { continue; }
		const Chunk & ref = *ptr;
		if (!ref.BufferData_Have) { continue; }
		ptr -> BufferData_Update();
	}
	BufferDataHave.Queue.Clear();
	BufferDataHave.QueueMutex.unlock();
	DrawUpdateBind.NewValue(sw_part.ElapsedTime());



	sw_part.Clear();
	ShaderU.Bind();
	DrawShaderBind.NewValue(sw_part.ElapsedTime());

	sw_part.Clear();
	BufferU.Bind();
	BufferU.Draw();
	DrawBufferDraw.NewValue(sw_part.ElapsedTime());



	sw_part.Clear();
	ShaderF.Bind();
	DrawShaderBind.NewValue(sw_part.ElapsedTime());

	/*{
		std::cout << "Entrys: " << BufferF.Entrys.Count() << '\n';
		for (unsigned int i = 0; i < BufferF.Entrys.Count(); i++)
		{
			std::cout << BufferF.Entrys[i] -> Offset << ' ';
			std::cout << BufferF.Entrys[i] -> Length << '\n';
		}
		std::cout << '\n';
	}*/
	sw_part.Clear();
	BufferF.Bind();
	BufferF.Draw();
	DrawBufferDraw.NewValue(sw_part.ElapsedTime());



	//std::cout << ThreadInfo::ThreadName << " Draw " << __LINE__ << '\n';
	ChunksLock.AccessU(sw, TimeDraw);
	//std::cout << ThreadInfo::ThreadName << " Draw " << __LINE__ << '\n';



	sw_total.Stop(); DrawTotal.NewValue(sw_total.ElapsedTime());
}
