#include "Physics2D/Collision/Projection.hpp"
#include <math.h>

#include "Arrow2D/Object.hpp"



Physics2D::Object * Physics2D::Collision::Projection::DebugObject = nullptr;
unsigned int Physics2D::Collision::Projection::DebugEdgeUndex = 0xFFFFFFFF;

bool Physics2D::Collision::Projection::DebugShow = false;
Point2D Physics2D::Collision::Projection::DebugOrigin;



Physics2D::Collision::Projection::~Projection() { }
Physics2D::Collision::Projection::Projection()
	: Position()
	, Distance(INFINITY)
{ }

Physics2D::Collision::Projection::Projection(const Projection & other)
	: Position(other.Position)
	, Distance(other.Distance)
{ }
Physics2D::Collision::Projection & Physics2D::Collision::Projection::operator=(const Projection & other)
{
	Position = other.Position;
	Distance = other.Distance;
	return *this;
}



Physics2D::Collision::Projection Physics2D::Collision::Projection::Project(
	Point2D origin,
	Point2D normal,
	Point2D point
)
{
	Projection data;
	data.Position = point;
	data.Distance = Point2D::dot(normal, point - origin);
	return data;
}
