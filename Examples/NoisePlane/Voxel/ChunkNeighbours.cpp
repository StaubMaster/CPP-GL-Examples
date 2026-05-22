#include "ChunkNeighbours.hpp"
#include "Chunk.hpp"
#include "Voxel.hpp"
#include "VoxelEnums.hpp"

#include "ValueType/Vector/U3.hpp"



#define n CHUNK_VALUES_PER_SIDE - 1



ChunkNeighbour::~ChunkNeighbour()
{ }
ChunkNeighbour::ChunkNeighbour()
	: Here(nullptr)
	, PrevX(nullptr)
	, PrevY(nullptr)
	, PrevZ(nullptr)
	, NextX(nullptr)
	, NextY(nullptr)
	, NextZ(nullptr)
{ }
ChunkNeighbour::ChunkNeighbour(const ChunkNeighbour & other)
	: Here(other.Here)
	, PrevX(other.PrevX)
	, PrevY(other.PrevY)
	, PrevZ(other.PrevZ)
	, NextX(other.NextX)
	, NextY(other.NextY)
	, NextZ(other.NextZ)
{ }
//ChunkNeighbour & ChunkNeighbour::operator=(const ChunkNeighbour & other) { }

ChunkNeighbour::ChunkNeighbour(ChunkManager & manager, Chunk * chunk)
	: Here(chunk)
	, PrevX(nullptr)
	, PrevY(nullptr)
	, PrevZ(nullptr)
	, NextX(nullptr)
	, NextY(nullptr)
	, NextZ(nullptr)
{
	VectorU3 udx;
	udx = manager.relative(chunk -> Index - VectorI3(1, 0, 0)); if (manager.Chunks.Check(udx)) { PrevX = manager.Chunks[udx]; }
	udx = manager.relative(chunk -> Index - VectorI3(0, 1, 0)); if (manager.Chunks.Check(udx)) { PrevY = manager.Chunks[udx]; }
	udx = manager.relative(chunk -> Index - VectorI3(0, 0, 1)); if (manager.Chunks.Check(udx)) { PrevZ = manager.Chunks[udx]; }
	udx = manager.relative(chunk -> Index + VectorI3(1, 0, 0)); if (manager.Chunks.Check(udx)) { NextX = manager.Chunks[udx]; }
	udx = manager.relative(chunk -> Index + VectorI3(0, 1, 0)); if (manager.Chunks.Check(udx)) { NextY = manager.Chunks[udx]; }
	udx = manager.relative(chunk -> Index + VectorI3(0, 0, 1)); if (manager.Chunks.Check(udx)) { NextZ = manager.Chunks[udx]; }
}
ChunkNeighbour::ChunkNeighbour(ChunkManager & manager, VectorI3 idx)
	: Here(nullptr)
	, PrevX(nullptr)
	, PrevY(nullptr)
	, PrevZ(nullptr)
	, NextX(nullptr)
	, NextY(nullptr)
	, NextZ(nullptr)
{
	VectorU3 udx;
	udx = manager.relative(idx); if (manager.Chunks.Check(udx)) { Here = manager.Chunks[udx]; }
	udx = manager.relative(idx - VectorI3(1, 0, 0)); if (manager.Chunks.Check(udx)) { PrevX = manager.Chunks[udx]; }
	udx = manager.relative(idx - VectorI3(0, 1, 0)); if (manager.Chunks.Check(udx)) { PrevY = manager.Chunks[udx]; }
	udx = manager.relative(idx - VectorI3(0, 0, 1)); if (manager.Chunks.Check(udx)) { PrevZ = manager.Chunks[udx]; }
	udx = manager.relative(idx + VectorI3(1, 0, 0)); if (manager.Chunks.Check(udx)) { NextX = manager.Chunks[udx]; }
	udx = manager.relative(idx + VectorI3(0, 1, 0)); if (manager.Chunks.Check(udx)) { NextY = manager.Chunks[udx]; }
	udx = manager.relative(idx + VectorI3(0, 0, 1)); if (manager.Chunks.Check(udx)) { NextZ = manager.Chunks[udx]; }
}



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



void ChunkNeighbour::UpdateVisual() const
{
	if (Here != nullptr) { Here -> MainBufferDataNew = true; }
	if (PrevX != nullptr) { PrevX -> MainBufferDataNew = true; }
	if (PrevY != nullptr) { PrevY -> MainBufferDataNew = true; }
	if (PrevZ != nullptr) { PrevZ -> MainBufferDataNew = true; }
	if (NextX != nullptr) { NextX -> MainBufferDataNew = true; }
	if (NextY != nullptr) { NextY -> MainBufferDataNew = true; }
	if (NextZ != nullptr) { NextZ -> MainBufferDataNew = true; }
}
bool ChunkNeighbour::GenerationDone() const
{
	if (Here != nullptr)  { if (!Here  -> GenerationDone()) { return false; } }
	if (PrevX != nullptr) { if (!PrevX -> GenerationDone()) { return false; } }
	if (PrevY != nullptr) { if (!PrevY -> GenerationDone()) { return false; } }
	if (PrevZ != nullptr) { if (!PrevZ -> GenerationDone()) { return false; } }
	if (NextX != nullptr) { if (!NextX -> GenerationDone()) { return false; } }
	if (NextY != nullptr) { if (!NextY -> GenerationDone()) { return false; } }
	if (NextZ != nullptr) { if (!NextZ -> GenerationDone()) { return false; } }
	return true;
}
