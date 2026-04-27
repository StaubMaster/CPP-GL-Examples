#ifndef  POLYHEDRA_DATA_HPP
# define POLYHEDRA_DATA_HPP

# include "PolyHedra.hpp"

# include "ValueType/Point3D.hpp"

struct PolyHedra::Corner
{
	Point3D Position;
	Point3D Normal;
	Corner();
	Corner(Point3D pos);
};
struct PolyHedra::Face
{
	unsigned int udx[3];
	Point3D Normal;
	Face();
	Face(unsigned int u0, unsigned int u1, unsigned int u2);
	bool Check(unsigned int count) const;
};
struct PolyHedra::Edge
{
	unsigned int udx[2];
	Edge();
	Edge(unsigned int u0, unsigned int u1);
	bool Check(unsigned int count) const;
};

#endif