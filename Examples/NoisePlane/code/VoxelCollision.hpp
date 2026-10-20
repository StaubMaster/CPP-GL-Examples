#ifndef  VOXEL_COLLISION_HPP
# define VOXEL_COLLISION_HPP

struct FrameTime;
struct ChunkContainer;

struct BoxEntity3D;
struct BoxEntityManager;

namespace Container
{
template<typename T> struct Array;
};

extern bool		VoxelCollision_DisplayBoxes;
void	VoxelCollision(const FrameTime & frame_time, ChunkContainer & container, BoxEntity3D & box_entity);
void	VoxelCollision(const FrameTime & frame_time, ChunkContainer & container, const Container::Array<BoxEntity3D*> & box_entitys);
void	VoxelCollision(const FrameTime & frame_time, ChunkContainer & container, BoxEntityManager & box_entity_manager);

#endif