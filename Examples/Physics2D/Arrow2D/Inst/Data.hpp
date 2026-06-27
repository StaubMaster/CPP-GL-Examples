#ifndef  ARROW_2D_INST_DATA_HPP
# define ARROW_2D_INST_DATA_HPP

# include "ValueType/VectorF2.hpp"
# include "ValueType/Color/U4.hpp"
# include "ValueType/Line/F2.hpp"
# include "ValueType/Ray/F2.hpp"

namespace Arrow2D
{
namespace Inst
{
struct Data
{
	VectorF2		Origin;
	VectorF2		Target;
	float		Size;
	ColorF4		Color;

	~Data();
	Data();

	Data(ColorF4 color, float size, VectorF2 origin, VectorF2 target);
	Data(ColorF4 color, float size, LineF2 line);
	Data(ColorF4 color, float size, RayF2 ray);

	Data & operator=(const float & size);
	Data & operator=(const ColorF4 & color);
	Data & operator=(const LineF2 & line);
	Data & operator=(const RayF2 & ray);

	void Clear();
};
};
};

#endif