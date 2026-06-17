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
	return Trans3D(Position);
}
void SceneObject_LightSolar::SetTrans(const Trans3D & trans)
{
	Position = trans.Position;
}



void SceneObject_LightSolar::Update()
{ }



void SceneObject_LightSolar::ShowWire()
{
	PolyHedraObject obj(Pallet, Trans3D(Position));
	obj.HideFull();
	obj.ShowWire();
}

void SceneObject_LightSolar::DisplayObject()
{
	PolyHedraObjectData data;
	data.Trans.Position = Position;
	data.Trans.Rotation = EulerAngle3D::PointToZ(Light -> Dir);
	Pallet -> PutInstance(data);
}



Ray3D_Hit SceneObject_LightSolar::Hit(const Ray3D & ray) const
{
	//return RayIntersectHit(ray, Object);
	return RayIntersectHit(ray, *(Pallet -> Pallet), Trans3D(Position, EulerAngle3D::PointToZ(Light -> Dir)));
}
