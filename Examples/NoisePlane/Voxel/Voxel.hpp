#ifndef  VOXEL_HPP
# define VOXEL_HPP

# include "VoxelOrientation.hpp"

struct VoxelTemplate;

struct Voxel
{
	const VoxelTemplate *	Template;
	VoxelOrientation		Orientation;

	~Voxel();
	Voxel();

	Voxel(const Voxel & other);
	Voxel & operator=(const Voxel & other);
};

#endif
