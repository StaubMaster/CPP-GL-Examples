#ifndef  UI_CONTROL_BUFFER_DATA_HPP
# define UI_CONTROL_BUFFER_DATA_HPP

# include "ValueType/_Include.hpp"
// include individual

namespace UI
{
namespace Control
{

namespace Main
{
struct BufferData
{
	VectorF2	Pos;

	~BufferData() = default;
	BufferData() = default;
	BufferData(const BufferData & other) = default;
	BufferData & operator=(const BufferData & other) = default;

	BufferData(VectorF2 pos);
};
};

namespace Inst
{
struct BufferData
{
	BoxF2		Box;
	float		Layer;
	ColorF4		Color;
	BoxF2		Bound;

	~BufferData() = default;
	BufferData() = default;
	BufferData(const BufferData & other) = default;
	BufferData & operator=(const BufferData & other) = default;

//	BufferData(BoxF2 box, float layer, ColorF4 color, BoxF2 bound);
	// make from ObjectData
};
};

};
};

#endif