#include "ChunkNeighbours.hpp"
#include "Chunk.hpp"
#include "VoxelEnums.hpp"

#include "ValueType/Vector/U3.hpp"



#define n CHUNK_VALUES_PER_SIDE - 1



const Chunk * ChunkNeighbour::LoopPrevX(VectorU3 & udx) const { if (udx.X != 0) { udx.X--; return Here; } else { udx.X = n; return PrevX; } }
const Chunk * ChunkNeighbour::LoopPrevY(VectorU3 & udx) const { if (udx.Y != 0) { udx.Y--; return Here; } else { udx.Y = n; return PrevY; } }
const Chunk * ChunkNeighbour::LoopPrevZ(VectorU3 & udx) const { if (udx.Z != 0) { udx.Z--; return Here; } else { udx.Z = n; return PrevZ; } }
const Chunk * ChunkNeighbour::LoopNextX(VectorU3 & udx) const { if (udx.X != n) { udx.X++; return Here; } else { udx.X = 0; return NextX; } }
const Chunk * ChunkNeighbour::LoopNextY(VectorU3 & udx) const { if (udx.Y != n) { udx.Y++; return Here; } else { udx.Y = 0; return NextY; } }
const Chunk * ChunkNeighbour::LoopNextZ(VectorU3 & udx) const { if (udx.Z != n) { udx.Z++; return Here; } else { udx.Z = 0; return NextZ; } }

const Chunk * ChunkNeighbour::Loop(VectorU3 & udx, AxisRel axis) const
{
	switch (axis)
	{
		case AxisRel::Here: return Here;
		case AxisRel::PrevX: return LoopPrevX(udx);
		case AxisRel::PrevY: return LoopPrevY(udx);
		case AxisRel::PrevZ: return LoopPrevZ(udx);
		case AxisRel::NextX: return LoopNextX(udx);
		case AxisRel::NextY: return LoopNextY(udx);
		case AxisRel::NextZ: return LoopNextZ(udx);
		case AxisRel::None: return nullptr;
	}
	return nullptr;
}



bool ChunkNeighbour::Visible(VectorU3 udx, AxisRel axis) const
{
	const Chunk * chunk = Loop(udx, axis);
	if (chunk != Here)
	{
		if (chunk == nullptr) { return false; }
		if (!chunk -> GenerationDone()) { return false; }
		if (chunk -> IsEmpty()) { return true; }
	}
	const Voxel & voxel = (*chunk)[udx];
	return voxel.Visible(axis);
}
