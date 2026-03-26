#include "Physics2D/Collision/Contact.hpp"
#include "Physics2D/Collision/ObjectProjection.hpp"

#include <cmath>

#include "DataShow.hpp"



Physics2D::Collision::ContactData::~ContactData() { }
Physics2D::Collision::ContactData::ContactData()
	: Valid(false)
	, Undex0(0xFFFFFFFF)
	, Undex1(0xFFFFFFFF)
	, Normal()
	, Position()
	, Distance(INFINITY)
{ }

Physics2D::Collision::ContactData::ContactData(const ContactData & other)
	: Valid(other.Valid)
	, Undex0(other.Undex0)
	, Undex1(other.Undex1)
	, Normal(other.Normal)
	, Position(other.Position)
	, Distance(other.Distance)
{ }
Physics2D::Collision::ContactData & Physics2D::Collision::ContactData::operator=(const ContactData & other)
{
	Valid = other.Valid;
	Undex0 = other.Undex0;
	Undex1 = other.Undex1;
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
		obj.AbsolutePositionOfIndex(projection.MinUdx)
	));
	arrows[1] = Arrow2D::Inst::Data(ColorF4(0, 0.25f, 0), 16.0f, Ray2D(
		origin,
		normal * projection.Box.Min
	));

	if (!ObjectProjection::DebugShow)
	{
		arrows.Data -> DisplayThisFrame = false;
	}

	if (projection.Box.Min <= 0.0f)
	{
		arrows[0].Col = ColorF4(0, 0, 1);

		data.Normal = normal;

		data.Distance = projection.Box.Min;
		data.Undex0 = projection.MinUdx;
		data.Undex1 = projection.MinUdx;

		data.Valid = true;
	}

	return data;
}
Physics2D::Collision::ContactData Physics2D::Collision::ContactData::CheckContact(
	const Object & obj0,
	const Object & obj1,
	Point2D normal,
	float timeDelta
)
{
	(void)timeDelta;
	ContactData data;
	Collision::ObjectProjectionOverlap overlap = Collision::ObjectProjectionOverlap::Overlap(normal, obj0, obj1);
	if (overlap.Valid)
	{
		data.Normal = normal;
		data.Distance = overlap.Distance;
		data.Undex0 = overlap.Undex0;
		data.Undex1 = overlap.Undex1;
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
		
		ObjectProjection::DebugShow = (i == ObjectProjection::DebugIndex);
		if (ObjectProjection::DebugShow)
		{
			ObjectProjection::DebugOrigin = o;
		}

		temp = CheckContact(o, n, obj1, timeDelta);
		//ObjectProjection::DebugShow = false;
		//temp = CheckContact(obj0, obj1, n, timeDelta);

		if (temp.Valid)
		{
			contact_count_0--;
			temp.Position = obj1.AbsolutePositionOfIndex(temp.Undex1);
			data.Consider(temp);
		}
	}

	unsigned int contact_count_1 = obj1.CornerCount();
	/*for (unsigned int i = 0; i < obj1.CornerCount(); i++)
	{
		n = obj1.EdgeNormalOfIndex(i);
		temp = CheckContact(obj0, obj1, n, timeDelta);
		if (!temp.Valid) { return ret; }
		if (temp.Valid)
		{
			contact_count_1--;
			temp.Position = obj0.AbsolutePositionOfIndex(temp.Undex0);
			data.Consider(temp);
		}
	}*/
	for (unsigned int i = 0; i < obj1.CornerCount(); i++)
	{
		edge = obj1.EdgeOfIndex(i);
		o = (edge.Pos0 + edge.Pos1) / 2;
		n = obj1.EdgeNormalOfIndex(i);

		ObjectProjection::DebugShow = (i == (ObjectProjection::DebugIndex - obj0.CornerCount()));
		if (ObjectProjection::DebugShow)
		{
			ObjectProjection::DebugOrigin = o;
		}

		temp = CheckContact(o, n, obj0, timeDelta);
		//ObjectProjection::DebugShow = false;
		//temp = CheckContact(obj0, obj1, n, timeDelta);

		if (temp.Valid)
		{
			contact_count_1--;
			temp.Position = obj0.AbsolutePositionOfIndex(temp.Undex0);
			data.Consider(temp);
		}
	}

	if (contact_count_0 == 0 && contact_count_1 == 0)
	{
		ret = data;
	}
	return ret;
}
