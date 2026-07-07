#include "SceneObject/PolyHedraObject.hpp"

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
	//Data.DrawWire = true;
	Data.DisplayWire = true;
}

void SceneObject_PolyHedraObject::DisplayObject()
{
	Data.InstancePut();
	//Data.PalletManager -> PutInstance(Data);
	//Data.DrawWire = false;
	Data.DisplayWire = false;
}



Ray3D_Hit SceneObject_PolyHedraObject::Hit(const RayF3 & ray) const
{
	return RayHitObject0(ray, Data);
}
