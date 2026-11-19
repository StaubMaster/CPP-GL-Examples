#ifndef  SCENE_OBJECT_HPP
# define SCENE_OBJECT_HPP

# include "ValueType/Trans/3D.hpp"
# include "ValueType/Ray/Hit/F3.hpp"

struct PolyHedraManager;

struct SceneObject_DisplayMode;
struct SceneObject
{
	virtual ~SceneObject() = default;
	SceneObject() = default;

	virtual Trans3D		GetTrans() const = 0;
	virtual void		SetTrans(const Trans3D & trans) = 0;
	// to these with (Trans3D &)

	virtual void	Update() = 0;

	virtual void	ShowWire() = 0;

	virtual void	DisplayObject(const SceneObject_DisplayMode & mode) = 0;
	// this kind of interferes with NewPolyHedra::DisplayObject
	// rename to just Display

	virtual RayHitF3	Hit(const RayF3 & ray) const = 0;
};

#endif