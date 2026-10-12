#ifndef  NEW_POLYHEDRA_DATA_TYPE_TRANS_SCALE_COLOR_3D_TYPE_MANAGER_HPP
# define NEW_POLYHEDRA_DATA_TYPE_TRANS_SCALE_COLOR_3D_TYPE_MANAGER_HPP

# include "ObjectData.hpp"
# include "InstanceData.hpp"

# include "NewPolyHedra/Type/Manager.hpp"

namespace TransScaleColor3D
{
typedef ObjectData TypeData;
typedef InstanceData TypeInstanceData;
typedef NewPolyHedra::TypeManager		<TypeData, TypeInstanceData> TypeManager;
};

#endif