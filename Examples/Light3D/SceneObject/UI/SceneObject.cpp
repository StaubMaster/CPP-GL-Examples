#include "SceneObject/UI/SceneObject.hpp"
#include "SceneObject/SceneObject.hpp"



SceneObjectUI::~SceneObjectUI()
{ }
SceneObjectUI::SceneObjectUI()
	: Form()
	, LightAmbient("LightAmbient")
	, LightSolar("LightSolar")
{
	Anchor.X.AnchorMin(0, 400);
	Anchor.Y.AnchorMin(0, 0);

	PolyHedraObject.Anchor.X.AnchorBoth(0, 0);
	LightAmbient.Anchor.X.AnchorBoth(0, 0);
	LightSolar.Anchor.X.AnchorBoth(0, 0);
	SpotLightEntry.Anchor.X.AnchorBoth(0, 0);

	PolyHedraObject.Hide();
	LightAmbient.Hide();
	LightSolar.Hide();
	SpotLightEntry.Hide();

	ChildInsert(PolyHedraObject);
	ChildInsert(LightAmbient);
	ChildInsert(LightSolar);
	ChildInsert(SpotLightEntry);

	AnchorFitChildrenY();
}



#include "SceneObject/PolyHedraObject.hpp"
#include "SceneObject/LightAmbient.hpp"
#include "SceneObject/LightSolar.hpp"
#include "SceneObject/SpotLightEntry.hpp"

void SceneObjectUI::Change(::SceneObject * obj)
{
	Object = obj;
	if (Object == nullptr) { return; }

	PolyHedraObject.Hide();
	LightAmbient.Hide();
	LightSolar.Hide();
	SpotLightEntry.Hide();

	PolyHedraObject.Change(nullptr);
	LightAmbient.Change(nullptr);
	LightSolar.Change(nullptr);
	SpotLightEntry.Change(nullptr);

	{
		SceneObject_PolyHedraObject * obj_ = dynamic_cast<SceneObject_PolyHedraObject*>(obj);
		if (obj_ != nullptr)
		{
			PolyHedraObject.Show();
			PolyHedraObject.Change(&(obj_ -> Object));
		}
	}
	{
		SceneObject_LightAmbient * obj_ = dynamic_cast<SceneObject_LightAmbient*>(obj);
		if (obj_ != nullptr)
		{
			LightAmbient.Show();
			LightAmbient.Change((obj_ -> Light));
		}
	}
	{
		SceneObject_LightSolar * obj_ = dynamic_cast<SceneObject_LightSolar*>(obj);
		if (obj_ != nullptr)
		{
			LightSolar.Show();
			LightSolar.Change((obj_ -> Light));
		}
	}
	{
		SceneObject_SpotLightEntry * obj_ = dynamic_cast<SceneObject_SpotLightEntry*>(obj);
		if (obj_ != nullptr)
		{
			SpotLightEntry.Show();
			SpotLightEntry.Change(&(obj_ -> Object));
		}
	}
	AnchorFitChildrenY();
}
void SceneObjectUI::Update()
{
	PolyHedraObject.Update();
	LightAmbient.Update();
	LightSolar.Update();
	SpotLightEntry.Update();
}
