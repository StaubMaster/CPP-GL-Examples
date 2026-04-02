#ifndef  INSTANCE_BASIC_3D_DATA_HPP
# define INSTANCE_BASIC_3D_DATA_HPP

# include "ValueType/Matrix4x4.hpp"
# include "ValueType/Trans3D.hpp"

namespace Instance
{
namespace Basic3D
{
struct Data
{
	Matrix4x4	Trans;
	Matrix4x4	Normal;

	~Data();
	Data();

	Data(Trans3D trans);
};
};
};

#endif