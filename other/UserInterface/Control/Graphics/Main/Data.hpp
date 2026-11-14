#ifndef  UI_CONTROL_GRAPHICS_MAIN_DATA_HPP
# define UI_CONTROL_GRAPHICS_MAIN_DATA_HPP

# include "ValueType/Vector/F2.hpp"

namespace UI
{
namespace ControlGraphics
{
namespace Main
{
struct Data
{
	VectorF2	Pos;

	~Data() = default;
	Data() = default;
	Data(const Data & other) = default;
	Data & operator=(const Data & other) = default;

	Data(const VectorF2 & pos);
};
};
};
};

#endif