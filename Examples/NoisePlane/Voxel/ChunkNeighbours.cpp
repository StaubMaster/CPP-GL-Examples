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



bool ChunkNeighbours::Visible(Axis dir, VectorU3 udx) const
{
	Chunk * chunk = nullptr;

	if (dir == Axis::NextX)
	{
		if (udx.X != CHUNK_VALUES_PER_SIDE - 1)
		{ chunk = Here; udx.X++; }
		else
		{ chunk = NextX; udx.X = 0; }
	}
	if (dir == Axis::NextY)
	{
		if (udx.Y != CHUNK_VALUES_PER_SIDE - 1)
		{ chunk = Here; udx.Y++; }
		else
		{ chunk = NextY; udx.Y = 0; }
	}
	if (dir == Axis::NextZ)
	{
		if (udx.Z != CHUNK_VALUES_PER_SIDE - 1)
		{ chunk = Here; udx.Z++; }
		else
		{ chunk = NextZ; udx.Z = 0; }
	}

	if (dir == Axis::PrevX)
	{
		if (udx.X != 0)
		{ chunk = Here; udx.X--; }
		else
		{ chunk = PrevX; udx.X = CHUNK_VALUES_PER_SIDE - 1; }
	}
	if (dir == Axis::PrevY)
	{
		if (udx.Y != 0)
		{ chunk = Here; udx.Y--; }
		else
		{ chunk = PrevY; udx.Y = CHUNK_VALUES_PER_SIDE - 1; }
	}
	if (dir == Axis::PrevZ)
	{
		if (udx.Z != 0)
		{ chunk = Here; udx.Z--; }
		else
		{ chunk = PrevZ; udx.Z = CHUNK_VALUES_PER_SIDE - 1; }
	}

	Voxel * val = nullptr;
	if (chunk != nullptr && chunk -> Data != nullptr)
	{
		if (chunk -> ChunkType == ChunkType::Filled)
		{
			val = &(*chunk)[udx];
		}
		if (chunk -> ChunkType == ChunkType::Empty)
		{
			val = (*chunk).Data;
		}
	}

	if (val == nullptr) { return false; }
	if (val -> Template == nullptr) { return true; }

	switch (dir)
	{
		case Axis::PrevX: return !(val -> Template -> HideNextX);
		case Axis::PrevY: return !(val -> Template -> HideNextY);
		case Axis::PrevZ: return !(val -> Template -> HideNextZ);
		case Axis::NextX: return !(val -> Template -> HidePrevX);
		case Axis::NextY: return !(val -> Template -> HidePrevY);
		case Axis::NextZ: return !(val -> Template -> HidePrevZ);
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
