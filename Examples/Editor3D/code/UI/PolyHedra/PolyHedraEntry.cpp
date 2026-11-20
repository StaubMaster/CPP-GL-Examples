#include "UI/PolyHedra/PolyHedraEntry.hpp"
#include "PolyHedra/Entry.hpp"
#include "PolyHedra/Manager.hpp"



UI::PolyHedraEntry::PolyHedraEntry()
	: NestedProperty("PolyHedraEntry")
	, File()
{
	AutoAnchorYType = EAutoAnchorType::StackMin;
	Make_Anchor_X_Both(nullptr, nullptr);
	Make_Anchor_Y_Both(nullptr, nullptr);

	File.Make_Anchor_X_Both(nullptr, nullptr);

	ChildInsert(File);
	Change(nullptr);

	Minimize();
}



#include "UnitToString.hpp"
#include <sstream>

void UI::PolyHedraEntry::Syncronize()
{
	if (Object != nullptr)
	{
		{
			std::stringstream ss;
			ss << "File: " << (Object -> File);
			File.SetText(ss.str());
		}
	}
	else
	{
		File.SetText("File:");
	}
}

void UI::PolyHedraEntry::Change(::PolyHedra * obj)
{
	Object = PolyHedraManager::sFind(obj);

	if (Object != nullptr)
	{
		Show();
	}
	else
	{
		Hide();
	}
}
