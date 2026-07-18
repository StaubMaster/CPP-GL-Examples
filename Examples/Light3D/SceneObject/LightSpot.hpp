#ifndef  SCENE_OBJECT_LIGHT_SPOT_HPP
# define SCENE_OBJECT_LIGHT_SPOT_HPP

# include "SceneObject.hpp"
# include "ValueType/Light/Spot.hpp"

# include "NewPolyHedraDataType/Basic3D/PalletObjectData.hpp"

struct SceneObject_LightSpot : public SceneObject
{
	LightSpot *		Light;

	Basic3D::PalletObjectData	Data;

	~SceneObject_LightSpot();
	SceneObject_LightSpot();

	Trans3D		GetTrans() const override;
	void		SetTrans(const Trans3D & trans) override;

	void	Update() override;

	void	ShowWire() override;

	void	DisplayObject(const DisplayMode & mode) override;

	RayHitF3	Hit(const RayF3 & ray) const override;
};

#endif