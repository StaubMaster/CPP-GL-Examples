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
	//AxisRel		Axis; // instread of Normal ?

	VoxelBoxCollision();
	void Consider(VectorF3 t, VectorF3 dir);
};

struct CollisionSide // could be compressed into a Byte
{
	bool	None; // all others are false
	bool	PrevX;
	bool	PrevY;
	bool	PrevZ;
	bool	NextX;
	bool	NextY;
	bool	NextZ;
	//bool	Here; // currently inside of something ?
	CollisionSide();
	void	Consider(AxisRel axis);
	void	Consider(VectorF3 vec);
	void	Consider(CollisionSide other);
};

class PolyHedra;
struct ChunkManager;

struct BoxEntity
{
	::PolyHedra *	PolyHedra = nullptr;
	BoxF3			Box;
	VectorF3		Pos;
	VectorF3		Vel;

	VoxelBoxCollision	FindCollisionTime(::ChunkManager & manager, LoopI3 loop, BoxF3 box, VectorF3 off) const;
	CollisionSide	Collide(::ChunkManager & manager, LoopI3 loop, FrameTime frame_time);
	CollisionSide	Collide(::ChunkManager & manager, FrameTime frame_time);
};

#endif