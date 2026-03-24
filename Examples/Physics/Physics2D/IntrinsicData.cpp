#include "Physics2D/IntrinsicData.hpp"
#include "PolyGon/Object.hpp"
#include "ValueType/AxisBox2D.hpp"



void Physics2D::IntrinsicData::Calculate_Area(const PolyGon::Object &polygon)
{
	unsigned int n = polygon.Corners.Count();
	Area = 0.0f;
	for (unsigned int i = 0; i < n; i++)
	{
		Point2D p0;
		Point2D p1;
		if (i == 0)
		{
			p0 = polygon.Corners[n - 1].Pos;
			p1 = polygon.Corners[0 - 0].Pos;
		}
		else
		{
			p0 = polygon.Corners[i - 1].Pos;
			p1 = polygon.Corners[i - 0].Pos;
		}
		float area = Point2D::cross(p0, p1);
		Area += area;
	}
	Area *= (1.0 / 2.0f);
	Mass = Area * Density;
}
void Physics2D::IntrinsicData::Calculate_CenterOfMass(const PolyGon::Object & polygon)
{
	unsigned int n = polygon.Corners.Count();
	CenterOfMass = Point2D();
	for (unsigned int i = 0; i < n; i++)
	{
		Point2D p0;
		Point2D p1;
		if (i == 0)
		{
			p0 = polygon.Corners[n - 1].Pos;
			p1 = polygon.Corners[0 - 0].Pos;
		}
		else
		{
			p0 = polygon.Corners[i - 1].Pos;
			p1 = polygon.Corners[i - 0].Pos;
		}
		float area = Point2D::cross(p0, p1);
		CenterOfMass += (p0 + p1) * area;
	}
	CenterOfMass *= (1.0 / (6.0f * Area));
}
void Physics2D::IntrinsicData::Calculate_MomentOfInertia(const PolyGon::Object & polygon)
{
	unsigned int n = polygon.Corners.Count();
	/* Moment of Inertia of Triangle
		I = (1/6) * m * ((P ∙ P) + (P ∙ Q) + (Q ∙ Q))
		m = ρ * A
		A = (1/2) * (P × Q)
	*/
	MomentOfInertia = 0.0f;
	for (unsigned int i = 0; i < n; i++)
	{
		Point2D p0;
		Point2D p1;
		if (i == 0)
		{
			p0 = polygon.Corners[n - 1].Pos;
			p1 = polygon.Corners[0 - 0].Pos;
		}
		else
		{
			p0 = polygon.Corners[i - 1].Pos;
			p1 = polygon.Corners[i - 0].Pos;
		}
		//p0 = p0 - CenterOfMass;
		//p1 = p1 - CenterOfMass;
		float area = Point2D::cross(p0, p1);
		float moment_of_inertia_of_triangle = 0.0f;
		moment_of_inertia_of_triangle += Point2D::dot(p0, p0);
		moment_of_inertia_of_triangle += Point2D::dot(p0, p1);
		moment_of_inertia_of_triangle += Point2D::dot(p1, p1);
		MomentOfInertia += area * moment_of_inertia_of_triangle;
	}
	MomentOfInertia *= ((Mass / Area) / 12.0f);
}

void Physics2D::IntrinsicData::Calculate(const PolyGon::Object & polygon)
{
	Calculate_Area(polygon);
	Calculate_CenterOfMass(polygon);
	Calculate_MomentOfInertia(polygon);

	AxisBox2D box = polygon.ToAxisBox();
	Point2D size = box.Size();
	// Box Center
	// Ic = (1/12) * m * (w^2 + h^2)
	BoxCMomentOfInertia = (Mass / 12.0f) * ((size.X * size.X) + (size.Y * size.Y));
	// Box Side W Middle
	// Ic = (1/12) * m * (w^2 + 4 * h^2)
	BoxWMomentOfInertia = (Mass / 12.0f) * ((size.X * size.X) + 4 * (size.Y * size.Y));
	// Box Side H Middle
	// Ic = (1/12) * m * (4 * w^2 + h^2)
	BoxHMomentOfInertia = (Mass / 12.0f) * (4 * (size.X * size.X) + (size.Y * size.Y));
}



#include <iostream>
#include "DataShow.hpp"
std::ostream & operator<<(std::ostream & s, const Physics2D::IntrinsicData & data)
{
	s << "Intrinsic:\n";
	s << "Mass    : " << data.Mass << " kg\n";
	s << "Area    : " << data.Area << " dm^2\n";
	s << "Density : " << data.Density << " kg/dm^2\n";
	s << "Center of Mass    : " << data.CenterOfMass << "\n";
	s << "Moment of Inertia : " << data.MomentOfInertia << " kg*dm^2\n";
	s << "Box C Moment of Inertia : " << data.BoxCMomentOfInertia << " kg*dm^2\n";
	s << "Box W Moment of Inertia : " << data.BoxWMomentOfInertia << " kg*dm^2\n";
	s << "Box H Moment of Inertia : " << data.BoxHMomentOfInertia << " kg*dm^2\n";
	s << '\n';
	return s;
}

