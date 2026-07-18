#ifndef  SCENE_OBJECT_LIGHT_POINT_HPP
# define SCENE_OBJECT_LIGHT_POINT_HPP

# include "SceneObject.hpp"
# include "ValueType/Light/Point.hpp"

# include "NewPolyHedraDataType/TransScaleColor3D/PalletObjectData.hpp"

struct SceneObject_LightPoint : public SceneObject
{
	LightPoint *	Light;

	TransScaleColor3D::PalletObjectData		Data;

	~SceneObject_LightPoint();
	SceneObject_LightPoint();

	Trans3D		GetTrans() const override;
	void		SetTrans(const Trans3D & trans) override;

	void	Update() override;

	void	ShowWire() override;

	void	DisplayObject(const DisplayMode & mode) override;

	RayHitF3	Hit(const RayF3 & ray) const override;
};

#endif