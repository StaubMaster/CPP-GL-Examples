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

	BoxF2		Box;
	float		Layer = 0.0f;
	ColorF4		Color;
	BoxF2		Bound;

	~ObjectData() = default;
	ObjectData() = default;
	ObjectData(const ObjectData & other) = default;
	ObjectData & operator=(const ObjectData & other) = default;
};
};
};

#endif