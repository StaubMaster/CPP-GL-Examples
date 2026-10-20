#include "VoxelCollision.hpp"

#include "FrameTime.hpp"
#include "3D/Chunk/Container.hpp"

#include "BoxEntity3D.hpp"
#include "BoxEntityManager.hpp"

#include "ValueType/Box/I3.hpp"
#include "DisplayHelp/Normalized.hpp"



bool	VoxelCollision_DisplayBoxes = false;
void VoxelCollision(const FrameTime & frame_time, ChunkContainer & container, BoxEntity3D & box_entity)
{
	BoxI3 range = box_entity.RangeI(frame_time);
	Container::Array<BoxF3> boxes = container.CollisionBoxes(range);
	if (VoxelCollision_DisplayBoxes)
	{
		DisplayHelp::Normalized(boxes);
	}
	box_entity.Collide(boxes, frame_time.Delta);
}
void VoxelCollision(const FrameTime & frame_time, ChunkContainer & container, const Container::Array<BoxEntity3D*> & box_entitys)
{
	for (unsigned int i = 0; i < box_entitys.Length(); i++)
	{
		BoxEntity3D * obj = box_entitys[i];
		if (obj != nullptr)
		{
			VoxelCollision(frame_time, container, *obj);
		}
	}
}
void VoxelCollision(const FrameTime & frame_time, ChunkContainer & container, BoxEntityManager & box_entity_manager)
{
	VoxelCollision(frame_time, container, box_entity_manager.BoxEntitys.ToArray());
}
