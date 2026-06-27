#ifndef  UI_CONTROL_OBJECT_DATA_HPP
# define UI_CONTROL_OBJECT_DATA_HPP

# include "ValueType/Box/F2.hpp"
# include "ValueType/Color/F4.hpp"

namespace UI
{
namespace Control
{
struct ObjectData
{
	bool	Remove;
	bool	Display;

	// this is Inst::BufferData. just put that here ?
	BoxF2		Box;
	float		Layer;
	ColorF4		Color;

	~ObjectData();
	ObjectData();
	ObjectData(const ObjectData & other);
	ObjectData & operator=(const ObjectData & other);
};
};
};

#endif