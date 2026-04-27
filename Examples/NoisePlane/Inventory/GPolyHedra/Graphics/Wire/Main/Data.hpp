#ifndef  POLYHEDRA_GRAPHICS_WIRE_MAIN_DATA_HPP
# define POLYHEDRA_GRAPHICS_WIRE_MAIN_DATA_HPP

# include "ValueType/Point3D.hpp"
# include "ValueType/ColorF4.hpp"

namespace PolyHedraWire
{
namespace Main
{
struct Data
{
	Point3D		Pos;
	ColorF4		Col;
	Data();
	Data(Point3D pos);
	Data(Point3D pos, ColorF4 col);
};
};
};

#endif