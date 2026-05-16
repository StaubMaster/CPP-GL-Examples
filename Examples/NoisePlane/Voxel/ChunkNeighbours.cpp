#include "ChunkNeighbours.hpp"
#include "Chunk.hpp"
#include "Voxel.hpp"
#include "VoxelEnums.hpp"

#include "ValueType/Vector/U3.hpp"



#define n CHUNK_VALUES_PER_SIDE - 1



const Chunk * ChunkNeighbour::LoopPrevX(VectorU3 & udx) const { if (udx.X != 0) { udx.X--; return Here; } else { udx.X = n; return PrevX; } }
const Chunk * ChunkNeighbour::LoopPrevY(VectorU3 & udx) const { if (udx.Y != 0) { udx.Y--; return Here; } else { udx.Y = n; return PrevY; } }
const Chunk * ChunkNeighbour::LoopPrevZ(VectorU3 & udx) const { if (udx.Z != 0) { udx.Z--; return Here; } else { udx.Z = n; return PrevZ; } }
const Chunk * ChunkNeighbour::LoopNextX(VectorU3 & udx) const { if (udx.X != n) { udx.X++; return Here; } else { udx.X = 0; return NextX; } }
const Chunk * ChunkNeighbour::LoopNextY(VectorU3 & udx) const { if (udx.Y != n) { udx.Y++; return Here; } else { udx.Y = 0; return NextY; } }
const Chunk * ChunkNeighbour::LoopNextZ(VectorU3 & udx) const { if (udx.Z != n) { udx.Z++; return Here; } else { udx.Z = 0; return NextZ; } }
const Chunk * ChunkNeighbour::Loop(VectorU3 & udx, const AxisRel & axis) const
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



bool ChunkNeighbour::IsVisiblePrevX(const Array3D<unsigned char> & is_empty, VectorU3 udx) const
{
	if (udx.X != 0)
	{
		udx.X--;
		return is_empty[udx];
	}
	else if (PrevX != nullptr && PrevX -> GenerationDone())
	{
		if (PrevX -> IsEmpty()) { return true; }
		udx.X = n;
		return PrevX -> Voxels[udx].IsEmpty();
	}
	return false;
}
bool ChunkNeighbour::IsVisiblePrevY(const Array3D<unsigned char> & is_empty, VectorU3 udx) const
{
	if (udx.Y != 0)
	{
		udx.Y--;
		return is_empty[udx];
	}
	else if (PrevY != nullptr && PrevY -> GenerationDone())
	{
		if (PrevY -> IsEmpty()) { return true; }
		udx.Y = n;
		return PrevY -> Voxels[udx].IsEmpty();
	}
	return false;
}
bool ChunkNeighbour::IsVisiblePrevZ(const Array3D<unsigned char> & is_empty, VectorU3 udx) const
{
	if (udx.Z != 0)
	{
		udx.Z--;
		return is_empty[udx];
	}
	else if (PrevZ != nullptr && PrevZ -> GenerationDone())
	{
		if (PrevZ -> IsEmpty()) { return true; }
		udx.Z = n;
		return PrevZ -> Voxels[udx].IsEmpty();
	}
	return false;
}
bool ChunkNeighbour::IsVisibleNextX(const Array3D<unsigned char> & is_empty, VectorU3 udx) const
{
	if (udx.X != n)
	{
		udx.X++;
		return is_empty[udx];
	}
	else if (NextX != nullptr && NextX -> GenerationDone())
	{
		if (NextX -> IsEmpty()) { return true; }
		udx.X = 0;
		return NextX -> Voxels[udx].IsEmpty();
	}
	return false;
}
bool ChunkNeighbour::IsVisibleNextY(const Array3D<unsigned char> & is_empty, VectorU3 udx) const
{
	if (udx.Y != n)
	{
		udx.Y++;
		return is_empty[udx];
	}
	else if (NextY != nullptr && NextY -> GenerationDone())
	{
		if (NextY -> IsEmpty()) { return true; }
		udx.Y = 0;
		return NextY -> Voxels[udx].IsEmpty();
	}
	return false;
}
bool ChunkNeighbour::IsVisibleNextZ(const Array3D<unsigned char> & is_empty, VectorU3 udx) const
{
	if (udx.Z != n)
	{
		udx.Z++;
		return is_empty[udx];
	}
	else if (NextZ != nullptr && NextZ -> GenerationDone())
	{
		if (NextZ -> IsEmpty()) { return true; }
		udx.Z = 0;
		return NextZ -> Voxels[udx].IsEmpty();
	}
	return false;
}
