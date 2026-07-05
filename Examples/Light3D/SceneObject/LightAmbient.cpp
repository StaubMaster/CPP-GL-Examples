#include "SceneObject/LightAmbient.hpp"

//#include "PolyHedraUI/PalletManager.hpp"
//#include "PolyHedraUI/Object.hpp"

#include "NewPolyHedra/DataType/TransScaleColor3D/ObjectData.hpp"
#include "NewPolyHedra/Type/ObjectData.hpp"
#include "NewPolyHedra/PalletObjectData.hpp"
#include "NewPolyHedra/PalletObjectManager.hpp"



SceneObject_LightAmbient::~SceneObject_LightAmbient()
{ }
SceneObject_LightAmbient::SceneObject_LightAmbient()
{ }



Trans3D SceneObject_LightAmbient::GetTrans() const
{
	return Data.Data().Trans;
	//return Data.Trans;
}
void SceneObject_LightAmbient::SetTrans(const Trans3D & trans)
{
	Data.Data().Trans = trans;
	//Data.Trans = trans;
}



void SceneObject_LightAmbient::Update()
{ }



void SceneObject_LightAmbient::ShowWire()
{
	//Data.DrawWire = true;
}

void SceneObject_LightAmbient::DisplayObject()
{
	Data.InstancePut();
	//Data.PalletManager -> PutInstance(Data);
	//Data.DrawWire = false;
}



Ray3D_Hit SceneObject_LightAmbient::Hit(const RayF3 & ray) const
{
	return RayHitObject(ray, Data);
}
