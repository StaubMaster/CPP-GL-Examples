#include "SceneObject/LightSolar.hpp"

#include "PolyHedra/ObjectData.hpp"
#include "PolyHedra/PalletManager.hpp"
#include "PolyHedra/Object.hpp"



SceneObject_LightSolar::~SceneObject_LightSolar()
{ }
SceneObject_LightSolar::SceneObject_LightSolar()
{ }



Trans3D SceneObject_LightSolar::GetTrans() const
{
	return Data.Trans;
}
void SceneObject_LightSolar::SetTrans(const Trans3D & trans)
{
	Data.Trans = trans;
}



void SceneObject_LightSolar::Update()
{ }



void SceneObject_LightSolar::ShowWire()
{
	Data.DrawWire = true;
}

void SceneObject_LightSolar::DisplayObject()
{
	Data.PalletManager -> PutInstance(Data);
	Data.DrawWire = false;
}



Ray3D_Hit SceneObject_LightSolar::Hit(const Ray3D & ray) const
{
	return RayHitObject(ray, Data);
}
