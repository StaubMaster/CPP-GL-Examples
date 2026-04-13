#ifndef  VOXEL_HPP
# define VOXEL_HPP

# define VOXEL_SCALE 0.0625

# include "Graphics/Voxel.hpp"

struct Voxel
{
	unsigned int	Value;

	~Voxel();
	Voxel();

	Voxel(const Voxel & other);
	Voxel & operator=(const Voxel & other);

	bool	IsSolid() const;

	VoxelGraphics::VoxelCube	ToGraphics(VectorU3 u) const;
};

#endif
