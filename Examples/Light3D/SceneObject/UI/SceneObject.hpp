#ifndef  SCENE_OBJECT_UI_HPP
# define SCENE_OBJECT_UI_HPP

# include "Control/Form.hpp"
# include "SceneObject/UI/PolyHedraObject.hpp"
# include "SceneObject/UI/SpotLightEntry.hpp"

struct SceneObject;

struct SceneObjectUI : public UI::Control::Form
{
	UI::Control::PolyHedraObject	PolyHedraObject;
	UI::Control::SpotLightEntry		SpotLightEntry;

	~SceneObjectUI();
	SceneObjectUI();

	::SceneObject * Object;
	void	Change(::SceneObject * obj);
	void	Update();
};

#endif