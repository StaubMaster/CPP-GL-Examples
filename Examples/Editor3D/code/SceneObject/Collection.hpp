#ifndef  SCENE_OBJECT_COLLECTION_HPP
# define SCENE_OBJECT_COLLECTION_HPP

# include "Generics/Container/Binary.hpp"

struct RayF3;

struct SceneObject;
struct SceneObject_DisplayMode;
struct SceneObject_Collection
{
	Container::Binary<SceneObject*>		Objects;

	void	Clear();
	void	Remove(const SceneObject * obj);

	void	Update();
	void	Display(const SceneObject_DisplayMode & mode);

	unsigned int	FindIndex(const SceneObject * obj) const;

	SceneObject *	FindHit(const RayF3 & ray) const;
};

#endif