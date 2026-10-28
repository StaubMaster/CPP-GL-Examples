#ifndef  SCENE_OBJECT_COLLECTION_HPP
# define SCENE_OBJECT_COLLECTION_HPP

# include "Generics/Container/Binary.hpp"

struct RayF3;

struct SceneObject;
struct SceneObjectDisplayMode;
struct SceneObjectCollection
{
	Container::Binary<SceneObject*>		Objects;

	SceneObject *	FindObject(const RayF3 & ray) const;
	unsigned int	FindObjectIndex(const SceneObject * obj) const;

	void	Clear();
	void	Update();
	void	Display(const SceneObjectDisplayMode & mode);
};

#endif