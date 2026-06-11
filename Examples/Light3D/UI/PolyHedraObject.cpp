#include "UI/PolyHedraObject.hpp"



UI::PolyHedraObject::~PolyHedraObject()
{ }
UI::PolyHedraObject::PolyHedraObject()
	: UI::Control::Form()
	, Pallet()
	, PalletName()
	, PalletFile()
	, PalletSkinsCount()
	, Trans("Trans")
{
	Anchor.X.AnchorMin(0, 400);
	Anchor.Y.AnchorMin(0, 0);

	Pallet.Anchor.X.AnchorBoth(0, 0);
	PalletName.Anchor.X.AnchorBoth(0, 0);
	PalletFile.Anchor.X.AnchorBoth(0, 0);
	PalletSkinsCount.Anchor.X.AnchorBoth(0, 0);

	Trans.Anchor.X.AnchorBoth(0, 0);

	ChildInsert(Pallet);
	Pallet.ChildInsert(PalletName);
	Pallet.ChildInsert(PalletFile);
	Pallet.ChildInsert(PalletSkinsCount);
	ChildInsert(Trans);

	Pallet.AnchorFitChildrenY();
	Trans.AnchorFitChildrenY();
	AnchorFitChildrenY();

	Change(nullptr);
}



#include "PolyHedra/Object.hpp"
#include "PolyHedra/PolyHedra.hpp"
#include "General/UnitToString.hpp"
#include <sstream>

void UI::PolyHedraObject::Change(::PolyHedraObject * obj)
{
	Object = obj;
	if (Object != nullptr)
	{
		std::stringstream ss;

		ss.str(std::string()); ss << "Name:" << (Object -> Pallet() -> Name); PalletName.SetText(ss.str());
		ss.str(std::string()); ss << "File:" << (Object -> Pallet() -> File.Path); PalletFile.SetText(ss.str());
		ss.str(std::string()); ss << "Skins :" << (Object -> Pallet() -> Skins.Count()); PalletSkinsCount.SetText(ss.str());

		Trans.Change(&(Object -> Trans()));
	}
	else
	{
		PalletName.SetText("Name:");
		PalletFile.SetText("File:");
		PalletSkinsCount.SetText("Skins:");

		Trans.Change(nullptr);
	}
}
