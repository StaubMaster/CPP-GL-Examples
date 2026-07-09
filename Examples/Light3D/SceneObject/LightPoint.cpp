#include "SceneObject/LightPoint.hpp"
#include "Ray3D_Hit.hpp"

#include "NewPolyHedra/DataType/TransScaleColor3D/ObjectData.hpp"
#include "NewPolyHedra/PalletObjectData.hpp"
#include "NewPolyHedra/PalletObjectManager.hpp"



SceneObject_LightPoint::~SceneObject_LightPoint()
{ }
SceneObject_LightPoint::SceneObject_LightPoint()
{ }



Trans3D SceneObject_LightPoint::GetTrans() const
{
	return Data.Data.Trans;
}
void SceneObject_LightPoint::SetTrans(const Trans3D & trans)
{
	Data.Data.Trans = trans;
	if (Light != nullptr)
	{
		Light -> Pos = trans.Position;
	}
}



void SceneObject_LightPoint::Update()
{
	if (Light != nullptr)
	{
		Data.Data.Trans.Position = Light -> Pos;
	}
}



void SceneObject_LightPoint::ShowWire()
{
	Data.ShowWire();
}

void SceneObject_LightPoint::DisplayObject(const DisplayMode & mode)
{
	if (mode.Indicators == DisplayMode::EIndicators::Show)
	{
		Data.InstancePut();
	}
	Data.HideWire();
}



RayHitF3 SceneObject_LightPoint::Hit(const RayF3 & ray) const
{
	return RayHitObject(ray, Data);
}
