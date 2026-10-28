#ifndef  SCENE_OBJECT_LIGHT_DIRECTION_HPP
# define SCENE_OBJECT_LIGHT_DIRECTION_HPP

# include "SceneObject.hpp"
# include "ValueType/Light/Direction.hpp"

# include "Special/TransScaleColor3D/Logical/Object.hpp"
# include "Special/TransScaleColor3D/Logical/Data.hpp"

struct SceneObjectDisplayMode;
struct SceneObject_LightDirection : public SceneObject
{
	LightDirection *	Light;

	TransScaleColor3D::LogicalObject	Data;

	~SceneObject_LightDirection();
	SceneObject_LightDirection();

	Trans3D		GetTrans() const override;
	void		SetTrans(const Trans3D & trans) override;

	void	Update() override;

	void	ShowWire() override;

	void	DisplayObject(const SceneObjectDisplayMode & mode) override;

	RayHitF3	Hit(const RayF3 & ray) const override;
};

#endif