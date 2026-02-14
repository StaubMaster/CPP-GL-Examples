#include "Collision2D.hpp"
#include "PolyGon/Data.hpp"
#include <cmath>



unsigned int Collision2D::TransPolyGon::Corners() const { return PolyGon.Corners.Count(); }
Point2D Collision2D::TransPolyGon::TransCorner(unsigned int idx) const
{
	return Trans.Rot.rotateBack(PolyGon.Corners[idx].Pos) + Trans.Pos;
}

Collision2D::TransPolyGon::~TransPolyGon() { }
Collision2D::TransPolyGon::TransPolyGon(const TransPolyGon & other)
	: PolyGon(other.PolyGon)
	, Trans(other.Trans)
{ }

Collision2D::TransPolyGon::TransPolyGon(const ::PolyGon & poly_gon, const ::Trans2D & trans)
	: PolyGon(poly_gon)
	, Trans(trans)
{ }
Collision2D::TransPolyGon::TransPolyGon(const ::PolyGon * poly_gon, const ::Trans2D & trans)
	: PolyGon(*poly_gon)
	, Trans(trans)
{ }





Collision2D::PolyGonProjectionData::~PolyGonProjectionData() { }
Collision2D::PolyGonProjectionData::PolyGonProjectionData()
	: Box()
	, MinUdx(0xFFFFFFFF)
	, MaxUdx(0xFFFFFFFF)
{ }

Collision2D::PolyGonProjectionData::PolyGonProjectionData(const PolyGonProjectionData & other)
	: Box(other.Box)
	, MinUdx(other.MinUdx)
	, MaxUdx(other.MaxUdx)
{ }
Collision2D::PolyGonProjectionData & Collision2D::PolyGonProjectionData::operator=(const PolyGonProjectionData & other)
{
	Box = other.Box;
	MinUdx = other.MinUdx;
	MaxUdx = other.MaxUdx;
	return *this;
}

void Collision2D::PolyGonProjectionData::Consider(float val, unsigned int idx)
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

Collision2D::PolyGonProjectionData Collision2D::PolyGonProjectionData::Project(
	const TransPolyGon & poly_gon,
	Point2D normal
)
{
	PolyGonProjectionData data;
	for (unsigned int i = 0; i < poly_gon.Corners(); i++)
	{
		Point2D	pos = poly_gon.TransCorner(i);
		float dot = Point2D::dot(normal, pos);
		data.Consider(dot, i);
	}
	return data;
}





Collision2D::PolyGonContactData::~PolyGonContactData() { }
Collision2D::PolyGonContactData::PolyGonContactData()
	: Valid(false)
	, Normal()
	, Distance(INFINITY)
	, Contact0Udx(0xFFFFFFFF)
	, Contact1Udx(0xFFFFFFFF)
{ }

Collision2D::PolyGonContactData::PolyGonContactData(const PolyGonContactData & other)
	: Valid(other.Valid)
	, Normal(other.Normal)
	, Distance(other.Distance)
	, Contact0Udx(other.Contact0Udx)
	, Contact1Udx(other.Contact1Udx)
{ }
Collision2D::PolyGonContactData & Collision2D::PolyGonContactData::operator=(const PolyGonContactData & other)
{
	Valid = other.Valid;
	Normal = other.Normal;
	Distance = other.Distance;
	Contact0Udx = other.Contact0Udx;
	Contact1Udx = other.Contact1Udx;
	return *this;
}



bool Collision2D::PolyGonContactData::Compare(const PolyGonContactData & other) const
{
	if (!other.Valid) { return false; }
	if (!Valid) { return true; }
	return (fabs(other.Distance) < fabs(Distance));
}


Collision2D::PolyGonContactData Collision2D::PolyGonContactData::Check(
	const TransPolyGon & poly_gon_0,
	const TransPolyGon & poly_gon_1,
	Point2D normal
)
{
	PolyGonContactData data;
	data.Normal = normal;

	PolyGonProjectionData projData0 = PolyGonProjectionData::Project(poly_gon_0, normal);
	PolyGonProjectionData projData1 = PolyGonProjectionData::Project(poly_gon_1, normal);

	if (projData0.Box.Intersekt(projData1.Box))
	{
		float diff0 = projData0.Box.Max - projData1.Box.Min;
		float diff1 = projData0.Box.Min - projData1.Box.Max;
		if (fabs(diff0) < fabs(diff1))
		{
			data.Distance = diff0;
			data.Contact0Udx = projData0.MaxUdx;
			data.Contact1Udx = projData1.MinUdx;
		}
		else
		{
			data.Distance = diff1;
			data.Contact0Udx = projData0.MinUdx;
			data.Contact1Udx = projData1.MaxUdx;
		}
		data.Valid = true;
	}
	return data;
}

Collision2D::PolyGonContactData Collision2D::PolyGonContactData::Check(
	const TransPolyGon & poly_gon_0,
	const TransPolyGon & poly_gon_1
)
{
	PolyGonContactData	ret;
	PolyGonContactData	data;
	PolyGonContactData	temp;
	Point2D n;

/*
	lots of repetition
	get a normal to check
	calculate the Contacts for that normal
	if no contact, then there is no contact between the bodys
	if there is contact, then check if its "better"
*/

	for (unsigned int i = 0; i < poly_gon_0.PolyGon.Sides.Count(); i++)
	{
		Point2D pos0 = poly_gon_0.TransCorner(poly_gon_0.PolyGon.Sides[i].Corner0.Udx);
		Point2D pos1 = poly_gon_0.TransCorner(poly_gon_0.PolyGon.Sides[i].Corner1.Udx);
		Point2D pos2 = poly_gon_0.TransCorner(poly_gon_0.PolyGon.Sides[i].Corner2.Udx);

		n = (pos1 - pos0).perpendicular0();
		temp = Check(poly_gon_0, poly_gon_1, n);
		if (!temp.Valid) { return ret; }
		if (data.Compare(temp)) { data = temp; }

		n = (pos2 - pos1).perpendicular0();
		temp = Check(poly_gon_0, poly_gon_1, n);
		if (!temp.Valid) { return ret; }
		if (data.Compare(temp)) { data = temp; }

		n = (pos0 - pos2).perpendicular0();
		temp = Check(poly_gon_0, poly_gon_1, n);
		if (!temp.Valid) { return ret; }
		if (data.Compare(temp)) { data = temp; }
	}

	for (unsigned int i = 0; i < poly_gon_1.PolyGon.Sides.Count(); i++)
	{
		Point2D pos0 = poly_gon_1.TransCorner(poly_gon_1.PolyGon.Sides[i].Corner0.Udx);
		Point2D pos1 = poly_gon_1.TransCorner(poly_gon_1.PolyGon.Sides[i].Corner1.Udx);
		Point2D pos2 = poly_gon_1.TransCorner(poly_gon_1.PolyGon.Sides[i].Corner2.Udx);

		n = (pos1 - pos0).perpendicular0();
		temp = Check(poly_gon_0, poly_gon_1, n);
		if (!temp.Valid) { return ret; }
		if (data.Compare(temp)) { data = temp; }

		n = (pos2 - pos1).perpendicular0();
		temp = Check(poly_gon_0, poly_gon_1, n);
		if (!temp.Valid) { return ret; }
		if (data.Compare(temp)) { data = temp; }

		n = (pos0 - pos2).perpendicular0();
		temp = Check(poly_gon_0, poly_gon_1, n);
		if (!temp.Valid) { return ret; }
		if (data.Compare(temp)) { data = temp; }
	}

	ret = data;
	return ret;
}
