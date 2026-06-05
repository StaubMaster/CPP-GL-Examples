#ifndef  UI_CONTROL_BUFFER_DATA_HPP
# define UI_CONTROL_BUFFER_DATA_HPP

# include "ValueType/_Include.hpp"

namespace UI
{

namespace Control
{

namespace Main
{
struct BufferData
{
	VectorF2	Pos;

	BufferData();
	BufferData(VectorF2 pos);
};
};

namespace Inst
{
struct BufferData
{
	BoxF2		Box;
	float		Layer;
	ColorF4		Col;

	BufferData();
	BufferData(BoxF2 box, float layer, ColorF4 col);
};
};

};

};

#endif