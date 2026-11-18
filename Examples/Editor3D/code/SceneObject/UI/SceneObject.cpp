#include "SceneObject/UI/SceneObject.hpp"
#include "SceneObject/SceneObject.hpp"



SceneObjectUI::SceneObjectUI()
	: Form()
//	, PolyHedraObject()
//	, LightAmbient("LightAmbient")
//	, LightSolar("LightSolar")
//	, LightSpot("LightSpot")
{
	//AutoAnchorYType = EAutoAnchorType::StackMinFit;
	//AutoAnchorYType = EAutoAnchorType::StackMin;

	//Anchor.X.AnchorMin(0, 400);
	//Anchor.Y.AnchorMin(0, 0);
	Make_Anchor_X_Min(nullptr, 400);
	Make_Anchor_Y_Min(nullptr, 400);

	//PolyHedraObject.Anchor.X.AnchorBoth(0, 0);
	//LightAmbient.Anchor.X.AnchorBoth(0, 0);
	//LightSolar.Anchor.X.AnchorBoth(0, 0);
	//LightSpot.Anchor.X.AnchorBoth(0, 0);
//	PolyHedraObject.Make_Anchor_X_Both(nullptr, nullptr);
//	PolyHedraObject.Make_Anchor_Y_Both(nullptr, nullptr);
//	LightAmbient.Make_Anchor_X_Both(nullptr, nullptr);
//	LightAmbient.Make_Anchor_Y_Both(nullptr, nullptr);
//	LightSolar.Make_Anchor_X_Both(nullptr, nullptr);
//	LightSolar.Make_Anchor_Y_Both(nullptr, nullptr);
//	LightSpot.Make_Anchor_X_Both(nullptr, nullptr);
//	LightSpot.Make_Anchor_Y_Both(nullptr, nullptr);

//	PolyHedraObject.Hide();
//	LightAmbient.Hide();
//	LightSolar.Hide();
//	LightSpot.Hide();

//	ChildInsert(PolyHedraObject);
//	ChildInsert(LightAmbient);
//	ChildInsert(LightSolar);
//	ChildInsert(LightSpot);
}



#include "SceneObject/PolyHedraObject.hpp"
#include "SceneObject/LightAmbient.hpp"
#include "SceneObject/LightDirection.hpp"
#include "SceneObject/LightSpot.hpp"

void SceneObjectUI::Change(::SceneObject * obj)
{
	ChildRemove(ObjectUI);
	delete ObjectUI;
	Object = obj;

	if (ObjectUI == nullptr)
	{
		//PolyHedraObject.Change(dynamic_cast<SceneObject_PolyHedraObject*>(obj));
		SceneObject_PolyHedraObject * cast = dynamic_cast<SceneObject_PolyHedraObject*>(obj));
		if (cast != nullptr)
		{
			
		}
	}

	if (ObjectUI == nullptr)
	{
		SceneObject_LightAmbient * obj_ = dynamic_cast<SceneObject_LightAmbient*>(obj);
		if (obj_ != nullptr)
		{
			LightAmbient.Show();
			LightAmbient.Change((obj_ -> Light));
		}
		else
		{
			LightAmbient.Hide();
			LightAmbient.Change(nullptr);
		}
	}

	if (ObjectUI == nullptr)
	{
		SceneObject_LightDirection * obj_ = dynamic_cast<SceneObject_LightDirection*>(obj);
		if (obj_ != nullptr)
		{
			LightSolar.Show();
			LightSolar.Change((obj_ -> Light));
		}
		else
		{
			LightSolar.Hide();
			LightSolar.Change(nullptr);
		}
	}

	if (ObjectUI == nullptr)
	{
		SceneObject_LightSpot * obj_ = dynamic_cast<SceneObject_LightSpot*>(obj);
		if (obj_ != nullptr)
		{
			LightSpot.Show();
			LightSpot.Change((obj_ -> Light));
		}
		else
		{
			LightSpot.Hide();
			LightSpot.Change(nullptr);
		}
	}
}
void SceneObjectUI::Syncronize()
{
	PolyHedraObject.Syncronize();
	LightAmbient.Syncronize();
	LightSolar.Syncronize();
	LightSpot.Syncronize();
}
