#include "ChunkManager.hpp"
#include "Chunk.hpp"
#include "Voxel.hpp"

#include "ValueType/Bool3.hpp"
#include "ValueType/BoxI3.hpp"
#include "ValueType/LoopI3.hpp"



ChunkManager::~ChunkManager() { }
ChunkManager::ChunkManager()
	: Shader()
	, Chunks()
	, ShouldGenerate(true)
	, GraphicsExist(false)
{ }



Voxel * ChunkManager::operator[](VectorI3 idx)
{
	VectorI3 chunk_idx = (VectorF3(idx) / (float)CHUNK_VALUES_PER_SIDE).roundF(); // make intager division round down;
	VectorU3 voxel_idx = idx - (chunk_idx * CHUNK_VALUES_PER_SIDE);

	Chunk * chunk = FindChunkOrNull(chunk_idx);
	if (chunk == nullptr) { return nullptr; }
	return &(*chunk)[voxel_idx];
}
//const Voxel * ChunkManager::operator[](VectorI3 voxel) const;



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

void ChunkManager::InsertAround(VectorF3 pos, unsigned int size)
{
	VectorI3 idx(pos.roundF() / (float)CHUNK_VALUES_PER_SIDE);

	BoxI3 box(idx - (int)size, idx + (int)size);
	LoopI3 loop(box.Min, box.Max);
	for (VectorI3 i = loop.Min(); loop.Check(i).All(true); loop.Next(i))
	{
		InsertChunk(i);
	}
}
void ChunkManager::InsertChunk(VectorI3 idx)
{
	if (!ShouldGenerate) { return; }

	Chunk * chunk = FindChunkOrNull(idx);
	if (chunk == nullptr)
	{
		chunk = new Chunk();
		chunk -> Index = idx;

		Chunks.Insert(chunk);
		NeighbourInsert(*chunk);

		chunk -> Buffer.Main.Pos.Change(0);
		chunk -> Buffer.Main.Tex.Change(1);
		chunk -> Buffer.Inst.Pos.Change(2);
		if (GraphicsExist)
		{
			chunk -> GraphicsCreate();
		}
	}
}

void ChunkManager::GenerateAround(const Perlin2D & noise, VectorF3 pos, unsigned int count)
{
	if (!ShouldGenerate) { return; }
	for (unsigned int c = 0; c < count; c++)
	{
		unsigned int idx = 0xFFFFFFFF;
		float dist;
		for (unsigned int i = 0; i < Chunks.Count(); i++)
		{
			if (Chunks[i] == nullptr) { continue; }
			Chunk & chunk = *Chunks[i];
			if (chunk.IsGenerated) { continue; }
			VectorF3 rel = ((chunk.Index + VectorF3(0.5f)) * CHUNK_VALUES_PER_SIDE) - pos;
			float d = rel.length2();
			if (idx == 0xFFFFFFFF || d < dist)
			{
				dist = d;
				idx = i;
			}
		}
		if (idx != 0xFFFFFFFF)
		{
			Chunk & chunk = *Chunks[idx];
			chunk.Generate(noise);
			chunk.Neighbours.UpdateBufferMain();
		}
		else { break; } // return instead of break ?
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
	neighbours.UpdateOthersHere();
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

void ChunkManager::Draw()
{
	if (!GraphicsExist) { return; }

	Shader.Bind();
	Texture.Bind();
	for (unsigned int i = 0; i < Chunks.Count(); i++)
	{
		(*Chunks[i]).Draw();
	}
}
