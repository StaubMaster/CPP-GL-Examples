#include "VoxelClear.hpp"

#include "Item/ItemTool.hpp"

#include "3D/Chunk.hpp"
#include "3D/Chunk/Container.hpp"

#include "Threading/ObjectTypeAccessUniqueGuard.hpp"
#include "Threading/ObjectTypeAssignUniqueGuard.hpp"



VoxelClear::VoxelClear(ChunkContainer & container)
	: Container(container)
	, Required(64)
{ }

void VoxelClear::ChangeTool(const ItemTool * tool)
{
	Tool = tool;
}

bool VoxelClear::Is() const
{
	return (Progress != 0xFFFFFFFF);
}
void VoxelClear::None()
{
	Progress = 0xFFFFFFFF;
	Index = ChunkVoxelIndex();
	Pallet = nullptr;
//	Tool = nullptr;
}

void VoxelClear::Change(const ChunkVoxelIndex & idx)
{
	Progress = 0;
	Index = idx;

	AccessLockedChunk chunk = Container.FindAbsoluteAccess(Index.Chunk);
	const Voxel & voxel = (*chunk).Voxels[Index.Voxel];
	if (!voxel.IsEmpty())
	{
		Pallet = &voxel.ToPallet();
	}
	else
	{
		Pallet = nullptr;
	}
}
void VoxelClear::Continue(const ChunkVoxelIndex & idx)
{
	if (Is())
	{
		if (
			(idx.Chunk == Index.Chunk).All(true) &&
			(idx.Voxel == Index.Voxel).All(true)
		)
		{
			if (Progress >= Required)
			{
				// why not .FindAbsoluteAssign() ?
				AccessLockedChunk chunk_access = Container.FindAbsoluteAccess(Index.Chunk);
				if (chunk_access.Is())
				{
					Voxel voxel;
					AssignLockedChunk chunk_assign = chunk_access.ToAssign();
					(*chunk_assign).ClearVoxel(Index.Voxel, voxel);
				}
				None();
			}
			else
			{
				if (Tool != nullptr && Pallet != nullptr)
				{
					if (Tool -> Material == Pallet -> Material)
					{
						Progress += Tool -> Multiplier;
					}
					else
					{
						Progress++;
					}
				}
				else
				{
					Progress++;
				}
			}
		}
		else
		{
			Change(idx);
		}
	}
	else
	{
		Change(idx);
	}
}



#include <iostream>
#include <sstream>
#include "ValueType/_Show.hpp"
void VoxelClear::Show(std::stringstream & ss) const
{
	if (Is())
	{
		ss << "VoxelClear:\n";
		ss << Index.Chunk << " :Chunk\n";
		ss << Index.Voxel << " :Voxel\n";
		ss << Progress << " :Progress\n";
	}
}
