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
	return Data.Trans;
}
void SceneObject_LightSpot::SetTrans(const Trans3D & trans)
{
	Data.Trans = trans;
	Light -> Pos = trans.Position;
	Light -> Dir = trans.Rotation.forward(VectorF3(0, 0, 1));
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
	Data.DrawWire = true;
}

void SceneObject_LightSpot::DisplayObject()
{
	Data.PalletManager -> PutInstance(Data);
	Data.DrawWire = false;
}



Ray3D_Hit SceneObject_LightSpot::Hit(const RayF3 & ray) const
{
	return RayHitObject(ray, Data);
}
