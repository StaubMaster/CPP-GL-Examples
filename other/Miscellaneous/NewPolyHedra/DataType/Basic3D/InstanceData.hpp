#ifndef  NEW_POLYHEDRA_DATA_TYPE_BASIC_3D_INSTANCE_DATA_HPP
# define NEW_POLYHEDRA_DATA_TYPE_BASIC_3D_INSTANCE_DATA_HPP

# include "ValueType/Matrix/4x4.hpp"

namespace NewPolyHedra
{
namespace Basic3D
{
struct ObjectData;
struct InstanceData
{
	Matrix4x4	Trans;
	Matrix4x4	Normal;
	~InstanceData() = default;
	InstanceData() = default;
	InstanceData(const ObjectData & data);
};
};
};

#endif