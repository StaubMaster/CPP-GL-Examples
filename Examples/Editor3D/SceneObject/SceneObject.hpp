#ifndef  SCENE_OBJECT_HPP
# define SCENE_OBJECT_HPP

# include "ValueType/Trans/3D.hpp"
# include "ValueType/Ray/Hit/F3.hpp"

struct PolyHedraManager;

struct SceneObjectDisplayMode;
struct SceneObject
{
	virtual ~SceneObject();
	SceneObject();

	virtual Trans3D		GetTrans() const = 0;
	virtual void		SetTrans(const Trans3D & trans) = 0;
	// to these with (Trans3D &)

	virtual void	Update() = 0;

	virtual void	ShowWire() = 0;

	virtual void	DisplayObject(const SceneObjectDisplayMode & mode) = 0;

	virtual RayHitF3	Hit(const RayF3 & ray) const = 0;
};

#endif