#ifndef  SCENE_OBJECT_LIGHT_SPOT_HPP
# define SCENE_OBJECT_LIGHT_SPOT_HPP

# include "SceneObject.hpp"
# include "ValueType/Light/Spot.hpp"
//# include "PolyHedra/ObjectData.hpp"
# include "NewPolyHedra/DataType/Basic3D/PalletObjectData.hpp"

struct SceneObject_LightSpot : public SceneObject
{
	LightSpot *				Light;
	//PolyHedraObjectData		Data;
	Basic3D::PalletObjectData	Data;

	~SceneObject_LightSpot();
	SceneObject_LightSpot();

	Trans3D		GetTrans() const override;
	void		SetTrans(const Trans3D & trans) override;

	void	Update() override;

	void	ShowWire() override;

	void	DisplayObject() override;

	Ray3D_Hit	Hit(const RayF3 & ray) const override;
};

#endif