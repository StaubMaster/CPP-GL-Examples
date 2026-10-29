#include "SceneObject/LightAmbient.hpp"
#include "SceneObject/DisplayMode.hpp"

#include "Ray3D_Hit.hpp"

//#include "NewPolyHedra/DataType/TransScaleColor3D/ObjectData.hpp"
//#include "NewPolyHedra/PalletObjectData.hpp"
//#include "NewPolyHedra/PalletObjectManager.hpp"



TransScaleColor3D::DisplayObject * SceneObject_LightAmbient::Display = nullptr;



SceneObject_LightAmbient::~SceneObject_LightAmbient()
{ }
SceneObject_LightAmbient::SceneObject_LightAmbient()
{
	Data.Scale = VectorF3(1.0f);
	Data.Color = ColorF4();
}



Trans3D SceneObject_LightAmbient::GetTrans() const
{
	return Data.Trans;
}
void SceneObject_LightAmbient::SetTrans(const Trans3D & trans)
{
	Data.Trans = trans;
}



void SceneObject_LightAmbient::Update()
{ }



void SceneObject_LightAmbient::ShowWire()
{
	_ShowWire = true;
}

void SceneObject_LightAmbient::DisplayObject(const SceneObjectDisplayMode & mode)
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



RayHitF3 SceneObject_LightAmbient::Hit(const RayF3 & ray) const
{
	return RayHitObject(ray, *Display, Data);
}
