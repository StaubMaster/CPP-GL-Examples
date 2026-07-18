#include "SceneObject/LightAmbient.hpp"
#include "Ray3D_Hit.hpp"

#include "NewPolyHedraDataType/TransScaleColor3D/ObjectData.hpp"
#include "NewPolyHedra/PalletObjectData.hpp"
#include "NewPolyHedra/PalletObjectManager.hpp"



SceneObject_LightAmbient::~SceneObject_LightAmbient()
{ }
SceneObject_LightAmbient::SceneObject_LightAmbient()
{ }



Trans3D SceneObject_LightAmbient::GetTrans() const
{
	return Data.Data.Trans;
}
void SceneObject_LightAmbient::SetTrans(const Trans3D & trans)
{
	Data.Data.Trans = trans;
}



void SceneObject_LightAmbient::Update()
{ }



void SceneObject_LightAmbient::ShowWire()
{
	Data.ShowWire();
}

void SceneObject_LightAmbient::DisplayObject(const DisplayMode & mode)
{
	if (mode.Indicators == DisplayMode::EIndicators::Show)
	{
		Data.InstancePut();
	}
	Data.HideWire();
}



RayHitF3 SceneObject_LightAmbient::Hit(const RayF3 & ray) const
{
	return RayHitObject(ray, Data);
}
