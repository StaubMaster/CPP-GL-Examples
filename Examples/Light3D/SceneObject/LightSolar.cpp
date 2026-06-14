#include "SceneObject/LightSolar.hpp"



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
	if (Object.Is())
	{
		Object.Trans().Position = Position;
	}
}



void SceneObject_LightSolar::Update()
{ }



void SceneObject_LightSolar::ShowWire()
{
	PolyHedraObject obj = Object;
	obj.HideFull();
	obj.ShowWire();
}



Ray3D_Hit SceneObject_LightSolar::Hit(const Ray3D & ray) const
{
	Ray3D_Hit hit = Ray3D_Hit::IntersectHit(ray, Object);
	hit.Index[0] = 1;
	return hit;
}
