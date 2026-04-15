#include "ChunkNeighbours.hpp"
#include "Voxel.hpp"
#include "Chunk.hpp"



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

Voxel * ChunkNeighbours::Value(AxisDirection dir, VectorU3 udx) const
{
	Chunk * chunk = nullptr;

	if (dir == AxisDirection::NextX)
	{
		if (udx.X != CHUNK_VALUES_PER_SIDE - 1)
		{ chunk = Here; udx.X++; }
		else
		{ chunk = NextX; udx.X = 0; }
	}
	if (dir == AxisDirection::NextY)
	{
		if (udx.Y != CHUNK_VALUES_PER_SIDE - 1)
		{ chunk = Here; udx.Y++; }
		else
		{ chunk = NextY; udx.Y = 0; }
	}
	if (dir == AxisDirection::NextZ)
	{
		if (udx.Z != CHUNK_VALUES_PER_SIDE - 1)
		{ chunk = Here; udx.Z++; }
		else
		{ chunk = NextZ; udx.Z = 0; }
	}

	if (dir == AxisDirection::PrevX)
	{
		if (udx.X != 0)
		{ chunk = Here; udx.X--; }
		else
		{ chunk = PrevX; udx.X = CHUNK_VALUES_PER_SIDE - 1; }
	}
	if (dir == AxisDirection::PrevY)
	{
		if (udx.Y != 0)
		{ chunk = Here; udx.Y--; }
		else
		{ chunk = PrevY; udx.Y = CHUNK_VALUES_PER_SIDE - 1; }
	}
	if (dir == AxisDirection::PrevZ)
	{
		if (udx.Z != 0)
		{ chunk = Here; udx.Z--; }
		else
		{ chunk = PrevZ; udx.Z = CHUNK_VALUES_PER_SIDE - 1; }
	}

	Voxel * val = nullptr;
	if (chunk != nullptr && chunk -> IsGenerated)
	{
		val = &(*chunk)[udx];
	}
	return val;
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
