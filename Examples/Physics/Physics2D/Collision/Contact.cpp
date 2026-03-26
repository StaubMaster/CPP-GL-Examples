#include "Physics2D/Collision/Contact.hpp"
#include "Physics2D/Collision/ObjectProjection.hpp"

#include <cmath>

#include "DataShow.hpp"



Physics2D::Collision::ContactData::~ContactData() { }
Physics2D::Collision::ContactData::ContactData()
	: Valid(false)
	, Normal()
	, Position()
	, Distance(INFINITY)
{ }

Physics2D::Collision::ContactData::ContactData(const ContactData & other)
	: Valid(other.Valid)
	, Normal(other.Normal)
	, Position(other.Position)
	, Distance(other.Distance)
{ }
Physics2D::Collision::ContactData & Physics2D::Collision::ContactData::operator=(const ContactData & other)
{
	Valid = other.Valid;
	Normal = other.Normal;
	Position = other.Position;
	Distance = other.Distance;
	return *this;
}



bool Physics2D::Collision::ContactData::Compare(const ContactData & other) const
{
	if (!other.Valid) { return false; }
	if (!Valid) { return true; }
	return (fabs(other.Distance) < fabs(Distance));
}
void Physics2D::Collision::ContactData::Consider(const ContactData & other)
{
	if (Compare(other))
	{
		*this = other;
	}
}



Physics2D::Collision::ContactData Physics2D::Collision::ContactData::CheckContact(
	Point2D origin,
	Point2D normal,
	const Object & obj,
	float timeDelta
)
{
	(void)timeDelta;

	ContactData data;
	ObjectProjection projection = ObjectProjection::Project(origin, normal, obj);

	Arrow2D::Object arrows(2);
	arrows[0] = Arrow2D::Inst::Data(ColorF4(1, 0, 0), 16.0f, Line2D(
		obj.ExtData.Now.Pos,
		obj.AbsolutePositionOfIndex(projection.Undex)
	));
	arrows[1] = Arrow2D::Inst::Data(ColorF4(0, 0.25f, 0), 16.0f, Ray2D(
		origin,
		normal * projection.Distance
	));

	if (!ObjectProjection::DebugShow)
	{
		arrows.Data -> DisplayThisFrame = false;
	}

	if (projection.Distance <= 0.0f)
	{
		arrows[0].Col = ColorF4(0, 0, 1);

		data.Normal = normal;

		data.Distance = projection.Distance;
		data.Position = obj.AbsolutePositionOfIndex(projection.Undex);

		data.Valid = true;
	}

	return data;
}

Physics2D::Collision::ContactData Physics2D::Collision::ContactData::CheckContact(
	const Object & obj0,
	const Object & obj1,
	float timeDelta
)
{
	(void)timeDelta;

	ContactData	ret;
	ContactData	data;
	ContactData	temp;
	Line2D		edge;
	Point2D		o;
	Point2D		n;

	unsigned int contact_count_0 = obj0.CornerCount();
	for (unsigned int i = 0; i < obj0.CornerCount(); i++)
	{
		edge = obj0.EdgeOfIndex(i);
		o = (edge.Pos0 + edge.Pos1) / 2;
		n = obj0.EdgeNormalOfIndex(i);

		ObjectProjection::DebugShow = (&obj0 == ObjectProjection::DebugObject && i == ObjectProjection::DebugEdgeUndex);
		if (ObjectProjection::DebugShow)
		{
			ObjectProjection::DebugOrigin = o;
		}

		temp = CheckContact(o, n, obj1, timeDelta);

		if (temp.Valid)
		{
			contact_count_0--;
			data.Consider(temp);
		}
	}

	unsigned int contact_count_1 = obj1.CornerCount();
	for (unsigned int i = 0; i < obj1.CornerCount(); i++)
	{
		edge = obj1.EdgeOfIndex(i);
		o = (edge.Pos0 + edge.Pos1) / 2;
		n = obj1.EdgeNormalOfIndex(i);

		ObjectProjection::DebugShow = (&obj1 == ObjectProjection::DebugObject && i == ObjectProjection::DebugEdgeUndex);
		if (ObjectProjection::DebugShow)
		{
			ObjectProjection::DebugOrigin = o;
		}

		temp = CheckContact(o, n, obj0, timeDelta);

		if (temp.Valid)
		{
			contact_count_1--;
			data.Consider(temp);
		}
	}

	if (contact_count_0 == 0 && contact_count_1 == 0)
	{
		ret = data;
	}
	return ret;
}
