#ifndef  CHAIN_NEIGHBOURS_3D_HPP
# define CHAIN_NEIGHBOURS_3D_HPP

# include "ValueType/Point3D.hpp"
# include "Miscellaneous/Container/Member.hpp"

struct ChainNeighbours3D
{
	Point3D *	Prev;
	Point3D		Here;
	Point3D *	Next;

	ChainNeighbours3D();
	ChainNeighbours3D(Point3D * prev, Point3D & here, Point3D * next);

	static ChainNeighbours3D sHere(Point3D & prev, Point3D & here, Point3D & next);
	static ChainNeighbours3D sPrev(Point3D & prev, Point3D & here);
	static ChainNeighbours3D sNext(Point3D & here, Point3D & next);
};

#endif