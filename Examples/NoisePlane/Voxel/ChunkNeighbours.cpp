#include "ChunkNeighbours.hpp"
#include "Chunk.hpp"
#include "Voxel.hpp"
#include "VoxelOrientation.hpp"
#include "VoxelPallet.hpp"



bool ChunkNeighbours::Done() const { return (Here != nullptr); }



ChunkNeighbours::~ChunkNeighbours() { }
ChunkNeighbours::ChunkNeighbours()
	: Here(nullptr)
	, PrevX(nullptr)
	, PrevY(nullptr)
	, PrevZ(nullptr)
	, NextX(nullptr)
	, NextY(nullptr)
	, NextZ(nullptr)
{ }
ChunkNeighbours::ChunkNeighbours(const ChunkNeighbours & other)
	: Here(other.Here)
	, PrevX(other.PrevX)
	, PrevY(other.PrevY)
	, PrevZ(other.PrevZ)
	, NextX(other.NextX)
	, NextY(other.NextY)
	, NextZ(other.NextZ)
{ }
ChunkNeighbours & ChunkNeighbours::operator=(const ChunkNeighbours & other)
{
	Here = other.Here;
	PrevX = other.PrevX;
	PrevY = other.PrevY;
	PrevZ = other.PrevZ;
	NextX = other.NextX;
	NextY = other.NextY;
	NextZ = other.NextZ;
	return *this;
}



const Chunk * ChunkNeighbours::Loop(AxisRel axis, VectorU3 & udx) const
{
	unsigned int n = CHUNK_VALUES_PER_SIDE - 1;
	switch (axis)
	{
		case AxisRel::None: return nullptr;
		case AxisRel::PrevX: if (udx.X != 0) { udx.X--; return Here; } else { udx.X = n; return PrevX; }
		case AxisRel::PrevY: if (udx.Y != 0) { udx.Y--; return Here; } else { udx.Y = n; return PrevY; }
		case AxisRel::PrevZ: if (udx.Z != 0) { udx.Z--; return Here; } else { udx.Z = n; return PrevZ; }
		case AxisRel::NextX: if (udx.X != n) { udx.X++; return Here; } else { udx.X = 0; return NextX; }
		case AxisRel::NextY: if (udx.Y != n) { udx.Y++; return Here; } else { udx.Y = 0; return NextY; }
		case AxisRel::NextZ: if (udx.Z != n) { udx.Z++; return Here; } else { udx.Z = 0; return NextZ; }
		case AxisRel::Here: return Here;
	}
	return nullptr;
}



void ChunkNeighbours::Change(AxisRel axis, Chunk * chunk)
{
	switch (axis)
	{
		case AxisRel::Here:  Here  = chunk; break;
		case AxisRel::PrevX: PrevX = chunk; break;
		case AxisRel::PrevY: PrevY = chunk; break;
		case AxisRel::PrevZ: PrevZ = chunk; break;
		case AxisRel::NextX: NextX = chunk; break;
		case AxisRel::NextY: NextY = chunk; break;
		case AxisRel::NextZ: NextZ = chunk; break;
		default: break;
	}
	if (axis == AxisRel::Here)
	{
		if (PrevX != nullptr) { PrevX -> Neighbours.NextX = Here; }
		if (PrevY != nullptr) { PrevY -> Neighbours.NextY = Here; }
		if (PrevZ != nullptr) { PrevZ -> Neighbours.NextZ = Here; }
		if (NextX != nullptr) { NextX -> Neighbours.PrevX = Here; }
		if (NextY != nullptr) { NextY -> Neighbours.PrevY = Here; }
		if (NextZ != nullptr) { NextZ -> Neighbours.PrevZ = Here; }
	}
}

void ChunkNeighbours::UpdateBufferMain()
{
	if (Here  != nullptr) { Here  -> MainBufferState = BufferDataState::Needed; }
	if (PrevX != nullptr) { PrevX -> MainBufferState = BufferDataState::Needed; }
	if (PrevY != nullptr) { PrevY -> MainBufferState = BufferDataState::Needed; }
	if (PrevZ != nullptr) { PrevZ -> MainBufferState = BufferDataState::Needed; }
	if (NextX != nullptr) { NextX -> MainBufferState = BufferDataState::Needed; }
	if (NextY != nullptr) { NextY -> MainBufferState = BufferDataState::Needed; }
	if (NextZ != nullptr) { NextZ -> MainBufferState = BufferDataState::Needed; }
}
