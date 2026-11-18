#ifndef  PROPERTY_CONTROL_LIGHT_DIRECTION_HPP
# define PROPERTY_CONTROL_LIGHT_DIRECTION_HPP

# include "UI/NestedProperty.hpp"
# include "UI/ValueType/LightBase.hpp"
# include "UI/ValueType/VectorF3.hpp"

// name conflicts. rename LightDirection to Light
struct LightDirection;

namespace UI
{
struct LightDirection : public NestedProperty
{
	LightBase	Base;
	VectorF3	Dir;

	LightDirection(const char * name);

	::LightDirection * Object;
	void	Syncronize();
	void	Change(::LightDirection * obj);
};
};

#endif