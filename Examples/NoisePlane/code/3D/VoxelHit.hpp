#ifndef  VOXEL_HIT_HPP
# define VOXEL_HIT_HPP

#include "GridCast/GridCast3D.hpp"
#include "Axis/3D/Enums.hpp"

struct Chunk;
struct ChunkContainer;

struct VoxelHit
{
	Axis3D::Rel		Side = Axis3D::Rel::None;
	VectorI3		Index;
	//VoxelIndex	Index;
	VectorF3		Position;
	VectorF3		Normal;

	bool	Valid() const;

	public:
	static GridCast3D::Hit	Hit(const Chunk & chunk, RayF3 ray3D, float limit);
	static GridCast3D::Hit	Hit(ChunkContainer & container, RayF3 ray3D, float limit);
};

#endif