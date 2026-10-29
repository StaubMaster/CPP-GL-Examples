#include "SceneObject/LightSpot.hpp"
#include "SceneObject/DisplayMode.hpp"

#include "Ray3D_Hit.hpp"



NewPolyHedra::Basic3D::DisplayObject * SceneObject_LightSpot::Display = nullptr;



SceneObject_LightSpot::~SceneObject_LightSpot()
{ }
SceneObject_LightSpot::SceneObject_LightSpot()
{ }



Trans3D SceneObject_LightSpot::GetTrans() const
{
	return Data.Trans;
}
void SceneObject_LightSpot::SetTrans(const Trans3D & trans)
{
	Data.Trans = trans;
	if (Light != nullptr)
	{
		Light -> Pos = trans.Position;
		Light -> Dir = trans.Rotation.forward(VectorF3(0, 0, 1));
	}
}



void SceneObject_LightSpot::Update()
{
	if (Light != nullptr)
	{
		Data.Trans.Position = Light -> Pos;
		Data.Trans.Rotation = EulerAngle3D::PointToZ(Light -> Dir);
	}
}



void SceneObject_LightSpot::ShowWire()
{
	_ShowWire = true;
}

void SceneObject_LightSpot::DisplayObject(const SceneObjectDisplayMode & mode)
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



RayHitF3 SceneObject_LightSpot::Hit(const RayF3 & ray) const
{
	return RayHitObject(ray, *Display, Data);
}
