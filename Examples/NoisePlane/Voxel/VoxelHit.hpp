#ifndef  VOXEL_HIT_HPP
# define VOXEL_HIT_HPP

#include "GridCast/GridCast3D.hpp"
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
	static GridCast3D::Hit	Hit(const Chunk & chunk, Ray3D ray3D, float limit);
	static GridCast3D::Hit	Hit(ChunkManager & manager, Ray3D ray3D, float limit);
};

#endif