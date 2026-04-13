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

ChunkValue ChunkNeighbours::Value(AxisDirection dir, VectorU3 voxel3, unsigned int voxel) const
{
	ChunkValue val;
	val.Undex = voxel3;
	if (dir == AxisDirection::Here && Here != nullptr) { val.Change(voxel3, (*Here).Values[voxel]); }
	if (dir == AxisDirection::NextX && NextX != nullptr) { val.Change(voxel3, (*NextX).Values[voxel]); }
	if (dir == AxisDirection::NextY && NextY != nullptr) { val.Change(voxel3, (*NextY).Values[voxel]); }
	if (dir == AxisDirection::NextZ && NextZ != nullptr) { val.Change(voxel3, (*NextZ).Values[voxel]); }
	if (dir == AxisDirection::PrevX && PrevX != nullptr) { val.Change(voxel3, (*PrevX).Values[voxel]); }
	if (dir == AxisDirection::PrevY && PrevY != nullptr) { val.Change(voxel3, (*PrevY).Values[voxel]); }
	if (dir == AxisDirection::PrevZ && PrevZ != nullptr) { val.Change(voxel3, (*PrevZ).Values[voxel]); }
	return val;
}
