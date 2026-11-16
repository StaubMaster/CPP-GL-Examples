#include "ValueTypeUI/LightBase.hpp"



UI::Control_::LightBase::~LightBase()
{ }
UI::Control_::LightBase::LightBase(const char * name)
	: PropertyControl(name)
	, Intensity()
	, Color("Color")
	, Object(nullptr)
{
	//Intensity.Anchor.X.AnchorBoth(0, 0);
	//Color.Anchor.X.AnchorBoth(0, 0);
	Intensity.Make_Anchor_X_Both(nullptr, nullptr);
	Color.Make_Anchor_X_Both(nullptr, nullptr);

	Intensity.ValueRange.Min.X = 0.0f;
	Intensity.ValueRange.Max.X = 1.0f;
	Intensity.ValueXChangedFunc.Assign(this, &LightBase::IntensityFunc);

	ChildInsert(Intensity);
	ChildInsert(Color);

	HideProperty();
}



#include "UnitToString.hpp"
#include <sstream>

void UI::Control_::LightBase::Syncronize()
{
	if (Object != nullptr)
	{
		Intensity.SetValueX(Object -> Intensity);
	}
	else
	{
		Intensity.SetText("Intensity:");
	}
	Color.Syncronize();
}

void UI::Control_::LightBase::Change(::LightBase * obj)
{
	Object = obj;
	if (Object != nullptr)
	{
		Color.Change(&(Object -> Color));
	}
	else
	{
		Color.Change(nullptr);
	}
}



void UI::Control_::LightBase::IntensityFunc(float val)
{
	if (Object == nullptr) { return; }
	Object -> Intensity = val;
	std::stringstream ss;
	ss << "Intensity:" << ToString(Object -> Intensity, 2);
	Intensity.SetText(ss.str());
}
