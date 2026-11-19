#include "SceneObject/Collection.hpp"
#include "SceneObject/.hpp"

#include "ValueType/Ray/F3.hpp"
#include "ValueType/Ray/Hit/F3Type.hpp"



void SceneObject_Collection::Clear()
{
	for (unsigned int i = 0; i < Objects.Count(); i++)
	{
		delete Objects[i];
	}
	Objects.Clear();
}
void SceneObject_Collection::Remove(const SceneObject * obj)
{
	for (unsigned int i = 0; i < Objects.Count(); i++)
	{
		if (Objects[i] == obj)
		{
			Objects.RemoveAt(i);
			i--;
		}
	}
}

void SceneObject_Collection::Update()
{
	for (unsigned int i = 0; i < Objects.Count(); i++)
	{
		SceneObject * obj = Objects[i];
		if (obj == nullptr) { continue; }
		obj -> Update();
	}
}
void SceneObject_Collection::Display(const SceneObject_DisplayMode & mode)
{
	for (unsigned int i = 0; i < Objects.Count(); i++)
	{
		SceneObject * obj = Objects[i];
		if (obj == nullptr) { continue; }
		obj -> DisplayObject(mode);
	}
}



unsigned int SceneObject_Collection::FindIndex(const SceneObject * obj) const
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

SceneObject * SceneObject_Collection::FindHit(const RayF3 & ray) const
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
