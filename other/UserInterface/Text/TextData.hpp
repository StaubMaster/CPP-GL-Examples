#ifndef  UI_TEXT_TEXT_DATA_HPP
# define UI_TEXT_TEXT_DATA_HPP

# include "ValueType/Vector/F2.hpp"
# include "ValueType/Box/F2.hpp"
# include "ValueType/Color/F4.hpp"

namespace UI
{

namespace Text
{

struct TextData
{
	BoxF2		Bound;
	ColorF4		Color0;
	ColorF4		Color1;
	VectorF2	CharSize;
	float		Depth;
	float		Padding[1];
};

const static unsigned int	TextsLimit = 64;

struct TextsBufferData
{
	TextData	Array[TextsLimit];
};

};

};

#endif