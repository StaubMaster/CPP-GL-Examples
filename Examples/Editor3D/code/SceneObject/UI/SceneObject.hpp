#ifndef  SCENE_OBJECT_UI_HPP
# define SCENE_OBJECT_UI_HPP

# include "Control/Form.hpp"
# include "UI/NestedProperty.hpp"

struct SceneObject;

struct SceneObjectUI : public UI::Control_::Form
{
	UI::NestedProperty *	ObjectUI = nullptr;

	SceneObjectUI();

	::SceneObject * Object;
	void	Change(::SceneObject * obj);
	void	Syncronize();
};

#endif