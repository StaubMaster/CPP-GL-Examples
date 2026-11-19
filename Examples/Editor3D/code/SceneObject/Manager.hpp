#ifndef  SCENE_OBJECT_MANAGER_HPP
# define SCENE_OBJECT_MANAGER_HPP

# include "SceneObject/DisplayMode.hpp"
# include "SceneObject/Collection.hpp"

struct SceneObject;
struct SceneObject_Manager
{
	SceneObject_DisplayMode		DisplayMode;
	SceneObject_Collection		Collection;

	SceneObject *	Selected = nullptr;
	SceneObject *	Hovering = nullptr;

	void	RemoveSelected();

	void	Display();
};

#endif