#ifndef  ARROW_2D_INST_DATA_HPP
# define ARROW_2D_INST_DATA_HPP

# include "ValueType/VectorF2.hpp"
# include "ValueType/ColorF4.hpp"
# include "ValueType/Line2D.hpp"
# include "ValueType/Ray2D.hpp"

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
	Data(ColorF4 color, float size, Line2D line);
	Data(ColorF4 color, float size, Ray2D ray);

	Data & operator=(const float & size);
	Data & operator=(const ColorF4 & color);
	Data & operator=(const Line2D & line);
	Data & operator=(const Ray2D & ray);

	void Clear();
};
};
};

#endif