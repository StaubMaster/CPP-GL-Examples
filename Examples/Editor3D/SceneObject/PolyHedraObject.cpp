#include "SceneObject/PolyHedraObject.hpp"
#include "SceneObject/DisplayMode.hpp"

#include "Ray3D_Hit.hpp"



SceneObject_PolyHedraObject::~SceneObject_PolyHedraObject()
{ }
SceneObject_PolyHedraObject::SceneObject_PolyHedraObject()
{ }
SceneObject_PolyHedraObject::SceneObject_PolyHedraObject(::NewPolyHedra::PalletObjectManager * manager, Trans3D trans)
{
	Data.Manager = manager;
	Data.Data.Trans = trans;
}



Trans3D SceneObject_PolyHedraObject::GetTrans() const
{
	return Data.Data.Trans;
}
void SceneObject_PolyHedraObject::SetTrans(const Trans3D & trans)
{
	Data.Data.Trans = trans;
}



void SceneObject_PolyHedraObject::Update()
{ }



void SceneObject_PolyHedraObject::ShowWire()
{
	Data.ShowWire();
}

void SceneObject_PolyHedraObject::DisplayObject(const SceneObjectDisplayMode & mode)
{
	if (mode.Objects == SceneObjectDisplayMode::EObjects::Full)
	{
		Data.InstancePut();
	}
	else if (mode.Objects == SceneObjectDisplayMode::EObjects::Wire)
	{
		bool full = Data.VisibleFull();
		bool wire = Data.VisibleWire();

		Data.HideFull();
		Data.ShowWire();
		Data.InstancePut();

		if (full) { Data.ShowFull(); }
		if (!wire) { Data.HideWire(); }
	}
	Data.HideWire();
}



RayHitF3 SceneObject_PolyHedraObject::Hit(const RayF3 & ray) const
{
	return RayHitObject(ray, Data);
}
