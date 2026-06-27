#ifndef  VOXEL_HIT_HPP
# define VOXEL_HIT_HPP

#include "General/GridCast/GridCast3D.hpp"

struct Chunk;
struct ChunkManager;
struct VoxelHit
{
	AxisRel		Side;
	VectorI3	Index;
	//VoxelIndex	Index;
	VectorF3	Position;
	VectorF3	Normal;

	bool	Valid() const;
	VoxelHit();

	public:
	static GridCast3D::Hit	Hit(const Chunk & chunk, RayF3 ray3D, float limit);
	static GridCast3D::Hit	Hit(ChunkManager & manager, RayF3 ray3D, float limit);
};

#endif