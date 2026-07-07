#include "SceneObject/PolyHedraObject.hpp"
#include "Ray3D_Hit.hpp"

#include "PolyHedra/PalletManager.hpp"
#include "PolyHedra/Object.hpp"



SceneObject_PolyHedraObject::~SceneObject_PolyHedraObject()
{ }
SceneObject_PolyHedraObject::SceneObject_PolyHedraObject()
{ }
SceneObject_PolyHedraObject::SceneObject_PolyHedraObject(::NewPolyHedra_PalletObjectManager * manager, Trans3D trans)
{
	//Data.Trans = trans;
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

void SceneObject_PolyHedraObject::DisplayObject(const DisplayMode & mode)
{
	if (mode.Objects == DisplayMode::EObjects::Full)
	{
		Data.InstancePut();
	}
	else if (mode.Objects == DisplayMode::EObjects::Wire)
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
	return RayHitObject0(ray, Data);
}
