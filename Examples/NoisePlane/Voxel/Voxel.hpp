#ifndef  VOXEL_HPP
# define VOXEL_HPP

# include "VoxelOrientation.hpp"

struct VoxelPallet;

struct Voxel
{
	unsigned short		Pallet;
	VoxelOrientation	Orientation;

	bool	IsEmpty() const;
	bool	Visible(AxisRel axis) const;

	void	MakeEmpty();
	void	Make(const VoxelPallet & pallet);

	~Voxel();
	Voxel();

	Voxel(const Voxel & other);
	Voxel & operator=(const Voxel & other);
};

#endif
