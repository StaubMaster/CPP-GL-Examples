#include "SceneObject/LightPoint.hpp"
#include "SceneObject/DisplayMode.hpp"

#include "Ray3D_Hit.hpp"

//#include "NewPolyHedra/DataType/TransScaleColor3D/ObjectData.hpp"
//#include "NewPolyHedra/PalletObjectData.hpp"
//#include "NewPolyHedra/PalletObjectManager.hpp"



TransScaleColor3D::DisplayObject * SceneObject_LightPoint::Display = nullptr;



SceneObject_LightPoint::~SceneObject_LightPoint()
{ }
SceneObject_LightPoint::SceneObject_LightPoint()
{
	Data.Scale = VectorF3(1.0f);
	Data.Color = ColorF4();
}



Trans3D SceneObject_LightPoint::GetTrans() const
{
	return Data.Trans;
}
void SceneObject_LightPoint::SetTrans(const Trans3D & trans)
{
	Data.Trans = trans;
	if (Light != nullptr)
	{
		Light -> Pos = trans.Position;
	}
}



void SceneObject_LightPoint::Update()
{
	if (Light != nullptr)
	{
		Data.Trans.Position = Light -> Pos;
	}
}



void SceneObject_LightPoint::ShowWire()
{
	_ShowWire = true;
}

void SceneObject_LightPoint::DisplayObject(const SceneObjectDisplayMode & mode)
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



RayHitF3 SceneObject_LightPoint::Hit(const RayF3 & ray) const
{
	return RayHitObject(ray, *Display, Data);
}
