#ifndef  SCENE_OBJECT_UI_HPP
# define SCENE_OBJECT_UI_HPP

# include "Control/Form.hpp"
# include "SceneObject/UI/PolyHedraObject.hpp"
# include "ValueTypeUI/LightBase.hpp"
# include "ValueTypeUI/LightDirection.hpp"
# include "ValueTypeUI/LightSpot.hpp"

struct SceneObject;

struct SceneObjectUI : public UI::Control_::Form
{
	// dont have these all the time
	// allocate and free as needed
	UI::Control_::PolyHedraObject	PolyHedraObject;
	UI::Control_::LightBase			LightAmbient;
	UI::Control_::LightDirection	LightSolar;
	UI::Control_::LightSpot			LightSpot;

	~SceneObjectUI();
	SceneObjectUI();

	::SceneObject * Object;
	void	Change(::SceneObject * obj);
	void	Syncronize();
};

#endif