#ifndef  NEW_POLYHEDRA_PALLET_FULL_MAKE_HPP
# define NEW_POLYHEDRA_PALLET_FULL_MAKE_HPP

# include "Data.hpp"

class PolyHedra;

namespace Container
{
template <typename T> struct Array;
};

namespace NewPolyHedra
{
namespace PalletFull
{
Container::Array<PalletFull::Triangle>	Make(const PolyHedra & polyhedra);
};
};

#endif