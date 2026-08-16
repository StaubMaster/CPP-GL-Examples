#include "Collection.hpp"
#include "SceneObject.hpp"

#include "ValueType/Ray/F3.hpp"
#include "ValueType/Ray/Hit/F3Type.hpp"



SceneObject * SceneObjectCollection::FindObject(const RayF3 & ray) const
{
	RayHitF3Type<unsigned int> hit;
	for (unsigned int i = 0; i < Objects.Count(); i++)
	{
		SceneObject * obj = Objects[i];
		if (obj == nullptr) { continue; }
		RayHitF3 hit_temp = obj -> Hit(ray);
		hit.Consider(hit_temp, i);
	}
	if (hit.Is())
	{
		return Objects[hit.Data];
	}
	return nullptr;
}
unsigned int SceneObjectCollection::FindObjectIndex(const SceneObject * obj) const
{
	for (unsigned int i = 0; i < Objects.Count(); i++)
	{
		if (Objects[i] == obj)
		{
			return i;
		}
	}
	return 0xFFFFFFFF;
}



void SceneObjectCollection::Clear()
{
	for (unsigned int i = 0; i < Objects.Count(); i++)
	{
		delete Objects[i];
	}
	Objects.Clear();
}
void SceneObjectCollection::Update()
{
	for (unsigned int i = 0; i < Objects.Count(); i++)
	{
		SceneObject * obj = Objects[i];
		if (obj == nullptr) { continue; }
		obj -> Update();
	}
}
void SceneObjectCollection::Display(const SceneObjectDisplayMode & mode)
{
	for (unsigned int i = 0; i < Objects.Count(); i++)
	{
		SceneObject * obj = Objects[i];
		if (obj == nullptr) { continue; }
		obj -> DisplayObject(mode);
	}
}
