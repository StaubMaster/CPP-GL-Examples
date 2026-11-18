#include "SceneObject/UI/SceneObject.hpp"
#include "SceneObject/SceneObject.hpp"



SceneObjectUI::SceneObjectUI()
	: Form()
{
	Make_Anchor_X_Min(nullptr, 400);
	Make_Anchor_Y_Min(nullptr, 400);
}

#include "SceneObject/PolyHedraObject.hpp"
#include "SceneObject/LightAmbient.hpp"
#include "SceneObject/LightDirection.hpp"
#include "SceneObject/LightSpot.hpp"

//#include "SceneObject/UI/PolyHedraObject.hpp"
#include "UI/PolyHedra/Basic3D/LogicalObject.hpp"
#include "UI/ValueType/LightBase.hpp"
#include "UI/ValueType/LightDirection.hpp"
#include "UI/ValueType/LightSpot.hpp"

void SceneObjectUI::Change(::SceneObject * obj)
{
	ChildRemove(ObjectUI);
	delete ObjectUI;
	ObjectUI = nullptr;

	Object = obj;
	if (ObjectUI == nullptr)
	{
		SceneObject_PolyHedraObject * cast = dynamic_cast<SceneObject_PolyHedraObject*>(obj);
		if (cast != nullptr)
		{
			UI::LogicalObject * obj_ui = new UI::LogicalObject();
			obj_ui -> Change(&(cast -> Data));
			ObjectUI = obj_ui;
			ChildInsert(obj_ui);
		}
	}

	if (ObjectUI == nullptr)
	{
		SceneObject_LightAmbient * cast = dynamic_cast<SceneObject_LightAmbient*>(obj);
		if (cast != nullptr)
		{
			UI::LightBase * obj_ui = new UI::LightBase("LightAmbient");
			obj_ui -> Change(cast -> Light);
			ObjectUI = obj_ui;
			ChildInsert(obj_ui);
		}
	}

	if (ObjectUI == nullptr)
	{
		SceneObject_LightDirection * cast = dynamic_cast<SceneObject_LightDirection*>(obj);
		if (cast != nullptr)
		{
			UI::LightDirection * obj_ui = new UI::LightDirection("LightSolar");
			obj_ui -> Change(cast -> Light);
			ObjectUI = obj_ui;
			ChildInsert(obj_ui);
		}
	}

	if (ObjectUI == nullptr)
	{
		SceneObject_LightSpot * cast = dynamic_cast<SceneObject_LightSpot*>(obj);
		if (cast != nullptr)
		{
			UI::LightSpot * obj_ui = new UI::LightSpot("LightSpot");
			obj_ui -> Change(cast -> Light);
			ObjectUI = obj_ui;
			ChildInsert(obj_ui);
		}
	}

	if (ObjectUI != nullptr)
	{
		ObjectUI -> Make_Anchor_X_Both(nullptr, nullptr);
		ObjectUI -> Make_Anchor_Y_Both(nullptr, nullptr);
	}
}
void SceneObjectUI::Syncronize()
{
	if (ObjectUI != nullptr)
	{
		ObjectUI -> Syncronize();
	}
}
