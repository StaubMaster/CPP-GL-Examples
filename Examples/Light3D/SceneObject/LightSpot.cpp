#include "SceneObject/LightSpot.hpp"

#include "PolyHedra/ObjectData.hpp"
#include "PolyHedra/PalletManager.hpp"
#include "PolyHedra/Object.hpp"



SceneObject_LightSpot::~SceneObject_LightSpot()
{ }
SceneObject_LightSpot::SceneObject_LightSpot()
{ }



Trans3D SceneObject_LightSpot::GetTrans() const
{
	return Data0.Trans;
}
void SceneObject_LightSpot::SetTrans(const Trans3D & trans)
{
	Data0.Trans = trans;
	Data1.Trans = trans;
	Data1.Trans.Rotation.Z0 = Angle();
	Data1.Trans.Rotation.X1 = Angle();
	Light -> Pos = trans.Position;
	Light -> Dir = trans.Rotation.forward(VectorF3(0, 0, 1));
}



void SceneObject_LightSpot::Update()
{ }



void SceneObject_LightSpot::ShowWire()
{
	Data0.DrawWire = true;
	Data1.DrawWire = true;
}

void SceneObject_LightSpot::DisplayObject()
{
	Data0.PalletManager -> PutInstance(Data0);
	Data1.PalletManager -> PutInstance(Data1);
	Data0.DrawWire = false;
	Data1.DrawWire = false;
}



Ray3D_Hit SceneObject_LightSpot::Hit(const Ray3D & ray) const
{
	Ray3D_Hit hit;
	hit.Consider(RayHitObject(ray, Data0));
	hit.Consider(RayHitObject(ray, Data1));
	return hit;
}
