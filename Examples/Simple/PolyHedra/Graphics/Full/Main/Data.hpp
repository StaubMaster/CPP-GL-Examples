#ifndef  POLYHEDRA_GRAPHICS_FULL_MAIN_DATA_HPP
# define POLYHEDRA_GRAPHICS_FULL_MAIN_DATA_HPP

# include "ValueType/Point3D.hpp"

namespace PolyHedraFull
{
namespace Main
{
struct Data
{
	Point3D	Position;
	Point3D	Normal;
	Point3D	Texture;
};
};
};

#endif