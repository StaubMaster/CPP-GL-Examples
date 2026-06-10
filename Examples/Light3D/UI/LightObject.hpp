#ifndef  UI_LIGHT_OBJECT_HPP
# define UI_LIGHT_OBJECT_HPP

# include "ControlsInclude.hpp"
# include "ObjectControl/VectorF3.hpp"
# include "ObjectControl/LightSpot.hpp"

struct SpotLightEntry;

namespace UI
{
struct SpotLightEntry : public UI::Control::Form
{
	UI::Control::VectorF3		Position;
	UI::Control::VectorF3		Target;
	UI::Control::LightSpot		Light;

	~SpotLightEntry();
	SpotLightEntry();

	::SpotLightEntry * Object;
	void	Change(::SpotLightEntry * obj);
};
};

#endif