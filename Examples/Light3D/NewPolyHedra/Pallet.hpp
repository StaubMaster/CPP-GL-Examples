#ifndef  NEW_POLYHEDRA_PALLET_HPP
# define NEW_POLYHEDRA_PALLET_HPP

# include "Graphics/Buffer/Array.hpp"

class PolyHedra;

struct NewPolyHedra_Pallet
{
	PolyHedra *			Object;
	::Buffer::Array		Buffer;
	//					Textures;
	NewPolyHedra_Pallet();
};

#endif