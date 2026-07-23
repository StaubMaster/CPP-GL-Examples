#ifndef  NEW_POLYHEDRA_PALLET_WIRE_DATA_HPP
# define NEW_POLYHEDRA_PALLET_WIRE_DATA_HPP

# include "ValueType/Vector/F3.hpp"
# include "ValueType/Color/F4.hpp"

namespace NewPolyHedra
{
namespace PalletWire
{
struct Data
{
	VectorF3	Pos;
	ColorF4		Col;
};
};
};

#endif