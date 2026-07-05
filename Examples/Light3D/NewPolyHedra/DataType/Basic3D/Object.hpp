#ifndef  NEW_POLYHEDRA_TEST_TYPE_BASIC_3D_OBJECT_HPP
# define NEW_POLYHEDRA_TEST_TYPE_BASIC_3D_OBJECT_HPP

# include "../../Type/Object.hpp"
# include "ObjectData.hpp"

namespace Basic3D
{
typedef NewPolyHedra_Type_Object<
	Basic3D::ObjectData
> Object;
};

#endif