#ifndef  POLYGON_GRAPHICS_FULL_MAIN_DATA_HPP
# define POLYGON_GRAPHICS_FULL_MAIN_DATA_HPP

# include "ValueType/Vector/F2.hpp"
# include "ValueType/Color/F4.hpp"

namespace PolyGonFull
{
namespace Main
{
struct Data
{
	VectorF2	Pos;
	ColorF4		Col;
	Data();
	Data(VectorF2 pos);
	Data(VectorF2 pos, ColorF4 col);
};
};
};

#endif