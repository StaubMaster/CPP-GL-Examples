#include "ChunkNeighbours.hpp"
#include "Chunk.hpp"
#include "VoxelEnums.hpp"

#include "ValueType/Vector/U3.hpp"



const Chunk * ChunkNeighbour::Loop(VectorU3 & udx, AxisRel axis) const
{
	const unsigned int n = CHUNK_VALUES_PER_SIDE - 1;
	switch (axis)
	{
		case AxisRel::Here: return Here;
		case AxisRel::PrevX: if (udx.X != 0) { udx.X--; return Here; } else { udx.X = n; return PrevX; }
		case AxisRel::PrevY: if (udx.Y != 0) { udx.Y--; return Here; } else { udx.Y = n; return PrevY; }
		case AxisRel::PrevZ: if (udx.Z != 0) { udx.Z--; return Here; } else { udx.Z = n; return PrevZ; }
		case AxisRel::NextX: if (udx.X != n) { udx.X++; return Here; } else { udx.X = 0; return NextX; }
		case AxisRel::NextY: if (udx.Y != n) { udx.Y++; return Here; } else { udx.Y = 0; return NextY; }
		case AxisRel::NextZ: if (udx.Z != n) { udx.Z++; return Here; } else { udx.Z = 0; return NextZ; }
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
