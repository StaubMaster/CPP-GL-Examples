#ifndef  VOXEL_HPP
# define VOXEL_HPP

# include "VoxelTemplate.hpp"
# include "Graphics/Voxel.hpp"

struct Voxel
{
	VoxelTemplate *		Template;

	~Voxel();
	Voxel();

	Voxel(const Voxel & other);
	Voxel & operator=(const Voxel & other);
};

#endif
