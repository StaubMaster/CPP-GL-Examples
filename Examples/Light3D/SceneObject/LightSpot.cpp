#include "SceneObject/LightSpot.hpp"



SceneObject_LightSpot::~SceneObject_LightSpot()
{ }
SceneObject_LightSpot::SceneObject_LightSpot()
{ }



void SceneObject_LightSpot::Update()
{ }



Ray3D_Hit SceneObject_LightSpot::Hit(const Ray3D & ray) const
{
	Ray3D_Hit hit_return;
	Ray3D_Hit hit;

	hit = Ray3D_Hit::IntersectHit(ray, Object0);
	hit.Index[0] = 1;
	hit_return.Consider(hit);

	hit = Ray3D_Hit::IntersectHit(ray, Object1);
	hit.Index[0] = 1;
	hit_return.Consider(hit);

	return hit_return;
}
