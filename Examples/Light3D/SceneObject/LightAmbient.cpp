#include "SceneObject/LightAmbient.hpp"



SceneObject_LightAmbient::~SceneObject_LightAmbient()
{ }
SceneObject_LightAmbient::SceneObject_LightAmbient()
{ }



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
