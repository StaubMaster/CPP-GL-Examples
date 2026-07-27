#ifndef  NEW_POLYHEDRA_PALLET_FULL_DATA_HPP
# define NEW_POLYHEDRA_PALLET_FULL_DATA_HPP

# include "ValueType/Vector/F3.hpp"
# include "ValueType/Color/F4.hpp"

namespace NewPolyHedra
{
namespace PalletFull
{
struct Data
{
	VectorF3	Position;
	VectorF3	Normal;
	VectorF3	Texture;
	ColorF4		Color;		// interpolate based on alpha ?
//		this would mostly be eighter fully used, or not at all
//		bring back single Color pre Face
//		
//		should Interpolation use alpha of Color or of Texture ?
//		use both and add ?
//		
};
};
};

#endif