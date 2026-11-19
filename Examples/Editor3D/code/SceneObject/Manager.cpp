#include "SceneObject/Manager.hpp"



void SceneObject_Manager::RemoveSelected()
{
	Collection.Remove(Selected);
	if (Hovering == Selected)
	{
		Hovering = nullptr;
	}
	Selected = nullptr;
}

void SceneObject_Manager::Display()
{
	Collection.Display(DisplayMode);
}
