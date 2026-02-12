#include "ChainNeighbours3D.hpp"



ChainNeighbours3D::ChainNeighbours3D() :
	Prev(nullptr),
	Here(),
	Next(nullptr)
{ }
ChainNeighbours3D::ChainNeighbours3D(Point3D * prev, Point3D & here, Point3D * next) :
	Prev(prev),
	Here(here),
	Next(next)
{ }



ChainNeighbours3D ChainNeighbours3D::sHere(Point3D & prev, Point3D & here, Point3D & next)
{
	return ChainNeighbours3D(&prev, here, &next);
}
ChainNeighbours3D ChainNeighbours3D::sPrev(Point3D & prev, Point3D & here)
{
	return ChainNeighbours3D(&prev, here, nullptr);
}
ChainNeighbours3D ChainNeighbours3D::sNext(Point3D & here, Point3D & next)
{
	return ChainNeighbours3D(nullptr, here, &next);
}
