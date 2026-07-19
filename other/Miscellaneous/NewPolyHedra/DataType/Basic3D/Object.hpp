#ifndef  NEW_POLYHEDRA_DATA_TYPE_BASIC_3D_OBJECT_HPP
# define NEW_POLYHEDRA_DATA_TYPE_BASIC_3D_OBJECT_HPP

# include "NewPolyHedra/Type/Object.hpp"
# include "ObjectData.hpp"

namespace NewPolyHedra
{
namespace Basic3D
{
typedef NewPolyHedra::Type_Object<
	ObjectData
> Object;
};
};

#endif