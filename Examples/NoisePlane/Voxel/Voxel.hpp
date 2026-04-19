#ifndef  VOXEL_HPP
# define VOXEL_HPP

# include "VoxelTemplate.hpp"
# include "VoxelOrientation.hpp"

struct Voxel
{
	VoxelTemplate *		Template;
	VoxelOrientation	Orientation;

	~Voxel();
	Voxel();

	Voxel(const Voxel & other);
	Voxel & operator=(const Voxel & other);
};

#endif
