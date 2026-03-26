#include "Physics2D/Collision/ObjectProjection.hpp"
#include <math.h>

#include "Arrow2D/Object.hpp"



unsigned int Physics2D::Collision::ObjectProjection::DebugIndex = 0xFFFFFFFF;
bool Physics2D::Collision::ObjectProjection::DebugShow = false;
Point2D Physics2D::Collision::ObjectProjection::DebugOrigin;



Physics2D::Collision::ObjectProjection::~ObjectProjection() { }
Physics2D::Collision::ObjectProjection::ObjectProjection()
	: Box()
	, MinUdx(0xFFFFFFFF)
	, MaxUdx(0xFFFFFFFF)
{ }

Physics2D::Collision::ObjectProjection::ObjectProjection(const ObjectProjection & other)
	: Box(other.Box)
	, MinUdx(other.MinUdx)
	, MaxUdx(other.MaxUdx)
{ }
Physics2D::Collision::ObjectProjection & Physics2D::Collision::ObjectProjection::operator=(const ObjectProjection & other)
{
	Box = other.Box;
	MinUdx = other.MinUdx;
	MaxUdx = other.MaxUdx;
	return *this;
}

void Physics2D::Collision::ObjectProjection::Consider(float val, unsigned int idx)
{
	if (MinUdx == 0xFFFFFFFF || val < Box.Min)
	{
		MinUdx = idx;
		Box.Min = val;
	}
	if (MaxUdx == 0xFFFFFFFF || val > Box.Max)
	{
		MaxUdx = idx;
		Box.Max = val;
	}
}

Physics2D::Collision::ObjectProjection Physics2D::Collision::ObjectProjection::Project(
	Point2D normal,
	const Object & obj
)
{
	ObjectProjection data;

	Arrow2D::Object normal_arrow(1);
	normal_arrow[0] = Arrow2D::Inst::Data(ColorF4(0, 1, 0), 16.0f, Ray2D(DebugOrigin, normal));

	Arrow2D::Object corners(obj.CornerCount());
	for (unsigned int i = 0; i < obj.CornerCount(); i++)
	{
		Point2D	pos = obj.AbsolutePositionOfIndex(i);
		float dot = Point2D::dot(normal, pos - DebugOrigin);
		data.Consider(dot, i);
		corners[i] = Arrow2D::Inst::Data(ColorF4(1, 0, 1), 16.0f, Line2D(pos, DebugOrigin + (normal * dot)));
	}

	if (!DebugShow)
	{
		normal_arrow.Data -> DisplayThisFrame = false;
		corners.Data -> DisplayThisFrame = false;
	}

	return data;
}
Physics2D::Collision::ObjectProjection Physics2D::Collision::ObjectProjection::Project(
	Point2D origin,
	Point2D normal,
	const Object & obj
)
{
	ObjectProjection data;

	Arrow2D::Object normal_arrow(1);
	normal_arrow[0] = Arrow2D::Inst::Data(ColorF4(0, 1, 0), 16.0f, Ray2D(origin, normal));

	Arrow2D::Object corners(obj.CornerCount());
	for (unsigned int i = 0; i < obj.CornerCount(); i++)
	{
		Point2D	pos = obj.AbsolutePositionOfIndex(i);
		float dot = Point2D::dot(normal, pos - origin);
		data.Consider(dot, i);
		corners[i] = Arrow2D::Inst::Data(ColorF4(0, 0.5f, 0), 16.0f, Line2D(pos, origin + (normal * dot)));
	}

	if (!DebugShow)
	{
		normal_arrow.Data -> DisplayThisFrame = false;
		corners.Data -> DisplayThisFrame = false;
	}

	return data;
}




Physics2D::Collision::ObjectProjectionOverlap::~ObjectProjectionOverlap() { }
Physics2D::Collision::ObjectProjectionOverlap::ObjectProjectionOverlap()
	: Valid(false)
	, Distance(0.0f)
	, Undex0(0xFFFFFFFF)
	, Undex1(0xFFFFFFFF)
{ }

Physics2D::Collision::ObjectProjectionOverlap::ObjectProjectionOverlap(const ObjectProjectionOverlap & other)
	: Valid(other.Valid)
	, Distance(other.Distance)
	, Undex0(other.Undex0)
	, Undex1(other.Undex1)
{ }
Physics2D::Collision::ObjectProjectionOverlap & Physics2D::Collision::ObjectProjectionOverlap::operator=(const ObjectProjectionOverlap & other)
{
	Valid = other.Valid;
	Distance = other.Distance;
	Undex0 = other.Undex0;
	Undex1 = other.Undex1;
	return *this;
}


/*
this only works with convex PolyGons
so the Edge being used for the Normal us the outer most Edge of that PolyGon
so it dosent need to be projected, I just need to know where the Edge is, on the normal
*/


Physics2D::Collision::ObjectProjectionOverlap Physics2D::Collision::ObjectProjectionOverlap::Overlap(
	ObjectProjection proj0,
	ObjectProjection proj1
)
{
	ObjectProjectionOverlap data;
	if (proj0.Box.Intersekt(proj1.Box))
	{
		float diff0 = proj0.Box.Max - proj1.Box.Min;
		float diff1 = proj0.Box.Min - proj1.Box.Max;
		if (fabs(diff0) < fabs(diff1))
		{
			data.Distance = diff0;
			data.Undex0 = proj0.MaxUdx;
			data.Undex1 = proj1.MinUdx;
		}
		else
		{
			data.Distance = diff1;
			data.Undex0 = proj0.MinUdx;
			data.Undex1 = proj1.MaxUdx;
		}
		data.Valid = true;
	}
	return data;
}

Physics2D::Collision::ObjectProjectionOverlap Physics2D::Collision::ObjectProjectionOverlap::Overlap(
	Point2D normal
	, const Object & obj0
	, const Object & obj1
)
{
	return Overlap(
		Collision::ObjectProjection::Project(normal, obj0),
		Collision::ObjectProjection::Project(normal, obj1)
	);
}
