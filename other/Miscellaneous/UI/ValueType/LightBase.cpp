#include "UI/ValueType/LightBase.hpp"



UI::LightBase::LightBase(const char * name)
	: NestedProperty(name)
	, Intensity()
	, Color("Color")
	, Object(nullptr)
{
	Intensity.Make_Anchor_X_Both(nullptr, nullptr);
	Color.Make_Anchor_X_Both(nullptr, nullptr);

	Intensity.ValueRange.Min.X = 0.0f;
	Intensity.ValueRange.Max.X = 1.0f;
	Intensity.ValueXChangedFunc.Assign(this, &LightBase::IntensityFunc);

	ChildInsert(Intensity);
	ChildInsert(Color);

	Minimize();
}



#include "UnitToString.hpp"
#include <sstream>

void UI::LightBase::Syncronize()
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

void UI::LightBase::Change(::LightBase * obj)
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



void UI::LightBase::IntensityFunc(float val)
{
	if (Object == nullptr) { return; }
	Object -> Intensity = val;
	std::stringstream ss;
	ss << "Intensity:" << ToString(Object -> Intensity, 2);
	Intensity.SetText(ss.str());
}
