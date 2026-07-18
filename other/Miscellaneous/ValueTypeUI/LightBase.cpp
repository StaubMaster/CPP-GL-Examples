#include "ValueTypeUI/LightBase.hpp"



UI::Control::LightBase::~LightBase()
{ }
UI::Control::LightBase::LightBase(const char * name)
	: PropertyControl(name)
	, Intensity()
	, Color("Color")
	, Object(nullptr)
{
	Intensity.Anchor.X.AnchorBoth(0, 0);
	Color.Anchor.X.AnchorBoth(0, 0);

	Intensity.ValueMin.X = 0.0f;
	Intensity.ValueMax.X = 1.0f;
	Intensity.ValueXChangedFunc.Assign(this, &LightBase::IntensityFunc);

	ChildInsert(Intensity);
	ChildInsert(Color);

	HideProperty();
}



#include "UnitToString.hpp"
#include <sstream>

void UI::Control::LightBase::Update()
{
	if (Object != nullptr)
	{
		Intensity.SetValueX(Object -> Intensity);
	}
	else
	{
		Intensity.SetText("Intensity:");
	}
	Color.Update();
}

void UI::Control::LightBase::Change(::LightBase * obj)
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



void UI::Control::LightBase::IntensityFunc(float val)
{
	if (Object == nullptr) { return; }
	Object -> Intensity = val;
	std::stringstream ss;
	ss << "Intensity:" << ToString(Object -> Intensity, 2);
	Intensity.SetText(ss.str());
}
