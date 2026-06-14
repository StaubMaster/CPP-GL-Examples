#include "SceneObject/LightAmbient.hpp"



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
	if (Object.Is())
	{
		Object.Trans().Position = Position;
	}
}



void SceneObject_LightAmbient::Update()
{ }



void SceneObject_LightAmbient::ShowWire()
{
	PolyHedraObject obj = Object;
	obj.HideFull();
	obj.ShowWire();
}



Ray3D_Hit SceneObject_LightAmbient::Hit(const Ray3D & ray) const
{
	Ray3D_Hit hit = Ray3D_Hit::IntersectHit(ray, Object);
	hit.Index[0] = 1;
	return hit;
}
