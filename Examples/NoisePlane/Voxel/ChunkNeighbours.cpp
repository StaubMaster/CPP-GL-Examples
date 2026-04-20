#include "ChunkNeighbours.hpp"
#include "Voxel.hpp"
#include "Chunk.hpp"
#include "VoxelOrientation.hpp"



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



bool ChunkNeighbours::Visible(Axis axis, VectorU3 udx) const
{
	unsigned int n = CHUNK_VALUES_PER_SIDE - 1;

	Chunk * chunk = nullptr;
	switch (axis)
	{
		case Axis::PrevX: if (udx.X != 0) { chunk = Here; udx.X--; } else { chunk = PrevX; udx.X = n; } break;
		case Axis::PrevY: if (udx.Y != 0) { chunk = Here; udx.Y--; } else { chunk = PrevY; udx.Y = n; } break;
		case Axis::PrevZ: if (udx.Z != 0) { chunk = Here; udx.Z--; } else { chunk = PrevZ; udx.Z = n; } break;
		case Axis::NextX: if (udx.X != n) { chunk = Here; udx.X++; } else { chunk = NextX; udx.X = 0; } break;
		case Axis::NextY: if (udx.Y != n) { chunk = Here; udx.Y++; } else { chunk = NextY; udx.Y = 0; } break;
		case Axis::NextZ: if (udx.Z != n) { chunk = Here; udx.Z++; } else { chunk = NextZ; udx.Z = 0; } break;
		default: break;
	}
	if (chunk == nullptr) { return false; }

	Voxel * voxel = nullptr;
	if (chunk -> Data != nullptr)
	{
		if (chunk -> ChunkType == ChunkType::Filled)
		{
			voxel = &(*chunk)[udx];
		}
		if (chunk -> ChunkType == ChunkType::Empty)
		{
			voxel = (*chunk).Data;
		}
	}
	if (voxel == nullptr) { return false; }
	if (voxel -> Template == nullptr) { return true; }

	switch (voxel -> Orientation.relative(axis))
	{
		case Axis::PrevX: return !(voxel -> Template -> HideNextX);
		case Axis::PrevY: return !(voxel -> Template -> HideNextY);
		case Axis::PrevZ: return !(voxel -> Template -> HideNextZ);
		case Axis::NextX: return !(voxel -> Template -> HidePrevX);
		case Axis::NextY: return !(voxel -> Template -> HidePrevY);
		case Axis::NextZ: return !(voxel -> Template -> HidePrevZ);
		default: return false;
	}
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
	if (Here  != nullptr) { Here  -> MainBufferNeedsData = true; }
	if (NextX != nullptr) { NextX -> MainBufferNeedsData = true; }
	if (NextY != nullptr) { NextY -> MainBufferNeedsData = true; }
	if (NextZ != nullptr) { NextZ -> MainBufferNeedsData = true; }
	if (PrevX != nullptr) { PrevX -> MainBufferNeedsData = true; }
	if (PrevY != nullptr) { PrevY -> MainBufferNeedsData = true; }
	if (PrevZ != nullptr) { PrevZ -> MainBufferNeedsData = true; }
}
