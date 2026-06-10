#ifndef  OBJECT_CONTROL_LIGHT_SPOT_HPP
# define OBJECT_CONTROL_LIGHT_SPOT_HPP

# include "Control/GroupBox.hpp"
# include "ObjectControl/LightBase.hpp"
# include "ObjectControl/VectorF3.hpp"

struct LightSpot;

namespace UI
{
namespace Control
{
struct LightSpot : public GroupBox
{
	LightBase	Base;
	VectorF3	Pos;
	VectorF3	Dir;

	~LightSpot();
	LightSpot();

	::LightSpot * Object;
	void	Change(::LightSpot * obj);
};
};
};

#endif