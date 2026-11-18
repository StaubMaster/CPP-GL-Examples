#include "UI/PolyHedra/Basic3D/DisplayObject.hpp"



UI::DisplayObject::DisplayObject()
	: NestedProperty("DisplayObject")
	, FullCount()
	, WireCount()
	, PalletObject()
{
	AutoAnchorYType = EAutoAnchorType::StackMin;
	Make_Anchor_X_Both(nullptr, nullptr);
	Make_Anchor_Y_Both(nullptr, nullptr);

	FullCount.Make_Anchor_X_Both(nullptr, nullptr);
	WireCount.Make_Anchor_X_Both(nullptr, nullptr);
	PalletObject.Make_Anchor_X_Both(nullptr, nullptr);

	ChildInsert(FullCount);
	ChildInsert(WireCount);
	ChildInsert(PalletObject);
	Change(nullptr);

	Minimize();
}



#include "UnitToString.hpp"
#include <sstream>

void UI::DisplayObject::Syncronize()
{
	if (Object != nullptr)
	{
		{
			std::stringstream ss;
			ss << "Full: " << (Object -> CountFull);
			FullCount.SetText(ss.str());
		}
		{
			std::stringstream ss;
			ss << "Wire: " << (Object -> CountWire);
			WireCount.SetText(ss.str());
		}
	}
	else
	{
		FullCount.SetText("Full:");
		WireCount.SetText("Wire:");
	}
	PalletObject.Syncronize();
}

void UI::DisplayObject::Change(::NewPolyHedra::Basic3D::DisplayObject * obj)
{
	if (obj != nullptr)
	{ Object = obj; }
	else
	{ Object = nullptr; }

	if (Object != nullptr)
	{
		Show();
		PalletObject.Change(&(Object -> PalletObject));
	}
	else
	{
		Hide();
		PalletObject.Change(nullptr);
	}
}
