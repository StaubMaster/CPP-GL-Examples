#include "ChunkManager.hpp"

#include "ValueType/Bool3.hpp"
#include "ValueType/BoxI3.hpp"
#include "ValueType/LoopI3.hpp"

//#include "ValueType/UndexBox2D.hpp"
//#include "ValueType/UndexLoop2D.hpp"



ChunkManager::~ChunkManager() { }
ChunkManager::ChunkManager()
	: Shader()
	, Chunks()
	, ShouldGenerate(true)
	, GraphicsExist(false)
{ }



unsigned int ChunkManager::FindChunkUndex(Chunk * chunk) const
{
	for (unsigned int i = 0; i < Chunks.Count(); i++)
	{
		if (Chunks[i] == chunk)
		{
			return i;
		}
	}
	return 0xFFFFFFFF;
}
unsigned int ChunkManager::FindChunkUndex(VectorI3 idx) const
{
	for (unsigned int i = 0; i < Chunks.Count(); i++)
	{
		if (((*Chunks[i]).Index == idx).All(true))
		{
			return i;
		}
	}
	return 0xFFFFFFFF;
}
Chunk * ChunkManager::FindChunkOrNull(VectorI3 idx) const
{
	for (unsigned int i = 0; i < Chunks.Count(); i++)
	{
		if (((*Chunks[i]).Index == idx).All(true))
		{
			return Chunks[i];
		}
	}
	return nullptr;
}



void ChunkManager::Clear()
{
	for (unsigned int i = 0; i < Chunks.Count(); i++)
	{
		delete Chunks[i];
	}
	Chunks.Clear();
}
void ChunkManager::UpdateAround(const Perlin2D & noise, VectorF3 pos)
{
	VectorF3 r = (pos / (CHUNK_VALUES_PER_SIDE * CHUNK_SCALE)).roundF();
	VectorI3 idx(r);

	VectorI3 size(2);
	BoxI3 box(idx - size, idx + size);
	LoopI3 loop(box.Min, box.Max);
	for (VectorI3 i = loop.Min(); loop.Check(i).All(true); loop.Next(i))
	{
		Generate(noise, i);
	}
}

void ChunkManager::Generate(const Perlin2D & noise, VectorI3 idx)
{
	if (!ShouldGenerate) { return; }

	Chunk * chunk = FindChunkOrNull(idx);
	if (chunk == nullptr)
	{
		chunk = new Chunk();
		chunk -> Index = idx;
		chunk -> Generate(noise);

		Chunks.Insert(chunk);
		NeighbourInsert(*chunk);

		chunk -> Buffer.Main.Pos.Change(0);
		chunk -> Buffer.Main.Col.Change(1);
		chunk -> Buffer.Inst.Pos.Change(2);
		if (GraphicsExist)
		{
			chunk -> GraphicsCreate();
		}
	}
}

void ChunkManager::NeighbourInsert(Chunk & chunk)
{
	ChunkNeighbours & neighbours = chunk.Neighbours;
	neighbours.Here = &chunk;
	{
		neighbours.NextX = FindChunkOrNull(VectorI3(chunk.Index.X + 1, chunk.Index.Y, chunk.Index.Z));
		neighbours.NextY = FindChunkOrNull(VectorI3(chunk.Index.X, chunk.Index.Y + 1, chunk.Index.Z));
		neighbours.NextZ = FindChunkOrNull(VectorI3(chunk.Index.X, chunk.Index.Y, chunk.Index.Z + 1));
		neighbours.PrevX = FindChunkOrNull(VectorI3(chunk.Index.X - 1, chunk.Index.Y, chunk.Index.Z));
		neighbours.PrevY = FindChunkOrNull(VectorI3(chunk.Index.X, chunk.Index.Y - 1, chunk.Index.Z));
		neighbours.PrevZ = FindChunkOrNull(VectorI3(chunk.Index.X, chunk.Index.Y, chunk.Index.Z - 1));
	}
	{
		if (neighbours.NextX != nullptr) { neighbours.NextX -> Neighbours.PrevX = &chunk; }
		if (neighbours.NextY != nullptr) { neighbours.NextY -> Neighbours.PrevY = &chunk; }
		if (neighbours.NextZ != nullptr) { neighbours.NextZ -> Neighbours.PrevZ = &chunk; }
		if (neighbours.PrevX != nullptr) { neighbours.PrevX -> Neighbours.NextX = &chunk; }
		if (neighbours.PrevY != nullptr) { neighbours.PrevY -> Neighbours.NextY = &chunk; }
		if (neighbours.PrevZ != nullptr) { neighbours.PrevZ -> Neighbours.NextZ = &chunk; }
	}
	{
		if (neighbours.Here  != nullptr) { neighbours.Here  -> MainBufferNeedsData = true; }
		if (neighbours.NextX != nullptr) { neighbours.NextX -> MainBufferNeedsData = true; }
		if (neighbours.NextY != nullptr) { neighbours.NextY -> MainBufferNeedsData = true; }
		if (neighbours.NextZ != nullptr) { neighbours.NextZ -> MainBufferNeedsData = true; }
		if (neighbours.PrevX != nullptr) { neighbours.PrevX -> MainBufferNeedsData = true; }
		if (neighbours.PrevY != nullptr) { neighbours.PrevY -> MainBufferNeedsData = true; }
		if (neighbours.PrevZ != nullptr) { neighbours.PrevZ -> MainBufferNeedsData = true; }
	}
}



void ChunkManager::GraphicsCreate()
{
	if (GraphicsExist) { return; }

	Shader.Create();
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
	for (unsigned int i = 0; i < Chunks.Count(); i++)
	{
		(*Chunks[i]).GraphicsDelete();
	}

	GraphicsExist = false;
}

void ChunkManager::Draw()
{
	if (!GraphicsExist) { return; }

	Shader.Bind();
	for (unsigned int i = 0; i < Chunks.Count(); i++)
	{
		(*Chunks[i]).Draw();
	}
}
