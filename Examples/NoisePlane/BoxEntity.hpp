#ifndef  BOX_ENTITY_HPP
# define BOX_ENTITY_HPP

# include "ValueType/VectorF3.hpp"
# include "ValueType/BoxF3.hpp"
# include "ValueType/LoopI3.hpp"

# include "FrameTime.hpp"

# include "ValueType/VectorI3.hpp"
# include "Voxel/Voxel.hpp"

struct VoxelBoxCollision
{
	float		Time;
	VectorF3	Normal;

	VoxelBoxCollision();
	void Consider(VectorF3 t, VectorF3 dir);
};

class PolyHedra;
struct ChunkManager;

struct BoxEntity
{
	::PolyHedra *	PolyHedra = nullptr;
	BoxF3			Box;
	VectorF3		Pos;
	VectorF3		Vel;

	VoxelBoxCollision FindCollisionTime(::ChunkManager & manager, LoopI3 loop, BoxF3 box, VectorF3 off) const;
	void Collide(::ChunkManager & manager, LoopI3 loop, FrameTime frame_time);
	void Collide(::ChunkManager & manager, FrameTime frame_time);
};

#endif