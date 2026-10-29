#include "SceneObject/LightDirection.hpp"
#include "SceneObject/DisplayMode.hpp"

#include "Ray3D_Hit.hpp"

//#include "NewPolyHedra/DataType/TransScaleColor3D/ObjectData.hpp"
//#include "NewPolyHedra/PalletObjectData.hpp"
//#include "NewPolyHedra/PalletObjectManager.hpp"



TransScaleColor3D::DisplayObject * SceneObject_LightDirection::Display = nullptr;



SceneObject_LightDirection::~SceneObject_LightDirection()
{ }
SceneObject_LightDirection::SceneObject_LightDirection()
{
	Data.Scale = VectorF3(1.0f);
	Data.Color = ColorF4();
}



Trans3D SceneObject_LightDirection::GetTrans() const
{
	return Data.Trans;
}
void SceneObject_LightDirection::SetTrans(const Trans3D & trans)
{
	Data.Trans = trans;
}



void SceneObject_LightDirection::Update()
{ }



void SceneObject_LightDirection::ShowWire()
{
	_ShowWire = true;
}

void SceneObject_LightDirection::DisplayObject(const SceneObjectDisplayMode & mode)
{
	if (mode.Indicators == SceneObjectDisplayMode::EIndicators::Show)
	{
		Display -> InstancesFullPut(Data);
		if (_ShowWire)
		{
			Display -> InstancesWirePut(Data);
		}
	}
	_ShowWire = false;
}



RayHitF3 SceneObject_LightDirection::Hit(const RayF3 & ray) const
{
	return RayHitObject(ray, *Display, Data);
}
