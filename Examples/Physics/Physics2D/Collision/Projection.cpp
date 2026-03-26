#include "Physics2D/Collision/Projection.hpp"
#include <math.h>

#include "Arrow2D/Object.hpp"



Physics2D::Object * Physics2D::Collision::Projection::DebugObject = nullptr;
unsigned int Physics2D::Collision::Projection::DebugEdgeUndex = 0xFFFFFFFF;

bool Physics2D::Collision::Projection::DebugShow = false;
Point2D Physics2D::Collision::Projection::DebugOrigin;



Physics2D::Collision::Projection::~Projection() { }
Physics2D::Collision::Projection::Projection()
	: Normal()
	, Position()
	, Distance(INFINITY)
{ }

Physics2D::Collision::Projection::Projection(const Projection & other)
	: Normal(other.Normal)
	, Position(other.Position)
	, Distance(other.Distance)
{ }
Physics2D::Collision::Projection & Physics2D::Collision::Projection::operator=(const Projection & other)
{
	Normal = other.Normal;
	Position = other.Position;
	Distance = other.Distance;
	return *this;
}



void Physics2D::Collision::Projection::Consider(const Projection & other)
{
	if (other.Distance < Distance)
	{
		*this = other;
	}
}



Physics2D::Collision::Projection Physics2D::Collision::Projection::Project(
	Point2D origin,
	Point2D normal,
	Point2D point
)
{
	Projection data;

	data.Normal = normal;
	data.Position = point;
	data.Distance = Point2D::dot(normal, point - origin);

	return data;
}

Physics2D::Collision::Projection Physics2D::Collision::Projection::Project(
	Point2D origin,
	Point2D normal,
	const Object & obj
)
{
	Projection data;

	Arrow2D::Object normal_arrow(1);
	normal_arrow[0] = Arrow2D::Inst::Data(ColorF4(0, 1, 0), 16.0f, Ray2D(origin, normal));

	Arrow2D::Object corners(obj.CornerCount());
	for (unsigned int i = 0; i < obj.CornerCount(); i++)
	{
		Projection temp;
		temp = Project(origin, normal, obj.AbsolutePositionOfIndex(i));

		data.Consider(temp);

		corners[i] = Arrow2D::Inst::Data(ColorF4(0, 0.5f, 0), 16.0f, Line2D(temp.Position, origin + (normal * temp.Distance)));
	}

	if (!DebugShow)
	{
		normal_arrow.Data -> DisplayThisFrame = false;
		corners.Data -> DisplayThisFrame = false;
	}

	return data;
}





Physics2D::Collision::ProjectionData::~ProjectionData() { }
Physics2D::Collision::ProjectionData::ProjectionData()
	: Normal()
	, Limit(0.0f)
	, Sum(0.0f)
	, Projections()
{ }

Physics2D::Collision::ProjectionData::ProjectionData(const ProjectionData & other)
	: Normal(other.Normal)
	, Limit(other.Limit)
	, Sum(other.Sum)
	, Projections(other.Projections.Copy())
{ }
Physics2D::Collision::ProjectionData & Physics2D::Collision::ProjectionData::operator=(const ProjectionData & other)
{
	Normal = other.Normal;
	Limit = other.Limit;
	Sum = other.Sum;
	Projections = other.Projections.Copy();
	return *this;
}



void Physics2D::Collision::ProjectionData::Consider(const Projection & projection)
{
	if (projection.Distance <= 0.0f)
	{
		Projections.Insert(projection);
		if (projection.Distance < Limit)
		{
			Limit = projection.Distance;
		}
		Sum += projection.Distance;
	}
}



Physics2D::Collision::ProjectionData Physics2D::Collision::ProjectionData::Project(
	Point2D origin,
	Point2D normal,
	const Object & obj
)
{
	ProjectionData data;
	data.Normal = normal;

	for (unsigned int i = 0; i < obj.CornerCount(); i++)
	{
		Projection projection;
		projection = Projection::Project(origin, normal, obj.AbsolutePositionOfIndex(i));
		data.Consider(projection);
	}

	return data;
}
