#include "ValueType/Box/F3.hpp"
#include "ValueType/Bool/3.hpp"



BoxF3::BoxF3()
	: Box_3(
		VectorF3(+1/0.0f),
		VectorF3(-1/0.0f)
	)
{ }
BoxF3::BoxF3(VectorF3 min, VectorF3 max)
	: Box_3(min, max)
{ }



VectorF3 BoxF3::CollisionTimePerAxis(
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
VectorF3 BoxF3::CollisionTimePerAxisNaN(
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



#include "../src/ValueType/Box/__.cpp"
#include "../src/ValueType/Box/_3.cpp"
template struct Box__<float, VectorF3, BoxF3>;
template struct Box_3<float, VectorF3, BoxF3>;
