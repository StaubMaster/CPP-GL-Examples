#ifndef  SCENE_OBJECT_HPP
# define SCENE_OBJECT_HPP

# include "Ray3D_Hit.hpp"

struct SceneObject
{
	virtual ~SceneObject();
	SceneObject();

	virtual void	Update() = 0;

	virtual void	ShowWire() = 0;

	virtual Ray3D_Hit	Hit(const Ray3D & ray) const = 0;
};

#endif