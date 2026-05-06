#ifndef  VOXEL_HPP
# define VOXEL_HPP

# include "VoxelOrientation.hpp"

struct VoxelPallet;

struct Voxel
{
	const VoxelPallet *		Pallet;
	VoxelOrientation		Orientation;

	bool	Visible(AxisRel axis) const;

	~Voxel();
	Voxel();

	Voxel(const Voxel & other);
	Voxel & operator=(const Voxel & other);
};

#endif
