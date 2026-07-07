#include "SceneObject/LightDirection.hpp"

#include "NewPolyHedra/DataType/TransScaleColor3D/ObjectData.hpp"
#include "NewPolyHedra/PalletObjectData.hpp"
#include "NewPolyHedra/PalletObjectManager.hpp"



SceneObject_LightDirection::~SceneObject_LightDirection()
{ }
SceneObject_LightDirection::SceneObject_LightDirection()
{ }



Trans3D SceneObject_LightDirection::GetTrans() const
{
	return Data.Data.Trans;
}
void SceneObject_LightDirection::SetTrans(const Trans3D & trans)
{
	Data.Data.Trans = trans;
}



void SceneObject_LightDirection::Update()
{ }



void SceneObject_LightDirection::ShowWire()
{
	Data.ShowWire();
}

void SceneObject_LightDirection::DisplayObject(const DisplayMode & mode)
{
	if (mode.Indicators == DisplayMode::EIndicators::Show)
	{
		Data.InstancePut();
	}
	Data.HideWire();
}



Ray3D_Hit SceneObject_LightDirection::Hit(const RayF3 & ray) const
{
	return RayHitObject1(ray, Data);
}
