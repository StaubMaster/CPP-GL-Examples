#include "SceneObject/LightDirection.hpp"

//#include "PolyHedraUI/PalletManager.hpp"
//#include "PolyHedraUI/Object.hpp"

#include "NewPolyHedra/DataType/TransScaleColor3D/ObjectData.hpp"
#include "NewPolyHedra/Type/ObjectData.hpp"
#include "NewPolyHedra/PalletObjectData.hpp"
#include "NewPolyHedra/PalletObjectManager.hpp"



SceneObject_LightDirection::~SceneObject_LightDirection()
{ }
SceneObject_LightDirection::SceneObject_LightDirection()
{ }



Trans3D SceneObject_LightDirection::GetTrans() const
{
	return Data.Data().Trans;
	//return Data.Trans;
}
void SceneObject_LightDirection::SetTrans(const Trans3D & trans)
{
	Data.Data().Trans = trans;
	//Data.Trans = trans;
}



void SceneObject_LightDirection::Update()
{ }



void SceneObject_LightDirection::ShowWire()
{
	//Data.DrawWire = true;
}

void SceneObject_LightDirection::DisplayObject()
{
	Data.InstancePut();
	//Data.PalletManager -> PutInstance(Data);
	//Data.DrawWire = false;
}



Ray3D_Hit SceneObject_LightDirection::Hit(const RayF3 & ray) const
{
	return RayHitObject(ray, Data);
}
