#ifndef  SCENE_OBJECT_LIGHT_AMBIENT_HPP
# define SCENE_OBJECT_LIGHT_AMBIENT_HPP

# include "SceneObject.hpp"
# include "ValueType/Light/Base.hpp"

# include "NewPolyHedra/DataType/TransScaleColor3D/PalletObjectData.hpp"

struct SceneObject_LightAmbient : public SceneObject
{
	LightBase *		Light;

	TransScaleColor3D::PalletObjectData		Data;

	~SceneObject_LightAmbient();
	SceneObject_LightAmbient();

	Trans3D		GetTrans() const override;
	void		SetTrans(const Trans3D & trans) override;

	void	Update() override;

	void	ShowWire() override;

	void	DisplayObject(const DisplayMode & mode) override;

	Ray3D_Hit	Hit(const RayF3 & ray) const override;
};

#endif