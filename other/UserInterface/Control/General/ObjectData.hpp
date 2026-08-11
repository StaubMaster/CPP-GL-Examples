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
	bool	Remove = false;
	bool	Display = true;

	float		Depth = 0.0f;
	BoxF2		Box; // DisplayBox
	ColorF4		Color;
	BoxF2		Bound; // BoarderBox

	~ObjectData() = default;
	ObjectData() = default;
	ObjectData(const ObjectData & other) = default;
	ObjectData & operator=(const ObjectData & other) = default;
};
};
};

#endif