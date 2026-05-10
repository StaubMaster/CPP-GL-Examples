#ifndef  CHAIN_NEIGHBOURS_3D_HPP
# define CHAIN_NEIGHBOURS_3D_HPP

# include "ValueType/VectorF3.hpp"
# include "Miscellaneous/Container/Member.hpp"

struct ChainNeighbours3D
{
	VectorF3 *	Prev;
	VectorF3		Here;
	VectorF3 *	Next;

	ChainNeighbours3D();
	ChainNeighbours3D(VectorF3 * prev, VectorF3 & here, VectorF3 * next);

	static ChainNeighbours3D sHere(VectorF3 & prev, VectorF3 & here, VectorF3 & next);
	static ChainNeighbours3D sPrev(VectorF3 & prev, VectorF3 & here);
	static ChainNeighbours3D sNext(VectorF3 & here, VectorF3 & next);
};

#endif