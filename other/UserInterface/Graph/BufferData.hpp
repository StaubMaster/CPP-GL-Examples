#ifndef  UI_GRAPH_DATA_HPP
# define UI_GRAPH_DATA_HPP

#include "ValueType/_Include.hpp"

namespace UI
{

namespace Graph
{

struct BufferData
{
	BoxF2		Box;
	VectorF2	Pos;
	ColorF4		Col;

	BufferData();
	BufferData(BoxF2 box, VectorF2 Pos, ColorF4 col);
};

};

};

#endif