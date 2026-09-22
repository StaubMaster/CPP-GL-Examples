#include "3D/Chunk/Neighbours.hpp"
#include "3D/Chunk/Manager.hpp"
#include "3D/Chunk.hpp"

#include "3D/Voxel.hpp"

#include "Axis/3D/Enums.hpp"

#include "ValueType/Vector/U3.hpp"

#define n CHUNK_VALUES_PER_SIDE - 1



ChunkNeighbour::ChunkNeighbour(Chunk * chunk)
	: Cube{
		{
			{ nullptr, nullptr, nullptr },
			{ nullptr, nullptr, nullptr },
			{ nullptr, nullptr, nullptr },
		},
		{
			{ nullptr, nullptr, nullptr },
			{ nullptr,  chunk , nullptr },
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
		if (chunk == nullptr) { return false; }
		if (!chunk -> IsDone()) { return false; }
		if (chunk -> IsEmpty()) { return true; }
		u = n;
	}
	return ((*chunk)[udx].IsAxisVisible(Axis3D::Rel::PrevX));
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
		if (chunk == nullptr) { return false; }
		if (!chunk -> IsDone()) { return false; }
		if (chunk -> IsEmpty()) { return true; }
		u = n;
	}
	return ((*chunk)[udx].IsAxisVisible(Axis3D::Rel::PrevY));
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
		if (chunk == nullptr) { return false; }
		if (!chunk -> IsDone()) { return false; }
		if (chunk -> IsEmpty()) { return true; }
		u = n;
	}
	return ((*chunk)[udx].IsAxisVisible(Axis3D::Rel::PrevZ));
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
		if (chunk == nullptr) { return false; }
		if (!chunk -> IsDone()) { return false; }
		if (chunk -> IsEmpty()) { return true; }
		u = 0;
	}
	return ((*chunk)[udx].IsAxisVisible(Axis3D::Rel::NextX));
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
		if (chunk == nullptr) { return false; }
		if (!chunk -> IsDone()) { return false; }
		if (chunk -> IsEmpty()) { return true; }
		u = 0;
	}
	return ((*chunk)[udx].IsAxisVisible(Axis3D::Rel::NextY));
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
		if (chunk == nullptr) { return false; }
		if (!chunk -> IsDone()) { return false; }
		if (chunk -> IsEmpty()) { return true; }
		u = 0;
	}
	return ((*chunk)[udx].IsAxisVisible(Axis3D::Rel::NextZ));
}

void ChunkNeighbour::BufferDataWantAll()
{
	if (Cube[1][1][1] != nullptr) { Cube[1][1][1] -> BufferData_Queue(); }
	if (Cube[1][1][0] != nullptr) { Cube[1][1][0] -> BufferData_Queue(); }
	if (Cube[1][0][1] != nullptr) { Cube[1][0][1] -> BufferData_Queue(); }
	if (Cube[0][1][1] != nullptr) { Cube[0][1][1] -> BufferData_Queue(); }
	if (Cube[1][1][2] != nullptr) { Cube[1][1][2] -> BufferData_Queue(); }
	if (Cube[1][2][1] != nullptr) { Cube[1][2][1] -> BufferData_Queue(); }
	if (Cube[2][1][1] != nullptr) { Cube[2][1][1] -> BufferData_Queue(); }
}
void ChunkNeighbour::BufferDataWant(const VectorU3 & udx)
{
	(void)udx;
	if (Cube[1][1][1] != nullptr) { Cube[1][1][1] -> BufferData_Queue(); }
	if (Cube[1][1][0] != nullptr) { Cube[1][1][0] -> BufferData_Queue(); }
	if (Cube[1][0][1] != nullptr) { Cube[1][0][1] -> BufferData_Queue(); }
	if (Cube[0][1][1] != nullptr) { Cube[0][1][1] -> BufferData_Queue(); }
	if (Cube[1][1][2] != nullptr) { Cube[1][1][2] -> BufferData_Queue(); }
	if (Cube[1][2][1] != nullptr) { Cube[1][2][1] -> BufferData_Queue(); }
	if (Cube[2][1][1] != nullptr) { Cube[2][1][1] -> BufferData_Queue(); }
}

bool ChunkNeighbour::CanMakeBuffer() const
{
	if (Cube[1][1][1] != nullptr) { if (!Cube[1][1][1] -> IsDone()) { return false; } }
	if (Cube[1][1][0] != nullptr) { if (!Cube[1][1][0] -> IsDone()) { return false; } }
	if (Cube[1][0][1] != nullptr) { if (!Cube[1][0][1] -> IsDone()) { return false; } }
	if (Cube[0][1][1] != nullptr) { if (!Cube[0][1][1] -> IsDone()) { return false; } }
	if (Cube[1][1][2] != nullptr) { if (!Cube[1][1][2] -> IsDone()) { return false; } }
	if (Cube[1][2][1] != nullptr) { if (!Cube[1][2][1] -> IsDone()) { return false; } }
	if (Cube[2][1][1] != nullptr) { if (!Cube[2][1][1] -> IsDone()) { return false; } }
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
