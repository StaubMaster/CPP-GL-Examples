#ifndef  SCENE_OBJECT_CONTROL_SPOT_LIGHT_ENTRY_HPP
# define SCENE_OBJECT_CONTROL_SPOT_LIGHT_ENTRY_HPP

# include "Control/GroupBox.hpp"
# include "PropertyControl/VectorF3.hpp"
# include "PropertyControl/LightSpot.hpp"

struct SpotLightEntry;

namespace UI
{
namespace Control
{
struct SpotLightEntry : public GroupBox
{
	UI::Control::VectorF3	Origin;
	UI::Control::VectorF3	Target;
	UI::Control::LightSpot	Light;

	~SpotLightEntry();
	SpotLightEntry();

	::SpotLightEntry * Object;
	void	Change(::SpotLightEntry * obj);
	void	Update();
};
};
};

#endif