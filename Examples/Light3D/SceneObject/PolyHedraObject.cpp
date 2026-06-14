#include "SceneObject/PolyHedraObject.hpp"



SceneObject_PolyHedraObject::~SceneObject_PolyHedraObject()
{ }
SceneObject_PolyHedraObject::SceneObject_PolyHedraObject()
{ }
SceneObject_PolyHedraObject::SceneObject_PolyHedraObject(::PolyHedraPalletManager * pallet, Trans3D trans)
	: Object(pallet)
{
	Trans = trans;
	if (Object.Is()) { Object.Trans() = Trans; }
}



Trans3D SceneObject_PolyHedraObject::GetTrans() const
{
	return Trans;
}
void SceneObject_PolyHedraObject::SetTrans(const Trans3D & trans)
{
	Trans = trans;
	if (Object.Is()) { Object.Trans() = Trans; }
}



void SceneObject_PolyHedraObject::Update()
{ }



void SceneObject_PolyHedraObject::ShowWire()
{
	PolyHedraObject obj = Object;
	obj.HideFull();
	obj.ShowWire();
}



Ray3D_Hit SceneObject_PolyHedraObject::Hit(const Ray3D & ray) const
{
	Ray3D_Hit hit = Ray3D_Hit::IntersectHit(ray, Object);
	hit.Index[0] = 0;
	return hit;
}
