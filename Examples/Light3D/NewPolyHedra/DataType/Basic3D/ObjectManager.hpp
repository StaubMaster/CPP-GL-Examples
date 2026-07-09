#ifndef  NEW_POLYHEDRA_TEST_TYPE_BASIC_3D_OBJECT_MANAGER_HPP
# define NEW_POLYHEDRA_TEST_TYPE_BASIC_3D_OBJECT_MANAGER_HPP

# include "../../Type/ObjectManager.hpp"
# include "ObjectData.hpp"
# include "InstanceData.hpp"

namespace Basic3D
{
typedef NewPolyHedra::Type_ObjectManager<
	Basic3D::ObjectData,
	Basic3D::InstanceData
> ObjectManager;
};

#endif