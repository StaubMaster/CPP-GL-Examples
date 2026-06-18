#include "SceneObject/PolyHedraObject.hpp"

#include "PolyHedra/PalletManager.hpp"
#include "PolyHedra/Object.hpp"



SceneObject_PolyHedraObject::~SceneObject_PolyHedraObject()
{ }
SceneObject_PolyHedraObject::SceneObject_PolyHedraObject()
{ }
SceneObject_PolyHedraObject::SceneObject_PolyHedraObject(::PolyHedraPalletManager * pallet, Trans3D trans)
	: Data(pallet)
{
	Data.Trans = trans;
}



Trans3D SceneObject_PolyHedraObject::GetTrans() const
{
	return Data.Trans;
}
void SceneObject_PolyHedraObject::SetTrans(const Trans3D & trans)
{
	Data.Trans = trans;
}



void SceneObject_PolyHedraObject::Update()
{ }



void SceneObject_PolyHedraObject::ShowWire()
{
	Data.DrawWire = true;
}

void SceneObject_PolyHedraObject::DisplayObject()
{
	Data.PalletManager -> PutInstance(Data);
	Data.DrawWire = false;
}



Ray3D_Hit SceneObject_PolyHedraObject::Hit(const Ray3D & ray) const
{
	return RayHitObject(ray, Data);
}
