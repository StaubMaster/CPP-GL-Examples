#include "ChunkManager.hpp"

#include "ValueType/Bool3.hpp"
#include "ValueType/BoxI3.hpp"
#include "ValueType/LoopI2.hpp"

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
	Generate(noise, idx);

	/*unsigned int size = 1;
	BoxI2 box(idx - VectorI2(size), idx + VectorI2(size));
	LoopI2 loop(box.Min, box.Max);
	for (VectorI2 i = loop.Min(); loop.Check(i).All(true); loop.Next(i))
	{
		Generate(noise, i);
	}*/
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
		//NeighbourInsert(*chunk);
		chunk -> MainBufferNeedsData = true;

		chunk -> Buffer.Main.Pos.Change(0);
		chunk -> Buffer.Main.Col.Change(1);
		chunk -> Buffer.Inst.Pos.Change(2);
		if (GraphicsExist)
		{
			chunk -> GraphicsCreate();
		}
	}
}

/*void ChunkManager::NeighbourInsert(Chunk & Chunk)
{
	{
		Chunk * Chunks[4];

		Chunks[0b00] = FindChunkOrNull(VectorI2(Chunk.Index.X + 0, Chunk.Index.Y + 0));
		Chunks[0b01] = FindChunkOrNull(VectorI2(Chunk.Index.X + 1, Chunk.Index.Y + 0));
		Chunks[0b10] = FindChunkOrNull(VectorI2(Chunk.Index.X + 0, Chunk.Index.Y + 1));
		Chunks[0b11] = FindChunkOrNull(VectorI2(Chunk.Index.X + 1, Chunk.Index.Y + 1));

		if (Chunks[0b00] != nullptr) { Chunk.Neighbours.Chunks[0b00] = Chunks[0b00]; }
		if (Chunks[0b01] != nullptr) { Chunk.Neighbours.Chunks[0b01] = Chunks[0b01]; }
		if (Chunks[0b10] != nullptr) { Chunk.Neighbours.Chunks[0b10] = Chunks[0b10]; }
		if (Chunks[0b11] != nullptr) { Chunk.Neighbours.Chunks[0b11] = Chunks[0b11]; }
	}
	{
		Chunk * Chunks[4];

		Chunks[0b00] = FindChunkOrNull(VectorI2(Chunk.Index.X - 0, Chunk.Index.Y - 0));
		Chunks[0b01] = FindChunkOrNull(VectorI2(Chunk.Index.X - 1, Chunk.Index.Y - 0));
		Chunks[0b10] = FindChunkOrNull(VectorI2(Chunk.Index.X - 0, Chunk.Index.Y - 1));
		Chunks[0b11] = FindChunkOrNull(VectorI2(Chunk.Index.X - 1, Chunk.Index.Y - 1));

		if (Chunks[0b00] != nullptr) { Chunks[0b00] -> Neighbours.Chunks[0b00] = &Chunk; }
		if (Chunks[0b01] != nullptr) { Chunks[0b01] -> Neighbours.Chunks[0b01] = &Chunk; }
		if (Chunks[0b10] != nullptr) { Chunks[0b10] -> Neighbours.Chunks[0b10] = &Chunk; }
		if (Chunks[0b11] != nullptr) { Chunks[0b11] -> Neighbours.Chunks[0b11] = &Chunk; }

		if (Chunks[0b00] != nullptr) { Chunks[0b00] -> MainBufferNeedsData = true; }
		if (Chunks[0b01] != nullptr) { Chunks[0b01] -> MainBufferNeedsData = true; }
		if (Chunks[0b10] != nullptr) { Chunks[0b10] -> MainBufferNeedsData = true; }
		if (Chunks[0b11] != nullptr) { Chunks[0b11] -> MainBufferNeedsData = true; }
	}
}*/



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
