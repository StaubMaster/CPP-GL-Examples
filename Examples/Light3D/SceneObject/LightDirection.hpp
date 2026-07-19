#ifndef  SCENE_OBJECT_LIGHT_DIRECTION_HPP
# define SCENE_OBJECT_LIGHT_DIRECTION_HPP

# include "SceneObject.hpp"
# include "ValueType/Light/Direction.hpp"

# include "NewPolyHedra/DataType/TransScaleColor3D/PalletObjectData.hpp"

struct SceneObject_LightDirection : public SceneObject
{
	LightDirection *	Light;

	TransScaleColor3D::PalletObjectData		Data;

	~SceneObject_LightDirection();
	SceneObject_LightDirection();

	Trans3D		GetTrans() const override;
	void		SetTrans(const Trans3D & trans) override;

	void	Update() override;

	void	ShowWire() override;

	void	DisplayObject(const DisplayMode & mode) override;

	RayHitF3	Hit(const RayF3 & ray) const override;
};

#endif