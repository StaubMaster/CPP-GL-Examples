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
	return Trans;
}
void SceneObject_LightSpot::SetTrans(const Trans3D & trans)
{
	Trans = trans;
	Light -> Pos = Trans.Position;
	Light -> Dir = Trans.Rotation.forward(VectorF3(0, 0, 1));
}



void SceneObject_LightSpot::Update()
{ }



void SceneObject_LightSpot::ShowWire()
{
	Trans3D trans = Trans;

	PolyHedraObject obj0(Pallet0, trans);
	obj0.HideFull();
	obj0.ShowWire();

	trans.Rotation.X1 = Angle();
	trans.Rotation.Z0 = Angle();

	PolyHedraObject obj1(Pallet1, trans);
	obj1.HideFull();
	obj1.ShowWire();
}

void SceneObject_LightSpot::DisplayObject()
{
	PolyHedraObjectData data;
	data.Trans = Trans;
	Pallet0 -> PutInstance(data);
	data.Trans.Rotation.X1 = Angle();
	data.Trans.Rotation.Z0 = Angle();
	Pallet1 -> PutInstance(data);
}



Ray3D_Hit SceneObject_LightSpot::Hit(const Ray3D & ray) const
{
	Trans3D trans = Trans;
	Ray3D_Hit hit;
	hit.Consider(RayIntersectHit(ray, *(Pallet0 -> Pallet), trans));
	trans.Rotation.X1 = Angle();
	trans.Rotation.Z0 = Angle();
	hit.Consider(RayIntersectHit(ray, *(Pallet1 -> Pallet), trans));
	return hit;
}
