#include "Physics2D/Collision/Contact.hpp"
#include "Physics2D/Collision/ObjectProjection.hpp"

#include <cmath>



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
	Point2D		n;

	for (unsigned int i = 0; i < obj0.CornerCount(); i++)
	{
		n = obj0.EdgeNormalOfIndex(i);
		temp = CheckContact(obj0, obj1, n, timeDelta);
		if (!temp.Valid) { return ret; }
		temp.Position = obj1.AbsolutePositionOfIndex(temp.Undex1);
		data.Consider(temp);
	}

	for (unsigned int i = 0; i < obj1.CornerCount(); i++)
	{
		n = obj1.EdgeNormalOfIndex(i);
		temp = CheckContact(obj0, obj1, n, timeDelta);
		if (!temp.Valid) { return ret; }
		temp.Position = obj0.AbsolutePositionOfIndex(temp.Undex0);
		data.Consider(temp);
	}

	ret = data;
	return ret;
}

