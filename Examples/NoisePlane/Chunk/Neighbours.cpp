#include "Neighbours.hpp"
#include "Manager.hpp"
#include "Chunk.hpp"

#include "Voxel.hpp"

#include "General/Axis/Enums.hpp"

#include "ValueType/Vector/U3.hpp"

#define n CHUNK_VALUES_PER_SIDE - 1



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
