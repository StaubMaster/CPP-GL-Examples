#ifndef  PROPERTY_CONTROL_LIGHT_SPOT_HPP
# define PROPERTY_CONTROL_LIGHT_SPOT_HPP

# include "UI/NestedProperty.hpp"
# include "UI/ValueType/LightBase.hpp"
# include "UI/ValueType/VectorF3.hpp"

struct LightSpot;

namespace UI
{
struct LightSpot : public NestedProperty
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

#endif