#ifndef  NEW_POLYHEDRA_TEST_TYPE_TRANS_SCALE_COLOR_3D_OBJECT_MANAGER_HPP
# define NEW_POLYHEDRA_TEST_TYPE_TRANS_SCALE_COLOR_3D_OBJECT_MANAGER_HPP

# include "../../Type/ObjectManager.hpp"
# include "ObjectData.hpp"
# include "InstanceData.hpp"

namespace TransScaleColor3D
{
typedef NewPolyHedra::Type_ObjectManager<
	TransScaleColor3D::ObjectData,
	TransScaleColor3D::InstanceData
> ObjectManager;
};

#endif