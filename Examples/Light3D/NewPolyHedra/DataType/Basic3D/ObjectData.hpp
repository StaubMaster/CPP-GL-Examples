#ifndef  NEW_POLYHEDRA_TEST_TYPE_BASIC_3D_OBJECT_DATA_HPP
# define NEW_POLYHEDRA_TEST_TYPE_BASIC_3D_OBJECT_DATA_HPP

# include "ValueType/Trans/3D.hpp"

namespace Instance
{
namespace Basic3D
{
struct Data;
};
};

namespace Basic3D
{
typedef Instance::Basic3D::Data InstanceData;
struct ObjectData
{
	Trans3D		Trans;
	InstanceData	ToData() const;
};
};

#endif