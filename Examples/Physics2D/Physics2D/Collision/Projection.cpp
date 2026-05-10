#include "Physics2D/Collision/Projection.hpp"
#include <math.h>

#include "Arrow2D/Object.hpp"



Physics2D::Object * Physics2D::Collision::Projection::DebugObject = nullptr;
unsigned int Physics2D::Collision::Projection::DebugEdgeUndex = 0xFFFFFFFF;

bool Physics2D::Collision::Projection::DebugShow = false;
VectorF2 Physics2D::Collision::Projection::DebugOrigin;



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
	VectorF2 origin,
	VectorF2 normal,
	VectorF2 point
)
{
	Projection data;
	data.Position = point;
	data.Distance = VectorF2::dot(normal, point - origin);
	return data;
}
