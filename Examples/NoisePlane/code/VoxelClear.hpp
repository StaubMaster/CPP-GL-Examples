#ifndef  VOXEL_CLEAR_HPP
# define VOXEL_CLEAR_HPP

# include "3D/ChunkVoxelIndex.hpp"

struct VoxelPallet;
struct ChunkContainer;
struct ItemTool;

# include <iosfwd>

struct VoxelClear
{
	ChunkContainer &	Container;

	unsigned int	Progress = 0xFFFFFFFF;
	unsigned int	Required = 64; // should come from Pallet

	ChunkVoxelIndex			Index;
	const VoxelPallet *		Pallet = nullptr;

	const ItemTool *		Tool = nullptr;

	~VoxelClear() = default;
	VoxelClear() = delete;
	VoxelClear(const VoxelClear & other) = delete;
	VoxelClear & operator=(const VoxelClear & other) = delete;
	VoxelClear(ChunkContainer & container);

	void	ChangeTool(const ItemTool * tool);

	bool	Is() const;
	void	None();

	void	Change(const ChunkVoxelIndex & idx);
	void	Continue(const ChunkVoxelIndex & idx);

	void	Show(std::stringstream & ss) const;
};

#endif