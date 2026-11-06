#ifndef  UI_TEXT_GRAPHICS_MAIN_DATA_HPP
# define UI_TEXT_GRAPHICS_MAIN_DATA_HPP

# include "ValueType/_Include.hpp"

namespace UI
{
namespace Text
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
	Data(VectorF2 pos);
};
};
};
};

#endif