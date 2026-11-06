#ifndef  UI_TEXT_GRAPHICS_INST_DATA_HPP
# define UI_TEXT_GRAPHICS_INST_DATA_HPP

# include "ValueType/_Include.hpp"

namespace UI
{
namespace Text
{
namespace Inst
{
struct Data
{
	VectorF2		TextPos;
	unsigned int	CharIdx;
	unsigned int	TextIdx;
	~Data() = default;
	Data() = default;
	Data(const Data & other) = default;
	Data & operator=(const Data & other) = default;
};
};
};
};

#endif