#include "PolyHedra/Data.hpp"



PolyHedra::Corner::Corner(VectorF3 pos)
	: Position(pos)
{ }
PolyHedra::Corner::Corner(float x, float y, float z)
	: Position(x, y, z)
{ }



bool PolyHedra::Face::Check(unsigned int count) const
{
	return (idx[0] < count &&
			idx[1] < count &&
			idx[2] < count);
}
PolyHedra::Face::Face(unsigned int idx0, unsigned int idx1, unsigned int idx2)
	: idx{ idx0, idx1, idx2 }
	, Normal()
{ }
PolyHedra::Face::Face(unsigned int idx0, unsigned int idx1, unsigned int idx2, unsigned int normal_group)
	: idx{ idx0, idx1, idx2 }
	, NormalGroup(normal_group)
	, Normal()
{ }



bool PolyHedra::Edge::Check(unsigned int count) const
{
	return (idx[0] < count &&
			idx[1] < count);
}
PolyHedra::Edge::Edge(unsigned int idx0, unsigned int idx1)
	: idx{ idx0, idx1 }
{ }
