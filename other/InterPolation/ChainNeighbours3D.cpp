#include "ChainNeighbours3D.hpp"



ChainNeighbours3D::ChainNeighbours3D() :
	Prev(nullptr),
	Here(),
	Next(nullptr)
{ }
ChainNeighbours3D::ChainNeighbours3D(VectorF3 * prev, VectorF3 & here, VectorF3 * next) :
	Prev(prev),
	Here(here),
	Next(next)
{ }



ChainNeighbours3D ChainNeighbours3D::sHere(VectorF3 & prev, VectorF3 & here, VectorF3 & next)
{
	return ChainNeighbours3D(&prev, here, &next);
}
ChainNeighbours3D ChainNeighbours3D::sPrev(VectorF3 & prev, VectorF3 & here)
{
	return ChainNeighbours3D(&prev, here, nullptr);
}
ChainNeighbours3D ChainNeighbours3D::sNext(VectorF3 & here, VectorF3 & next)
{
	return ChainNeighbours3D(nullptr, here, &next);
}
