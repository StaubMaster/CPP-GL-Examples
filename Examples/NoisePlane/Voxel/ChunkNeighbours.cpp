#include "ChunkNeighbours.hpp"
#include "Chunk.hpp"
#include "Voxel.hpp"
#include "VoxelEnums.hpp"

#include "ValueType/Vector/U3.hpp"



#define n CHUNK_VALUES_PER_SIDE - 1



/*
ChunkAxisNeighbour::~ChunkAxisNeighbour()
{ }
ChunkAxisNeighbour::ChunkAxisNeighbour()
	: Here(nullptr)
	, PrevX(nullptr)
	, PrevY(nullptr)
	, PrevZ(nullptr)
	, NextX(nullptr)
	, NextY(nullptr)
	, NextZ(nullptr)
{ }
ChunkAxisNeighbour::ChunkAxisNeighbour(const ChunkAxisNeighbour & other)
	: Here(other.Here)
	, PrevX(other.PrevX)
	, PrevY(other.PrevY)
	, PrevZ(other.PrevZ)
	, NextX(other.NextX)
	, NextY(other.NextY)
	, NextZ(other.NextZ)
{ }
ChunkAxisNeighbour & ChunkAxisNeighbour::operator=(const ChunkAxisNeighbour & other)
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
ChunkAxisNeighbour::ChunkAxisNeighbour(const Chunk & chunk)
	: Here(&chunk)
	, PrevX(nullptr)
	, PrevY(nullptr)
	, PrevZ(nullptr)
	, NextX(nullptr)
	, NextY(nullptr)
	, NextZ(nullptr)
{ }



void ChunkAxisNeighbour::ChangePrevX(const Chunk * chunk) { PrevX = chunk; }
void ChunkAxisNeighbour::ChangePrevY(const Chunk * chunk) { PrevY = chunk; }
void ChunkAxisNeighbour::ChangePrevZ(const Chunk * chunk) { PrevZ = chunk; }
void ChunkAxisNeighbour::ChangeNextX(const Chunk * chunk) { NextX = chunk; }
void ChunkAxisNeighbour::ChangeNextY(const Chunk * chunk) { NextY = chunk; }
void ChunkAxisNeighbour::ChangeNextZ(const Chunk * chunk) { NextZ = chunk; }



bool ChunkAxisNeighbour::IsVisiblePrevX(const Array3D<unsigned char> & is_empty, VectorU3 udx) const
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
bool ChunkAxisNeighbour::IsVisiblePrevY(const Array3D<unsigned char> & is_empty, VectorU3 udx) const
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
bool ChunkAxisNeighbour::IsVisiblePrevZ(const Array3D<unsigned char> & is_empty, VectorU3 udx) const
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
bool ChunkAxisNeighbour::IsVisibleNextX(const Array3D<unsigned char> & is_empty, VectorU3 udx) const
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
bool ChunkAxisNeighbour::IsVisibleNextY(const Array3D<unsigned char> & is_empty, VectorU3 udx) const
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
bool ChunkAxisNeighbour::IsVisibleNextZ(const Array3D<unsigned char> & is_empty, VectorU3 udx) const
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



bool ChunkAxisNeighbour::GenerationDone() const
{
	if (Here != nullptr) { if (!Here -> GenerationDone()) { return false; } }
	if (PrevX != nullptr) { if (!PrevX -> GenerationDone()) { return false; } }
	if (PrevY != nullptr) { if (!PrevY -> GenerationDone()) { return false; } }
	if (PrevZ != nullptr) { if (!PrevZ -> GenerationDone()) { return false; } }
	if (NextX != nullptr) { if (!NextX -> GenerationDone()) { return false; } }
	if (NextY != nullptr) { if (!NextY -> GenerationDone()) { return false; } }
	if (NextZ != nullptr) { if (!NextZ -> GenerationDone()) { return false; } }
	return true;
}
*/





/*
ChunkCubeNeighbour::~ChunkCubeNeighbour()
{ }
ChunkCubeNeighbour::ChunkCubeNeighbour()
	: Cube{
		{
			{ nullptr, nullptr, nullptr },
			{ nullptr, nullptr, nullptr },
			{ nullptr, nullptr, nullptr },
		},
		{
			{ nullptr, nullptr, nullptr },
			{ nullptr, nullptr, nullptr },
			{ nullptr, nullptr, nullptr },
		},
		{
			{ nullptr, nullptr, nullptr },
			{ nullptr, nullptr, nullptr },
			{ nullptr, nullptr, nullptr },
		},
	}
{ }
ChunkCubeNeighbour::ChunkCubeNeighbour(const ChunkCubeNeighbour & other)
	: Cube{
		{
			{ other.Cube[0][0][0], other.Cube[0][0][1], other.Cube[0][0][2] },
			{ other.Cube[0][1][0], other.Cube[0][1][1], other.Cube[0][1][2] },
			{ other.Cube[0][2][0], other.Cube[0][2][1], other.Cube[0][2][2] },
		},
		{
			{ other.Cube[1][0][0], other.Cube[1][0][1], other.Cube[1][0][2] },
			{ other.Cube[1][1][0], other.Cube[1][1][1], other.Cube[1][1][2] },
			{ other.Cube[1][2][0], other.Cube[1][2][1], other.Cube[1][2][2] },
		},
		{
			{ other.Cube[2][0][0], other.Cube[2][0][1], other.Cube[2][0][2] },
			{ other.Cube[2][1][0], other.Cube[2][1][1], other.Cube[2][1][2] },
			{ other.Cube[2][2][0], other.Cube[2][2][1], other.Cube[2][2][2] },
		},
	}
{ }
ChunkCubeNeighbour & ChunkCubeNeighbour::operator=(const ChunkCubeNeighbour & other)
{
	Cube[0][0][0] = other.Cube[0][0][0]; Cube[0][0][1] = other.Cube[0][0][1]; Cube[0][0][2] = other.Cube[0][0][2];
	Cube[0][1][0] = other.Cube[0][1][0]; Cube[0][1][1] = other.Cube[0][1][1]; Cube[0][1][2] = other.Cube[0][1][2];
	Cube[0][2][0] = other.Cube[0][2][0]; Cube[0][2][1] = other.Cube[0][2][1]; Cube[0][2][2] = other.Cube[0][2][2];
	Cube[1][0][0] = other.Cube[1][0][0]; Cube[1][0][1] = other.Cube[1][0][1]; Cube[1][0][2] = other.Cube[1][0][2];
	Cube[1][1][0] = other.Cube[1][1][0]; Cube[1][1][1] = other.Cube[1][1][1]; Cube[1][1][2] = other.Cube[1][1][2];
	Cube[1][2][0] = other.Cube[1][2][0]; Cube[1][2][1] = other.Cube[1][2][1]; Cube[1][2][2] = other.Cube[1][2][2];
	Cube[2][0][0] = other.Cube[2][0][0]; Cube[2][0][1] = other.Cube[2][0][1]; Cube[2][0][2] = other.Cube[2][0][2];
	Cube[2][1][0] = other.Cube[2][1][0]; Cube[2][1][1] = other.Cube[2][1][1]; Cube[2][1][2] = other.Cube[2][1][2];
	Cube[2][2][0] = other.Cube[2][2][0]; Cube[2][2][1] = other.Cube[2][2][1]; Cube[2][2][2] = other.Cube[2][2][2];
	return *this;
}
ChunkCubeNeighbour::ChunkCubeNeighbour(const Chunk & chunk)
	: Cube{
		{
			{ nullptr, nullptr, nullptr },
			{ nullptr, nullptr, nullptr },
			{ nullptr, nullptr, nullptr },
		},
		{
			{ nullptr, nullptr, nullptr },
			{ nullptr, &chunk , nullptr },
			{ nullptr, nullptr, nullptr },
		},
		{
			{ nullptr, nullptr, nullptr },
			{ nullptr, nullptr, nullptr },
			{ nullptr, nullptr, nullptr },
		},
	}
{ }

void ChunkCubeNeighbour::Change(const Chunk * chunk, unsigned int x, unsigned int y, unsigned int z) { Cube[z][y][x] = chunk; }

bool ChunkCubeNeighbour::CanAssamble() const
{
	for (unsigned int z = 0; z < 3; z++)
	{
		for (unsigned int y = 0; y < 3; y++)
		{
			for (unsigned int x = 0; x < 3; x++)
			{
				const Chunk * chunk = Cube[z][y][x];
				if (chunk == nullptr) { return false; }
				if (!chunk -> DecorationsGenerated) { return false; }
			}
		}
	}
	return true;
}
*/






ChunkNeighbour::~ChunkNeighbour()
{ }
ChunkNeighbour::ChunkNeighbour()
	: Cube{
		{
			{ nullptr, nullptr, nullptr },
			{ nullptr, nullptr, nullptr },
			{ nullptr, nullptr, nullptr },
		},
		{
			{ nullptr, nullptr, nullptr },
			{ nullptr, nullptr, nullptr },
			{ nullptr, nullptr, nullptr },
		},
		{
			{ nullptr, nullptr, nullptr },
			{ nullptr, nullptr, nullptr },
			{ nullptr, nullptr, nullptr },
		},
	}
{ }
ChunkNeighbour::ChunkNeighbour(const ChunkNeighbour & other)
	: Cube{
		{
			{ other.Cube[0][0][0], other.Cube[0][0][1], other.Cube[0][0][2] },
			{ other.Cube[0][1][0], other.Cube[0][1][1], other.Cube[0][1][2] },
			{ other.Cube[0][2][0], other.Cube[0][2][1], other.Cube[0][2][2] },
		},
		{
			{ other.Cube[1][0][0], other.Cube[1][0][1], other.Cube[1][0][2] },
			{ other.Cube[1][1][0], other.Cube[1][1][1], other.Cube[1][1][2] },
			{ other.Cube[1][2][0], other.Cube[1][2][1], other.Cube[1][2][2] },
		},
		{
			{ other.Cube[2][0][0], other.Cube[2][0][1], other.Cube[2][0][2] },
			{ other.Cube[2][1][0], other.Cube[2][1][1], other.Cube[2][1][2] },
			{ other.Cube[2][2][0], other.Cube[2][2][1], other.Cube[2][2][2] },
		},
	}
{ }
ChunkNeighbour & ChunkNeighbour::operator=(const ChunkNeighbour & other)
{
	Cube[0][0][0] = other.Cube[0][0][0]; Cube[0][0][1] = other.Cube[0][0][1]; Cube[0][0][2] = other.Cube[0][0][2];
	Cube[0][1][0] = other.Cube[0][1][0]; Cube[0][1][1] = other.Cube[0][1][1]; Cube[0][1][2] = other.Cube[0][1][2];
	Cube[0][2][0] = other.Cube[0][2][0]; Cube[0][2][1] = other.Cube[0][2][1]; Cube[0][2][2] = other.Cube[0][2][2];
	Cube[1][0][0] = other.Cube[1][0][0]; Cube[1][0][1] = other.Cube[1][0][1]; Cube[1][0][2] = other.Cube[1][0][2];
	Cube[1][1][0] = other.Cube[1][1][0]; Cube[1][1][1] = other.Cube[1][1][1]; Cube[1][1][2] = other.Cube[1][1][2];
	Cube[1][2][0] = other.Cube[1][2][0]; Cube[1][2][1] = other.Cube[1][2][1]; Cube[1][2][2] = other.Cube[1][2][2];
	Cube[2][0][0] = other.Cube[2][0][0]; Cube[2][0][1] = other.Cube[2][0][1]; Cube[2][0][2] = other.Cube[2][0][2];
	Cube[2][1][0] = other.Cube[2][1][0]; Cube[2][1][1] = other.Cube[2][1][1]; Cube[2][1][2] = other.Cube[2][1][2];
	Cube[2][2][0] = other.Cube[2][2][0]; Cube[2][2][1] = other.Cube[2][2][1]; Cube[2][2][2] = other.Cube[2][2][2];
	return *this;
}
ChunkNeighbour::ChunkNeighbour(Chunk & chunk)
	: Cube{
		{
			{ nullptr, nullptr, nullptr },
			{ nullptr, nullptr, nullptr },
			{ nullptr, nullptr, nullptr },
		},
		{
			{ nullptr, nullptr, nullptr },
			{ nullptr, &chunk , nullptr },
			{ nullptr, nullptr, nullptr },
		},
		{
			{ nullptr, nullptr, nullptr },
			{ nullptr, nullptr, nullptr },
			{ nullptr, nullptr, nullptr },
		},
	}
{ }

bool ChunkNeighbour::IsVisiblePrevX(const Array3D<unsigned char> & is_empty, VectorU3 udx) const
{
	if (udx.X != 0)
	{
		udx.X--;
		return is_empty[udx];
	}
	else if (Cube[1][1][0] != nullptr && Cube[1][1][0] -> GenerationDone())
	{
		if (Cube[1][1][0] -> IsEmpty()) { return true; }
		udx.X = n;
		return Cube[1][1][0] -> Voxels[udx].IsEmpty();
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
	else if (Cube[1][0][1] != nullptr && Cube[1][0][1] -> GenerationDone())
	{
		if (Cube[1][0][1] -> IsEmpty()) { return true; }
		udx.Y = n;
		return Cube[1][0][1] -> Voxels[udx].IsEmpty();
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
	else if (Cube[0][1][1] != nullptr && Cube[0][1][1] -> GenerationDone())
	{
		if (Cube[0][1][1] -> IsEmpty()) { return true; }
		udx.Z = n;
		return Cube[0][1][1] -> Voxels[udx].IsEmpty();
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
	else if (Cube[1][1][2] != nullptr && Cube[1][1][2] -> GenerationDone())
	{
		if (Cube[1][1][2] -> IsEmpty()) { return true; }
		udx.X = 0;
		return Cube[1][1][2] -> Voxels[udx].IsEmpty();
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
	else if (Cube[1][2][1] != nullptr && Cube[1][2][1] -> GenerationDone())
	{
		if (Cube[1][2][1] -> IsEmpty()) { return true; }
		udx.Y = 0;
		return Cube[1][2][1] -> Voxels[udx].IsEmpty();
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
	else if (Cube[2][1][1] != nullptr && Cube[2][1][1] -> GenerationDone())
	{
		if (Cube[2][1][1] -> IsEmpty()) { return true; }
		udx.Z = 0;
		return Cube[2][1][1] -> Voxels[udx].IsEmpty();
	}
	return false;
}

void ChunkNeighbour::BufferDataWant()
{
	if (Cube[1][1][1] == nullptr) { return; }
	Chunk & chunk = *Cube[1][1][1];

	if (Cube[1][1][1] != nullptr) { chunk.Manager.AuxThread1.QueuePut(Cube[1][1][1]); }
	if (Cube[1][1][0] != nullptr) { chunk.Manager.AuxThread1.QueuePut(Cube[1][1][0]); }
	if (Cube[1][0][1] != nullptr) { chunk.Manager.AuxThread1.QueuePut(Cube[1][0][1]); }
	if (Cube[0][1][1] != nullptr) { chunk.Manager.AuxThread1.QueuePut(Cube[0][1][1]); }
	if (Cube[1][1][2] != nullptr) { chunk.Manager.AuxThread1.QueuePut(Cube[1][1][2]); }
	if (Cube[1][2][1] != nullptr) { chunk.Manager.AuxThread1.QueuePut(Cube[1][2][1]); }
	if (Cube[2][1][1] != nullptr) { chunk.Manager.AuxThread1.QueuePut(Cube[2][1][1]); }
}

bool ChunkNeighbour::CanMakeBuffer() const
{
	if (Cube[1][1][1] != nullptr) { if (!Cube[1][1][1] -> GenerationDone()) { return false; } }
	if (Cube[1][1][0] != nullptr) { if (!Cube[1][1][0] -> GenerationDone()) { return false; } }
	if (Cube[1][0][1] != nullptr) { if (!Cube[1][0][1] -> GenerationDone()) { return false; } }
	if (Cube[0][1][1] != nullptr) { if (!Cube[0][1][1] -> GenerationDone()) { return false; } }
	if (Cube[1][1][2] != nullptr) { if (!Cube[1][1][2] -> GenerationDone()) { return false; } }
	if (Cube[1][2][1] != nullptr) { if (!Cube[1][2][1] -> GenerationDone()) { return false; } }
	if (Cube[2][1][1] != nullptr) { if (!Cube[2][1][1] -> GenerationDone()) { return false; } }
	return true;
}

bool ChunkNeighbour::CanAssamble() const
{
	for (unsigned int z = 0; z < 3; z++)
	{
		for (unsigned int y = 0; y < 3; y++)
		{
			for (unsigned int x = 0; x < 3; x++)
			{
				const Chunk * chunk = Cube[z][y][x];
				if (chunk == nullptr) { return false; }
				if (!chunk -> DecorationsGenerated) { return false; }
			}
		}
	}
	return true;
}
