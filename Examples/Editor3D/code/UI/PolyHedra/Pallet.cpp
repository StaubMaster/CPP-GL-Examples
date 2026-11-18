#include "UI/PolyHedra/Pallet.hpp"



UI::PolyHedraPallet::PolyHedraPallet()
	: NestedProperty("PolyHedraPallet")
	, FullCount()
	, WireCount()
	, PolyHedraObject()
{
	AutoAnchorYType = EAutoAnchorType::StackMin;
	Make_Anchor_X_Both(nullptr, nullptr);
	Make_Anchor_Y_Both(nullptr, nullptr);

	FullCount.Make_Anchor_X_Both(nullptr, nullptr);
	WireCount.Make_Anchor_X_Both(nullptr, nullptr);
	PolyHedraObject.Make_Anchor_X_Both(nullptr, nullptr);

	ChildInsert(FullCount);
	ChildInsert(WireCount);
	ChildInsert(PolyHedraObject);
	Change(nullptr);

	Minimize();
}



#include "UnitToString.hpp"
#include <sstream>

void UI::PolyHedraPallet::Syncronize()
{
	if (Object != nullptr)
	{
		{
			std::stringstream ss;
			ss << "Full: " << (Object -> BufferFull.Count);
			FullCount.SetText(ss.str());
		}
		{
			std::stringstream ss;
			ss << "Wire: " << (Object -> BufferWire.Count);
			WireCount.SetText(ss.str());
		}
	}
	else
	{
		FullCount.SetText("Full:");
		WireCount.SetText("Wire:");
	}
	PolyHedraObject.Syncronize();
}

void UI::PolyHedraPallet::Change(::NewPolyHedra::Pallet * obj)
{
	if (obj != nullptr)
	{ Object = obj; }
	else
	{ Object = nullptr; }

	if (Object != nullptr)
	{
		Show();
		PolyHedraObject.Change(Object -> Object);
	}
	else
	{
		Hide();
		PolyHedraObject.Change(nullptr);
	}
}
