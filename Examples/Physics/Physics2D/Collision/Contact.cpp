#include "Physics2D/Collision/Contact.hpp"

#include <cmath>

#include "DataShow.hpp"



Physics2D::Collision::ContactData::~ContactData() { }
Physics2D::Collision::ContactData::ContactData()
	: Valid(false)
	, Normal()
	, Limit(0.0f)
	, Sum(0.0f)
	, Projections()
{ }

Physics2D::Collision::ContactData::ContactData(const ContactData & other)
	: Valid(other.Valid)
	, Normal(other.Normal)
	, Limit(other.Limit)
	, Sum(other.Sum)
	, Projections(other.Projections.Copy())
{ }
Physics2D::Collision::ContactData & Physics2D::Collision::ContactData::operator=(const ContactData & other)
{
	Valid = other.Valid;
	Normal = other.Normal;
	Limit = other.Limit;
	Sum = other.Sum;
	Projections = other.Projections.Copy();
	return *this;
}





void Physics2D::Collision::ContactData::Consider(const Projection & projection)
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

Physics2D::Collision::ContactData Physics2D::Collision::ContactData::Project(
	Point2D origin,
	Point2D normal,
	const Object & obj
)
{
	ContactData data;
	data.Normal = normal;
	for (unsigned int i = 0; i < obj.CornerCount(); i++)
	{
		Projection projection;
		projection = Projection::Project(origin, normal, obj.AbsolutePositionOfIndex(i));
		data.Consider(projection);
	}
	data.Valid = (data.Projections.Count() != 0);

	if (data.Valid && Projection::DebugShow)
	{
		Arrow2D::Object normal_arrow(1);
		normal_arrow[0] = Arrow2D::Inst::Data(ColorF4(0, 1, 0), 16.0f, Ray2D(origin, normal));

		Arrow2D::Object projection_arrows(data.Projections.Count());
		for (unsigned int i = 0; i < data.Projections.Count(); i++)
		{
			Projection & proj = data.Projections[i];
			projection_arrows[i] = Arrow2D::Inst::Data(
				ColorF4(0, 0.5f, 0), 16.0f, Line2D(
				proj.Position,
				origin + (normal * proj.Distance)
			));
		}
	}

	return data;
}





bool Physics2D::Collision::ContactData::Compare(const ContactData & other) const
{
	if (!other.Valid) { return false; }
	if (!Valid) { return true; }
	return (fabs(other.Limit) < fabs(Limit));
}
void Physics2D::Collision::ContactData::Consider(const ContactData & other)
{
	if (Compare(other))
	{
		*this = other;
	}
}

bool Physics2D::Collision::ContactData::Contact(
	ContactData & data,
	const Object & edges,
	const Object & contacts,
	float timeDelta
)
{
	(void)timeDelta;

	ContactData	temp;

	Line2D		edge;
	Point2D		origin;
	Point2D		normal;

	unsigned int non_contact_count = edges.CornerCount();
	for (unsigned int i = 0; i < edges.CornerCount(); i++)
	{
		edge = edges.EdgeOfIndex(i);
		origin = (edge.Pos0 + edge.Pos1) / 2;
		normal = edges.EdgeNormalOfIndex(i);

		Projection::DebugShow = (&edges == Projection::DebugObject && i == Projection::DebugEdgeUndex);
		if (Projection::DebugShow)
		{
			Projection::DebugOrigin = origin;
		}

		temp = Project(origin, normal, contacts);

		if (temp.Valid)
		{
			non_contact_count--;
			data.Consider(temp);
		}
	}

	return (non_contact_count == 0);
}



Physics2D::Collision::ContactData Physics2D::Collision::ContactData::Contact(
	const Object & obj0,
	const Object & obj1,
	float timeDelta
)
{
	(void)timeDelta;

	ContactData	ret;
	ContactData	data;

	bool all_contact_0 = Contact(data, obj0, obj1, timeDelta);
	bool all_contact_1 = Contact(data, obj1, obj0, timeDelta);

	if (all_contact_0 && all_contact_1)
	{
		ret = data;
	}
	return ret;
}
