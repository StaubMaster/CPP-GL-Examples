#include "SceneObject/UI/SceneObject.hpp"
#include "SceneObject/SceneObject.hpp"



SceneObjectUI::~SceneObjectUI()
{ }
SceneObjectUI::SceneObjectUI()
	: Form()
{
	Anchor.X.AnchorMin(0, 400);
	Anchor.Y.AnchorMin(0, 0);

	PolyHedraObject.Anchor.X.AnchorBoth(0, 0);
	SpotLightEntry.Anchor.X.AnchorBoth(0, 0);

	PolyHedraObject.Hide();
	SpotLightEntry.Hide();

	ChildInsert(PolyHedraObject);
	ChildInsert(SpotLightEntry);

	AnchorFitChildrenY();
}



#include "SceneObject/PolyHedraObject.hpp"
#include "SceneObject/SpotLightEntry.hpp"

void SceneObjectUI::Change(::SceneObject * obj)
{
	Object = obj;
	if (Object == nullptr) { return; }

	{
		SceneObject_PolyHedraObject * obj_ = dynamic_cast<SceneObject_PolyHedraObject*>(obj);
		if (obj_ != nullptr)
		{
			PolyHedraObject.Show();
			SpotLightEntry.Hide();
			PolyHedraObject.Change(&(obj_ -> Object));
			SpotLightEntry.Change(nullptr);
		}
	}
	{
		SceneObject_SpotLightEntry * obj_ = dynamic_cast<SceneObject_SpotLightEntry*>(obj);
		if (obj_ != nullptr)
		{
			PolyHedraObject.Hide();
			SpotLightEntry.Show();
			PolyHedraObject.Change(nullptr);
			SpotLightEntry.Change(&(obj_ -> Object));
		}
	}
	AnchorFitChildrenY();
}
void SceneObjectUI::Update()
{
	PolyHedraObject.Update();
	SpotLightEntry.Update();
}
