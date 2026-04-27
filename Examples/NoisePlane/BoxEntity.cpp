#include "BoxEntity.hpp"
#include "Voxel/ChunkManager.hpp"



VoxelBoxCollision::VoxelBoxCollision()
	: Time(0.0f/0.0f)
	, Normal()
{ }
void VoxelBoxCollision::Consider(VectorF3 t, VectorF3 dir)
{
	float time;
	VectorF3 normal;
	VectorI3 ranks = t.abs().RankDimensions();
	     if (ranks.X == 0) { time = t.X; normal = VectorF3(dir.X, 0, 0); }
	else if (ranks.Y == 0) { time = t.Y; normal = VectorF3(0, dir.Y, 0); }
	else if (ranks.Z == 0) { time = t.Z; normal = VectorF3(0, 0, dir.Z); }
	else { return; }
	if (Time != Time || Time > time)
	{
		Time = time;
		Normal = normal;
	}
}



CollisionSide::CollisionSide()
	: None(true)
	, PrevX(false)
	, PrevY(false)
	, PrevZ(false)
	, NextX(false)
	, NextY(false)
	, NextZ(false)
{ }
void CollisionSide::Consider(AxisRel axis)
{
	switch (axis)
	{
		case AxisRel::PrevX: PrevX = true; None = false; break;
		case AxisRel::PrevY: PrevY = true; None = false; break;
		case AxisRel::PrevZ: PrevZ = true; None = false; break;
		case AxisRel::NextX: NextX = true; None = false; break;
		case AxisRel::NextY: NextY = true; None = false; break;
		case AxisRel::NextZ: NextZ = true; None = false; break;
		default: break;
	}
}
void CollisionSide::Consider(VectorF3 vec)
{
	if (vec.X > 0.0f) { Consider(AxisRel::PrevX); }
	if (vec.Y > 0.0f) { Consider(AxisRel::PrevY); }
	if (vec.Z > 0.0f) { Consider(AxisRel::PrevZ); }
	if (vec.X < 0.0f) { Consider(AxisRel::NextX); }
	if (vec.Y < 0.0f) { Consider(AxisRel::NextY); }
	if (vec.Z < 0.0f) { Consider(AxisRel::NextZ); }
}
void CollisionSide::Consider(CollisionSide other)
{
	None = None | other.None;
	PrevX = PrevX | other.PrevX;
	PrevY = PrevY | other.PrevY;
	PrevZ = PrevZ | other.PrevZ;
	NextX = NextX | other.NextX;
	NextY = NextY | other.NextY;
	NextZ = NextZ | other.NextZ;
}



VoxelBoxCollision BoxEntity::FindCollisionTime(::ChunkManager & manager, LoopI3 loop, BoxF3 box, VectorF3 off) const
{
	VoxelBoxCollision collision;
	for (VectorI3 i = loop.Min(); loop.Check(i).All(true); loop.Next(i))
	{
		const Voxel * voxel = manager.FindVoxelOrNull(i);
		if (voxel != nullptr && voxel -> Template != nullptr)
		{
			BoxF3 voxel_box(i + VectorI3(0, 0, 0), i + VectorI3(1, 1, 1));
			if ((box + off).IntersectBoxInclusive(voxel_box).All(true)) { continue; }
			VectorF3 t = BoxF3::CollisionTimePerAxisNaN(box + off, Vel, voxel_box); // might have wack collision. handle Collision in VoxelTemplate
			VectorF3 dir; // normalize Axis
			if (Vel.X > 0.0f) { dir.X = +1.0f; } else { dir.X = -1.0f; }
			if (Vel.Y > 0.0f) { dir.Y = +1.0f; } else { dir.Y = -1.0f; }
			if (Vel.Z > 0.0f) { dir.Z = +1.0f; } else { dir.Z = -1.0f; }
			collision.Consider(t, -dir);
		}
	}
	return collision;
}
CollisionSide BoxEntity::Collide(::ChunkManager & manager, LoopI3 loop, FrameTime frame_time)
{
	CollisionSide side;
	VectorF3 rel;
	float time_limit = frame_time.Delta;
	for (unsigned int l = 0; l < 4; l++)
	{
		VoxelBoxCollision collision = FindCollisionTime(manager, loop, Box + Pos, rel);
		if (collision.Time <= time_limit)
		{
			rel += Vel * collision.Time;
			time_limit -= collision.Time;
			float dot = collision.Normal.dot(Vel);
			if (dot < 0.0f)
			{
				rel += (collision.Normal * 0.01f);
				Vel -= (collision.Normal * dot);
			}
			side.Consider(collision.Normal);
		}
		else
		{
			break;
		}
	}
	if (time_limit > 0.0f)
	{
		rel += Vel * time_limit;
	}
	Pos += rel;
	return side;
}
CollisionSide BoxEntity::Collide(::ChunkManager & manager, FrameTime frame_time)
{
	BoxF3 box = Box + Pos;
	box.Consider(Box.Min + Pos + (Vel * frame_time.Delta));
	box.Consider(Box.Max + Pos + (Vel * frame_time.Delta));
	box = box - VectorF3(0.5f);
	LoopI3 loop(box.Min.round(), Bool3(false), box.Max.round(), Bool3(false));
	return Collide(manager, loop, frame_time);
}
