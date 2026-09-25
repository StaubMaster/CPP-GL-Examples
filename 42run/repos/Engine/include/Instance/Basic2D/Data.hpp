#ifndef  INSTANCE_BASIC_2D_DATA_HPP
# define INSTANCE_BASIC_2D_DATA_HPP

# include "ValueType/Matrix/3x3.hpp"
# include "ValueType/Trans/2D.hpp"

namespace Instance
{
namespace Basic2D
{
struct Data
{
	Matrix3x3	Trans;

	~Data();
	Data();

	Data(Trans2D trans);
};
};
};

#endif