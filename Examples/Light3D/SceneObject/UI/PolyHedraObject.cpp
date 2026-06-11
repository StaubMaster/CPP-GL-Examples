#include "SceneObject/UI/PolyHedraObject.hpp"



UI::Control::PolyHedraObject::~PolyHedraObject()
{ }
UI::Control::PolyHedraObject::PolyHedraObject()
	: GroupBox()
	, Pallet()
	, PalletName()
	, PalletFile()
	, PalletSkinsCount()
	, Trans("Trans")
{
	Anchor.X.AnchorBoth(0, 0);
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

void UI::Control::PolyHedraObject::Update()
{
	if (Object != nullptr)
	{
		std::stringstream ss;
		ss.str(std::string()); ss << "Name:" << (Object -> Pallet() -> Name); PalletName.SetText(ss.str());
		ss.str(std::string()); ss << "File:" << (Object -> Pallet() -> File.Path); PalletFile.SetText(ss.str());
		ss.str(std::string()); ss << "Skins :" << (Object -> Pallet() -> Skins.Count()); PalletSkinsCount.SetText(ss.str());
	}
	else
	{
		PalletName.SetText("Name:");
		PalletFile.SetText("File:");
		PalletSkinsCount.SetText("Skins:");
	}
	Trans.Update();
}

void UI::Control::PolyHedraObject::Change(::PolyHedraObject * obj)
{
	Object = obj;
	if (Object != nullptr)
	{
		Trans.Change(&(Object -> Trans()));
	}
	else
	{
		Trans.Change(nullptr);
	}
}
