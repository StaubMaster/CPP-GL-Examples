#include "SceneObject/LightAmbient.hpp"

#include "PolyHedra/ObjectData.hpp"
#include "PolyHedra/PalletManager.hpp"
#include "PolyHedra/Object.hpp"



SceneObject_LightAmbient::~SceneObject_LightAmbient()
{ }
SceneObject_LightAmbient::SceneObject_LightAmbient()
{ }



Trans3D SceneObject_LightAmbient::GetTrans() const
{
	return Trans3D(Position);
}
void SceneObject_LightAmbient::SetTrans(const Trans3D & trans)
{
	Position = trans.Position;
}



void SceneObject_LightAmbient::Update()
{ }



void SceneObject_LightAmbient::ShowWire()
{
	PolyHedraObject obj(Pallet, Trans3D(Position));
	obj.HideFull();
	obj.ShowWire();
}

void SceneObject_LightAmbient::DisplayObject()
{
	PolyHedraObjectData data;
	data.Trans.Position = Position;
	Pallet -> PutInstance(data);
}



Ray3D_Hit SceneObject_LightAmbient::Hit(const Ray3D & ray) const
{
	//return RayIntersectHit(ray, Object);
	return RayIntersectHit(ray, *(Pallet -> Pallet), Trans3D(Position));
}
