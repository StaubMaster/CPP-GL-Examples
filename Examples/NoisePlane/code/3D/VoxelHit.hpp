#ifndef  VOXEL_HIT_HPP
# define VOXEL_HIT_HPP

#include "GridCast/GridCast3D.hpp"
#include "Axis/3D/Enums.hpp"

struct Chunk;
struct ChunkContainer;

struct VoxelHit
{
	Axis3D::Rel		Side = Axis3D::Rel::None;
	VectorF3		Position;
	VectorI3		Index;

	bool	Valid() const;
	public:
	static VoxelHit		Hit(RayF3 ray, float limit, ChunkContainer & container);
	private:
	static GridCast3D::Hit	HitGridCast(RayF3 ray, float limit, ChunkContainer & container);
	static GridCast3D::Hit	HitGridCast(RayF3 ray, float limit, const Chunk & chunk);
};

#endif