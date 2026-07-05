#ifndef  SCENE_OBJECT_LIGHT_AMBIENT_HPP
# define SCENE_OBJECT_LIGHT_AMBIENT_HPP

# include "SceneObject.hpp"
# include "ValueType/Light/Base.hpp"
//# include "PolyHedraUI/ObjectData.hpp"

# include "NewPolyHedra/Type/PalletObjectData.hpp"
# include "NewPolyHedra/DataType/TransScaleColor3D/ObjectData.hpp"

struct SceneObject_LightAmbient : public SceneObject
{
	LightBase *		Light;
	//PolyHedraUIObjectData		Data;
	NewPolyHedra_Type_PalletObjectData<TransScaleColor3D::ObjectData>	Data;

	~SceneObject_LightAmbient();
	SceneObject_LightAmbient();

	Trans3D		GetTrans() const override;
	void		SetTrans(const Trans3D & trans) override;

	void	Update() override;

	void	ShowWire() override;

	void	DisplayObject() override;

	Ray3D_Hit	Hit(const RayF3 & ray) const override;
};

#endif