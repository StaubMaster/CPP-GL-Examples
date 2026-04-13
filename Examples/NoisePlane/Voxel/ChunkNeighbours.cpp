#include "ChunkNeighbours.hpp"
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

ChunkValue ChunkNeighbours::Value(AxisDirection dir, VectorU3 udx) const
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

	ChunkValue val;
	if (chunk != nullptr)
	{
		val.Change((*chunk)[udx]);
	}
	return val;
}
