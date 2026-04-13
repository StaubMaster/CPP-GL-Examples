#ifndef  VOXEL_HPP
# define VOXEL_HPP

# define VOXEL_SCALE 0.0625

# include "ChunkGraphics.hpp"

struct Voxel
{
	float	Value;

	~Voxel();
	Voxel();

	Voxel(const Voxel & other);
	Voxel & operator=(const Voxel & other);

	bool	IsSolid() const;

	ChunkGraphics::VoxelData	ToGraphics(VectorU3 u) const;
};

#endif
