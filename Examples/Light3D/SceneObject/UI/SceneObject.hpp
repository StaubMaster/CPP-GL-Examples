#ifndef  SCENE_OBJECT_UI_HPP
# define SCENE_OBJECT_UI_HPP

# include "Control/Form.hpp"
# include "SceneObject/UI/PolyHedraObject.hpp"
# include "PropertyControl/LightBase.hpp"
# include "PropertyControl/LightSolar.hpp"
# include "PropertyControl/LightSpot.hpp"

struct SceneObject;

struct SceneObjectUI : public UI::Control::Form
{
	UI::Control::PolyHedraObject	PolyHedraObject;
	UI::Control::LightBase			LightAmbient;
	UI::Control::LightSolar			LightSolar;
	UI::Control::LightSpot			LightSpot;

	~SceneObjectUI();
	SceneObjectUI();

	::SceneObject * Object;
	void	Change(::SceneObject * obj);
	void	Update();
};

#endif