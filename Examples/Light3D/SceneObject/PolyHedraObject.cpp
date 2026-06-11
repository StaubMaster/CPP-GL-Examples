#include "SceneObject/PolyHedraObject.hpp"



SceneObject_PolyHedraObject::~SceneObject_PolyHedraObject()
{ }
SceneObject_PolyHedraObject::SceneObject_PolyHedraObject()
{ }
SceneObject_PolyHedraObject::SceneObject_PolyHedraObject(const PolyHedraObject & obj)
	: Object(obj)
{ }



void SceneObject_PolyHedraObject::Update()
{ }



Ray3D_Hit SceneObject_PolyHedraObject::Hit(const Ray3D & ray) const
{
	Ray3D_Hit hit = Ray3D_Hit::IntersectHit(ray, Object);
	hit.Index[0] = 0;
	return hit;
}
