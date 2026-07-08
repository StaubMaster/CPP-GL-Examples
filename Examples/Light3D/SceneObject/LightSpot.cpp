#include "SceneObject/LightSpot.hpp"
#include "Ray3D_Hit.hpp"

#include "PolyHedra/ObjectData.hpp"
#include "PolyHedra/PalletManager.hpp"
#include "PolyHedra/Object.hpp"



SceneObject_LightSpot::~SceneObject_LightSpot()
{ }
SceneObject_LightSpot::SceneObject_LightSpot()
{ }



Trans3D SceneObject_LightSpot::GetTrans() const
{
	return Data.Data.Trans;
}
void SceneObject_LightSpot::SetTrans(const Trans3D & trans)
{
	Data.Data.Trans = trans;
	Light -> Pos = trans.Position;
	Light -> Dir = trans.Rotation.forward(VectorF3(0, 0, 1));
}



void SceneObject_LightSpot::Update()
{
	if (Light != nullptr)
	{
		Data.Data.Trans.Position = Light -> Pos;
		Data.Data.Trans.Rotation = EulerAngle3D::PointToZ(Light -> Dir);
	}
}



void SceneObject_LightSpot::ShowWire()
{
	Data.ShowWire();
}

void SceneObject_LightSpot::DisplayObject(const DisplayMode & mode)
{
	if (mode.Indicators == DisplayMode::EIndicators::Show)
	{
		Data.InstancePut();
	}
	Data.HideWire();
}



RayHitF3 SceneObject_LightSpot::Hit(const RayF3 & ray) const
{
	return RayHitObject(ray, Data);
}
