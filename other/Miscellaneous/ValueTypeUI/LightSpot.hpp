#ifndef  PROPERTY_CONTROL_LIGHT_SPOT_HPP
# define PROPERTY_CONTROL_LIGHT_SPOT_HPP

# include "PropertyControl.hpp"
# include "ValueTypeUI/LightBase.hpp"
# include "ValueTypeUI/VectorF3.hpp"

struct LightSpot;

namespace UI
{
namespace Control_
{
struct LightSpot : public PropertyControl
{
	LightBase	Base;
	VectorF3	Pos;
	VectorF3	Dir;

	LightSpot(const char * name);

	::LightSpot * Object;
	void	Syncronize();
	void	Change(::LightSpot * obj);
};
};
};

#endif