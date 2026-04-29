#include "ChunkNeighbours.hpp"
#include "Chunk.hpp"
#include "Voxel.hpp"
#include "VoxelOrientation.hpp"
#include "VoxelTemplate.hpp"



ChunkNeighbours::~ChunkNeighbours() { }
ChunkNeighbours::ChunkNeighbours()
	: Here(nullptr)
	, NextX(nullptr)
	, NextY(nullptr)
	, NextZ(nullptr)
	, PrevX(nullptr)
	, PrevY(nullptr)
	, PrevZ(nullptr)
{ }
ChunkNeighbours::ChunkNeighbours(const ChunkNeighbours & other)
	: Here(other.Here)
	, NextX(other.NextX)
	, NextY(other.NextY)
	, NextZ(other.NextZ)
	, PrevX(other.PrevX)
	, PrevY(other.PrevY)
	, PrevZ(other.PrevZ)
{ }
ChunkNeighbours & ChunkNeighbours::operator=(const ChunkNeighbours & other)
{
	Here = other.Here;
	NextX = other.NextX;
	NextY = other.NextY;
	NextZ = other.NextZ;
	PrevX = other.PrevX;
	PrevY = other.PrevY;
	PrevZ = other.PrevZ;
	return *this;
}



bool ChunkNeighbours::Visible(AxisRel axis, VectorU3 udx) const
{
	unsigned int n = CHUNK_VALUES_PER_SIDE - 1;

	Chunk * chunk = nullptr;
	switch (axis)
	{
		case AxisRel::None: return false;
		case AxisRel::PrevX: if (udx.X != 0) { chunk = Here; udx.X--; } else { chunk = PrevX; udx.X = n; } break;
		case AxisRel::PrevY: if (udx.Y != 0) { chunk = Here; udx.Y--; } else { chunk = PrevY; udx.Y = n; } break;
		case AxisRel::PrevZ: if (udx.Z != 0) { chunk = Here; udx.Z--; } else { chunk = PrevZ; udx.Z = n; } break;
		case AxisRel::NextX: if (udx.X != n) { chunk = Here; udx.X++; } else { chunk = NextX; udx.X = 0; } break;
		case AxisRel::NextY: if (udx.Y != n) { chunk = Here; udx.Y++; } else { chunk = NextY; udx.Y = 0; } break;
		case AxisRel::NextZ: if (udx.Z != n) { chunk = Here; udx.Z++; } else { chunk = NextZ; udx.Z = 0; } break;
		case AxisRel::Here: return true;
	}
	if (chunk == nullptr) { return false; }
	if (!chunk -> Done()) { return false; }

	if (chunk -> IsEmpty()) { return true; }
	Voxel & voxel = (*chunk)[udx];
	if (voxel.Template == nullptr) { return true; }

	return voxel.Template -> Visible(voxel.Orientation.relative(axis));
}

void ChunkNeighbours::UpdateOthersHere()
{
	if (NextX != nullptr) { NextX -> Neighbours.PrevX = Here; }
	if (NextY != nullptr) { NextY -> Neighbours.PrevY = Here; }
	if (NextZ != nullptr) { NextZ -> Neighbours.PrevZ = Here; }
	if (PrevX != nullptr) { PrevX -> Neighbours.NextX = Here; }
	if (PrevY != nullptr) { PrevY -> Neighbours.NextY = Here; }
	if (PrevZ != nullptr) { PrevZ -> Neighbours.NextZ = Here; }
}

void ChunkNeighbours::UpdateBufferMain()
{
	if (Here  != nullptr) { Here  -> MainBufferState = Chunk::BufferDataState::Needed; }
	if (NextX != nullptr) { NextX -> MainBufferState = Chunk::BufferDataState::Needed; }
	if (NextY != nullptr) { NextY -> MainBufferState = Chunk::BufferDataState::Needed; }
	if (NextZ != nullptr) { NextZ -> MainBufferState = Chunk::BufferDataState::Needed; }
	if (PrevX != nullptr) { PrevX -> MainBufferState = Chunk::BufferDataState::Needed; }
	if (PrevY != nullptr) { PrevY -> MainBufferState = Chunk::BufferDataState::Needed; }
	if (PrevZ != nullptr) { PrevZ -> MainBufferState = Chunk::BufferDataState::Needed; }
}
