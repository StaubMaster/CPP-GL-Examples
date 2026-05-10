#ifndef  ARROW_2D_MAIN_DATA_HPP
# define ARROW_2D_MAIN_DATA_HPP

# include "ValueType/VectorF2.hpp"
# include "ValueType/VectorF3.hpp"

namespace Arrow2D
{
namespace Main
{
struct Data
{
	VectorF2		Pos;
	VectorF3		Tex;
	Data();
	Data(VectorF2 pos);
	Data(VectorF2 pos, VectorF3 tex);
};
};
};

#endif