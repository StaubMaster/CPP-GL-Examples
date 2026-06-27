#ifndef  PROPERTY_CONTROL_LIGHT_DIRECTION_HPP
# define PROPERTY_CONTROL_LIGHT_DIRECTION_HPP

# include "PropertyControl.hpp"
# include "PropertyControl/LightBase.hpp"
# include "PropertyControl/VectorF3.hpp"

// name conflicts. rename LightDirection to Light
struct LightDirection;

namespace UI
{
namespace Control
{
struct LightDirection : public PropertyControl
{
	LightBase	Base;
	VectorF3	Dir;

	~LightDirection();
	LightDirection(const char * name);

	::LightDirection * Object;
	void	Update();
	void	Change(::LightDirection * obj);
};
};
};

#endif