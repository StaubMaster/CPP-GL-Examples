#include "Physics2D/Collision/ObjectProjection.hpp"
#include <math.h>

#include "Arrow2D/Object.hpp"



Physics2D::Object * Physics2D::Collision::ObjectProjection::DebugObject = nullptr;
unsigned int Physics2D::Collision::ObjectProjection::DebugEdgeUndex = 0xFFFFFFFF;

bool Physics2D::Collision::ObjectProjection::DebugShow = false;
Point2D Physics2D::Collision::ObjectProjection::DebugOrigin;



Physics2D::Collision::ObjectProjection::~ObjectProjection() { }
Physics2D::Collision::ObjectProjection::ObjectProjection()
	: Distance()
	, Undex(0xFFFFFFFF)
{ }

Physics2D::Collision::ObjectProjection::ObjectProjection(const ObjectProjection & other)
	: Distance(other.Distance)
	, Undex(other.Undex)
{ }
Physics2D::Collision::ObjectProjection & Physics2D::Collision::ObjectProjection::operator=(const ObjectProjection & other)
{
	Distance = other.Distance;
	Undex = other.Undex;
	return *this;
}

void Physics2D::Collision::ObjectProjection::Consider(float val, unsigned int idx)
{
	if (Undex == 0xFFFFFFFF || val < Distance)
	{
		Undex = idx;
		Distance = val;
	}
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
