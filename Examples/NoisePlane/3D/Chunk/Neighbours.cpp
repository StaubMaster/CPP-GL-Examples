#include "3D/Chunk/Neighbours.hpp"
#include "3D/Chunk/Manager.hpp"
#include "3D/Chunk.hpp"

#include "3D/Voxel.hpp"

#include "Axis/Enums.hpp"

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

bool ChunkNeighbour::IsVisiblePrevX(const Array3D<bool> & voxel_is_empty, VectorU3 udx) const
{
	const Chunk * chunk = nullptr;
	unsigned int & u = udx.X;
	if (u != 0)
	{
		u--;
		if (voxel_is_empty[udx]) { return true; }
		chunk = Cube[1][1][1];
	}
	else
	{
		chunk = Cube[1][1][0];
		if (chunk == nullptr || !(chunk -> GenerationDone())) { return false; }
		if (chunk -> IsEmpty()) { return true; }
		u = n;
	}
	return (chunk -> Voxels[udx].IsAxisVisible(AxisRel::PrevX));
}
bool ChunkNeighbour::IsVisiblePrevY(const Array3D<bool> & voxel_is_empty, VectorU3 udx) const
{
	const Chunk * chunk = nullptr;
	unsigned int & u = udx.Y;
	if (u != 0)
	{
		u--;
		if (voxel_is_empty[udx]) { return true; }
		chunk = Cube[1][1][1];
	}
	else
	{
		chunk = Cube[1][0][1];
		if (chunk == nullptr || !(chunk -> GenerationDone())) { return false; }
		if (chunk -> IsEmpty()) { return true; }
		u = n;
	}
	return (chunk -> Voxels[udx].IsAxisVisible(AxisRel::PrevY));
}
bool ChunkNeighbour::IsVisiblePrevZ(const Array3D<bool> & voxel_is_empty, VectorU3 udx) const
{
	const Chunk * chunk = nullptr;
	unsigned int & u = udx.Z;
	if (u != 0)
	{
		u--;
		if (voxel_is_empty[udx]) { return true; }
		chunk = Cube[1][1][1];
	}
	else
	{
		chunk = Cube[0][1][1];
		if (chunk == nullptr || !(chunk -> GenerationDone())) { return false; }
		if (chunk -> IsEmpty()) { return true; }
		u = n;
	}
	return (chunk -> Voxels[udx].IsAxisVisible(AxisRel::PrevZ));
}
bool ChunkNeighbour::IsVisibleNextX(const Array3D<bool> & voxel_is_empty, VectorU3 udx) const
{
	const Chunk * chunk = nullptr;
	unsigned int & u = udx.X;
	if (u != n)
	{
		u++;
		if (voxel_is_empty[udx]) { return true; }
		chunk = Cube[1][1][1];
	}
	else
	{
		chunk = Cube[1][1][2];
		if (chunk == nullptr || !(chunk -> GenerationDone())) { return false; }
		if (chunk -> IsEmpty()) { return true; }
		u = 0;
	}
	return (chunk -> Voxels[udx].IsAxisVisible(AxisRel::NextX));
}
bool ChunkNeighbour::IsVisibleNextY(const Array3D<bool> & voxel_is_empty, VectorU3 udx) const
{
	const Chunk * chunk = nullptr;
	unsigned int & u = udx.Y;
	if (u != n)
	{
		u++;
		if (voxel_is_empty[udx]) { return true; }
		chunk = Cube[1][1][1];
	}
	else
	{
		chunk = Cube[1][2][1];
		if (chunk == nullptr || !(chunk -> GenerationDone())) { return false; }
		if (chunk -> IsEmpty()) { return true; }
		u = 0;
	}
	return (chunk -> Voxels[udx].IsAxisVisible(AxisRel::NextY));
}
bool ChunkNeighbour::IsVisibleNextZ(const Array3D<bool> & voxel_is_empty, VectorU3 udx) const
{
	const Chunk * chunk = nullptr;
	unsigned int & u = udx.Z;
	if (u != n)
	{
		u++;
		if (voxel_is_empty[udx]) { return true; }
		chunk = Cube[1][1][1];
	}
	else
	{
		chunk = Cube[2][1][1];
		if (chunk == nullptr || !(chunk -> GenerationDone())) { return false; }
		if (chunk -> IsEmpty()) { return true; }
		u = 0;
	}
	return (chunk -> Voxels[udx].IsAxisVisible(AxisRel::NextZ));
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
