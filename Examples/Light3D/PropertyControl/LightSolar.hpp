#ifndef  PROPERTY_CONTROL_LIGHT_SOLAR_HPP
# define PROPERTY_CONTROL_LIGHT_SOLAR_HPP

# include "PropertyControl.hpp"
# include "PropertyControl/LightBase.hpp"
# include "PropertyControl/VectorF3.hpp"

struct LightSolar;

namespace UI
{
namespace Control
{
struct LightSolar : public PropertyControl
{
	LightBase	Base;
	VectorF3	Dir;

	~LightSolar();
	LightSolar(const char * name);

	::LightSolar * Object;
	void	Update();
	void	Change(::LightSolar * obj);
};
};
};

#endif