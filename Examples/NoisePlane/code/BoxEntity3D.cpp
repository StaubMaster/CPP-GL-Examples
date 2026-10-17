#include "BoxEntity3D.hpp"
#include "ValueType/Vector/I3.hpp"
#include "ValueType/Bool/3.hpp"

#include "Axis/3D/Enums.hpp"



static VectorI3 Axis_Ranks(const VectorF3 & vec)
{
	VectorI3 ranks;

	const float *	value_ptr = (const float*)&vec;
	int *			ranks_ptr = (int*)&ranks;

	for (unsigned int i = 0; i < 3; i++)
	{
		if (value_ptr[i] != value_ptr[i])
		{
			ranks_ptr[i] = -1;
		}
		else
		{
			for (unsigned int j = 0; j < 3; j++)
			{
				if (i != j)
				{
					if (value_ptr[i] > value_ptr[j])
					{
						ranks_ptr[i]++;
					}
				}
			}
		}
	}

	return ranks;
}

BoxEntity3D_CollisionTime::BoxEntity3D_CollisionTime(VectorF3 t, VectorF3 dir)
{
	//VectorI3 ranks = t.abs().RankDimensions();
	VectorI3 ranks = Axis_Ranks(t.abs());
	if      (ranks.X == 0) { Time = t.X; Normal = VectorF3(dir.X, 0, 0); }
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



void BoxEntity3D_CollisionSide::Consider(const Axis3D::Rel & axis)
{
	switch (axis)
	{
		case Axis3D::Rel::PrevX: PrevX = true; None = false; break;
		case Axis3D::Rel::PrevY: PrevY = true; None = false; break;
		case Axis3D::Rel::PrevZ: PrevZ = true; None = false; break;
		case Axis3D::Rel::NextX: NextX = true; None = false; break;
		case Axis3D::Rel::NextY: NextY = true; None = false; break;
		case Axis3D::Rel::NextZ: NextZ = true; None = false; break;
		default: break;
	}
}
void BoxEntity3D_CollisionSide::Consider(const VectorF3 & vec)
{
	if (vec.X > 0.0f) { Consider(Axis3D::Rel::PrevX); }
	if (vec.Y > 0.0f) { Consider(Axis3D::Rel::PrevY); }
	if (vec.Z > 0.0f) { Consider(Axis3D::Rel::PrevZ); }
	if (vec.X < 0.0f) { Consider(Axis3D::Rel::NextX); }
	if (vec.Y < 0.0f) { Consider(Axis3D::Rel::NextY); }
	if (vec.Z < 0.0f) { Consider(Axis3D::Rel::NextZ); }
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



static VectorF3 CollisionTimePerAxis(
	const BoxF3 & box0, const VectorF3 & vel0,
	const BoxF3 & box1
)
{
	Bool3	comp = (vel0 > 0.0f);

	//VectorF3 pos0;
	//if (vel0.X > 0.0f) { pos0.X = box0.Max.X; } else { pos0.X = box0.Min.X; }
	//if (vel0.Y > 0.0f) { pos0.Y = box0.Max.Y; } else { pos0.Y = box0.Min.Y; }
	//if (vel0.Z > 0.0f) { pos0.Z = box0.Max.Z; } else { pos0.Z = box0.Min.Z; }
	VectorF3 pos0 = VectorF3::Mix(box0.Min, box0.Max, comp);

	//VectorF3 pos1;
	//if (vel0.X > 0.0f) { pos1.X = box1.Min.X; } else { pos1.X = box1.Max.X; }
	//if (vel0.Y > 0.0f) { pos1.Y = box1.Min.Y; } else { pos1.Y = box1.Max.Y; }
	//if (vel0.Z > 0.0f) { pos1.Z = box1.Min.Z; } else { pos1.Z = box1.Max.Z; }
	VectorF3 pos1 = VectorF3::Mix(box1.Max, box1.Min, comp);

	return (pos1 - pos0) / vel0;
}
static VectorF3 CollisionTimePerAxisNaN(
	const BoxF3 & box0, const VectorF3 & vel0,
	const BoxF3 & box1
)
{
	VectorF3 t = CollisionTimePerAxis(box0, vel0, box1);

	if (t.X >= 0.0f)
	{
		BoxF3 box = box0 + (vel0 * t.X);
		box.Min.X = -1.0f/0.0f; // -Infinity
		box.Max.X = +1.0f/0.0f; // +Infinity
		if (!box.IntersectsInclusive(box1).All(true))
		{
			t.X = 0.0f / 0.0f; // no Collision
		}
	}
	else { t.X = 0.0f / 0.0f; }

	if (t.Y >= 0.0f)
	{
		BoxF3 box = box0 + (vel0 * t.Y);
		box.Min.Y = -1.0f/0.0f; // -Infinity
		box.Max.Y = +1.0f/0.0f; // +Infinity
		if (!box.IntersectsInclusive(box1).All(true))
		{
			t.Y = 0.0f / 0.0f; // no Collision
		}
	}
	else { t.Y = 0.0f / 0.0f; }

	if (t.Z >= 0.0f)
	{
		BoxF3 box = box0 + (vel0 * t.Z);
		box.Min.Z = -1.0f/0.0f; // -Infinity
		box.Max.Z = +1.0f/0.0f; // +Infinity
		if (!box.IntersectsInclusive(box1).All(true))
		{
			t.Z = 0.0f / 0.0f; // no Collision
		}
	}
	else { t.Z = 0.0f / 0.0f; }

	return t;
}

BoxEntity3D_CollisionTime BoxEntity3D::FindCollisionTime(const BoxF3 & other) const
{
	if ((Box + Pos).IntersectsInclusive(other).All(true))
	{
		BoxEntity3D_CollisionTime();
	}
	VectorF3 t = CollisionTimePerAxisNaN((Box + Pos), Vel, other);

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
