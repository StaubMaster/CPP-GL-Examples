#include "SceneObject/SpotLightEntry.hpp"



SceneObject_SpotLightEntry::~SceneObject_SpotLightEntry()
{ }
SceneObject_SpotLightEntry::SceneObject_SpotLightEntry()
{ }



void SceneObject_SpotLightEntry::Update()
{
	Object.Update();
}



Ray3D_Hit SceneObject_SpotLightEntry::Hit(const Ray3D & ray) const
{
	Ray3D_Hit hit = Ray3D_Hit::IntersectHit(ray, Object);
	hit.Index[0] = 1;
	return hit;
}
