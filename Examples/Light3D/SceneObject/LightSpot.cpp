#include "SceneObject/LightSpot.hpp"



SceneObject_LightSpot::~SceneObject_LightSpot()
{ }
SceneObject_LightSpot::SceneObject_LightSpot()
{ }



Trans3D SceneObject_LightSpot::GetTrans() const
{
	return Trans3D(Position);
}
void SceneObject_LightSpot::SetTrans(const Trans3D & trans)
{
	Position = trans.Position;
	if (Object0.Is())
	{
		Object0.Trans().Position = Position;
	}
	if (Object1.Is())
	{
		Object1.Trans().Position = Position;
	}
}



void SceneObject_LightSpot::Update()
{ }



void SceneObject_LightSpot::ShowWire()
{
	PolyHedraObject obj0 = Object0;
	obj0.HideFull();
	obj0.ShowWire();

	PolyHedraObject obj1 = Object1;
	obj1.HideFull();
	obj1.ShowWire();
}



Ray3D_Hit SceneObject_LightSpot::Hit(const Ray3D & ray) const
{
	Ray3D_Hit hit;
	hit.Consider(RayIntersectHit(ray, Object0));
	hit.Consider(RayIntersectHit(ray, Object1));
	return hit;
}
