#ifndef  SCENE_OBJECT_HPP
# define SCENE_OBJECT_HPP

# include "Ray3D_Hit.hpp"
# include "ValueType/Trans/3D.hpp"

struct PolyHedraManager;

struct SceneObject
{
	virtual ~SceneObject();
	SceneObject();

	virtual Trans3D		GetTrans() const = 0;
	virtual void		SetTrans(const Trans3D & trans) = 0;

	virtual void	Update() = 0;

	virtual void	ShowWire() = 0;

	virtual void	DisplayObject() = 0;

	virtual Ray3D_Hit	Hit(const RayF3 & ray) const = 0;
};

#endif