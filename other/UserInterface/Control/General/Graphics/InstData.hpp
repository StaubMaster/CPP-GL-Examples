#ifndef  UI_CONTROL_GRAPHICS_INST_DATA_HPP
# define UI_CONTROL_GRAPHICS_INST_DATA_HPP

# include "ValueType/Box/F2.hpp"
# include "ValueType/Color/F4.hpp"

namespace UI
{
namespace Control
{
namespace Inst
{
struct Data
{
	BoxF2		Box;
	float		Layer = 0.0f;
	ColorF4		Color;
	BoxF2		Bound;

	~Data() = default;
	Data() = default;
	Data(const Data & other) = default;
	Data & operator=(const Data & other) = default;

//	Data(BoxF2 box, float layer, ColorF4 color, BoxF2 bound);
	// make from ObjectData
};
};
};
};

#endif