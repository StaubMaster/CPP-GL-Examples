#ifndef  VOXEL_HPP
# define VOXEL_HPP

# include "AxisOrientation.hpp"

struct VoxelPallet;

struct Voxel
{
	unsigned short		Pallet;
	AxisOrientation		Orientation;

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
