#include "SceneObject/UI/SceneObject.hpp"
#include "SceneObject/SceneObject.hpp"



SceneObjectUI::~SceneObjectUI()
{ }
SceneObjectUI::SceneObjectUI()
	: Form()
	, LightAmbient("LightAmbient")
	, LightSolar("LightSolar")
	, LightSpot("LightSpot")
{
	Anchor.X.AnchorMin(0, 400);
	Anchor.Y.AnchorMin(0, 0);

	PolyHedraObject.Anchor.X.AnchorBoth(0, 0);
	LightAmbient.Anchor.X.AnchorBoth(0, 0);
	LightSolar.Anchor.X.AnchorBoth(0, 0);
	LightSpot.Anchor.X.AnchorBoth(0, 0);

	PolyHedraObject.Hide();
	LightAmbient.Hide();
	LightSolar.Hide();
	LightSpot.Hide();

	ChildInsert(PolyHedraObject);
	ChildInsert(LightAmbient);
	ChildInsert(LightSolar);
	ChildInsert(LightSpot);

	AnchorFitChildrenY();
}



#include "SceneObject/PolyHedraObject.hpp"
#include "SceneObject/LightAmbient.hpp"
#include "SceneObject/LightSolar.hpp"
#include "SceneObject/LightSpot.hpp"

void SceneObjectUI::Change(::SceneObject * obj)
{
	Object = obj;

	PolyHedraObject.Change(dynamic_cast<SceneObject_PolyHedraObject*>(obj));

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

	{
		SceneObject_LightSolar * obj_ = dynamic_cast<SceneObject_LightSolar*>(obj);
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

	AnchorFitChildrenY();
}
void SceneObjectUI::Update()
{
	PolyHedraObject.Update();
	LightAmbient.Update();
	LightSolar.Update();
	LightSpot.Update();
}
