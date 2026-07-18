#ifndef  PROPERTY_CONTROL_LIGHT_SPOT_HPP
# define PROPERTY_CONTROL_LIGHT_SPOT_HPP

# include "PropertyControl.hpp"
# include "ValueTypeUI/LightBase.hpp"
# include "ValueTypeUI/VectorF3.hpp"

struct LightSpot;

namespace UI
{
namespace Control
{
struct LightSpot : public PropertyControl
{
	LightBase	Base;
	VectorF3	Pos;
	VectorF3	Dir;

	~LightSpot();
	LightSpot(const char * name);

	::LightSpot * Object;
	void	Update();
	void	Change(::LightSpot * obj);
};
};
};

#endif