#include "BoxEntity3D.hpp"
#include "ValueType/Vector/I3.hpp"
#include "ValueType/Bool/3.hpp"



BoxEntity3D_CollisionTime::BoxEntity3D_CollisionTime(VectorF3 t, VectorF3 dir)
{
	VectorI3 ranks = t.abs().RankDimensions();
	     if (ranks.X == 0) { Time = t.X; Normal = VectorF3(dir.X, 0, 0); }
	else if (ranks.Y == 0) { Time = t.Y; Normal = VectorF3(0, dir.Y, 0); }
	else if (ranks.Z == 0) { Time = t.Z; Normal = VectorF3(0, 0, dir.Z); }
	else { Time = 0.0f / 0.0f; }
}
void BoxEntity3D_CollisionTime::Consider(const BoxEntity3D_CollisionTime & other)
{
	if (Time != Time || Time > other.Time)
	{
		*this = other;
	}
}



void BoxEntity3D_CollisionSide::Consider(const AxisRel & axis)
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
void BoxEntity3D_CollisionSide::Consider(const VectorF3 & vec)
{
	if (vec.X > 0.0f) { Consider(AxisRel::PrevX); }
	if (vec.Y > 0.0f) { Consider(AxisRel::PrevY); }
	if (vec.Z > 0.0f) { Consider(AxisRel::PrevZ); }
	if (vec.X < 0.0f) { Consider(AxisRel::NextX); }
	if (vec.Y < 0.0f) { Consider(AxisRel::NextY); }
	if (vec.Z < 0.0f) { Consider(AxisRel::NextZ); }
}
void BoxEntity3D_CollisionSide::Consider(const BoxEntity3D_CollisionSide & other)
{
	None = None & other.None;
	PrevX = PrevX | other.PrevX;
	PrevY = PrevY | other.PrevY;
	PrevZ = PrevZ | other.PrevZ;
	NextX = NextX | other.NextX;
	NextY = NextY | other.NextY;
	NextZ = NextZ | other.NextZ;
}



BoxEntity3D_CollisionTime BoxEntity3D::FindCollisionTime(const BoxF3 & other) const
{
	if ((Box + Pos).IntersectsInclusive(other).All(true))
	{
		BoxEntity3D_CollisionTime();
	}
	VectorF3 t = BoxF3::CollisionTimePerAxisNaN((Box + Pos), Vel, other);

	VectorF3 dir; // normalize Axis
	if (Vel.X > 0.0f) { dir.X = +1.0f; } else { dir.X = -1.0f; }
	if (Vel.Y > 0.0f) { dir.Y = +1.0f; } else { dir.Y = -1.0f; }
	if (Vel.Z > 0.0f) { dir.Z = +1.0f; } else { dir.Z = -1.0f; }

	return BoxEntity3D_CollisionTime(t, -dir);
}
BoxEntity3D_CollisionTime BoxEntity3D::FindCollisionTime(const Container::Array<BoxF3> & boxes) const
{
	BoxEntity3D_CollisionTime collision;
	for (unsigned int i = 0; i < boxes.Length(); i++)
	{
		collision.Consider(FindCollisionTime(boxes[i]));
	}
	return collision;
}

BoxEntity3D_CollisionSide BoxEntity3D::Collide(const Container::Array<BoxF3> & boxes, float time_limit)
{
	BoxEntity3D_CollisionSide side;

	for (unsigned int i = 0; i < 4; i++)
	{
		BoxEntity3D_CollisionTime collision = FindCollisionTime(boxes);
		if (collision.Time <= time_limit) // handles NaN
		{
			time_limit -= collision.Time;
			Pos += Vel * collision.Time;
			float dot = collision.Normal.dot(Vel);
			if (dot < 0.0f)
			{
				Pos += (collision.Normal * 0.001f);
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
		Pos += Vel * time_limit;
	}

	return side;
}
