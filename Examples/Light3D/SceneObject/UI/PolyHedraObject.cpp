#include "SceneObject/UI/PolyHedraObject.hpp"



UI::Control::PolyHedraObject::~PolyHedraObject()
{ }
UI::Control::PolyHedraObject::PolyHedraObject()
	: GroupBox()
	, Pallet()
	, PalletName()
	, PalletFile()
	, PalletSkinsCount()
	, PalletChange()
	, Trans("Trans")
{
	AutoSizerYType = EAutoSizerType::FitFixed;

	Anchor.X.AnchorBoth(0, 0);
	Anchor.Y.AnchorMin(0, 0);

	Pallet.Anchor.X.AnchorBoth(0, 0);
	PalletName.Anchor.X.AnchorBoth(0, 0);
	PalletFile.Anchor.X.AnchorBoth(0, 0);
	PalletSkinsCount.Anchor.X.AnchorBoth(0, 0);
	PalletChange.Anchor.X.AnchorBoth(0, 0);

	PalletChange.SetText("Change Pallet");

	Trans.Anchor.X.AnchorBoth(0, 0);

	ChildInsert(Pallet);
	Pallet.ChildInsert(PalletName);
	Pallet.ChildInsert(PalletFile);
	Pallet.ChildInsert(PalletSkinsCount);
	Pallet.ChildInsert(PalletChange);
	ChildInsert(Trans);

	Pallet.UpdateAutoSize();
	Trans.UpdateAutoSize();
	UpdateAutoSize();

	Change(nullptr);
}



#include "NewPolyHedra/PalletObjectManager.hpp"
#include "NewPolyHedra/Pallet.hpp"

#include "PolyHedra/PolyHedra.hpp"

#include "SceneObject/PolyHedraObject.hpp"
#include "UnitToString.hpp"
#include <sstream>

void UI::Control::PolyHedraObject::Update()
{
	if (Object != nullptr)
	{
		const PolyHedra & polyhedra = *(Object -> Manager -> Pallet -> Object);
		std::stringstream ss;
		ss.str(std::string()); ss << "Name:" << (polyhedra.Name); PalletName.SetText(ss.str());
		ss.str(std::string()); ss << "File:" << (polyhedra.File.Path); PalletFile.SetText(ss.str());
		ss.str(std::string()); ss << "Skins :" << (polyhedra.Skins.Count()); PalletSkinsCount.SetText(ss.str());
	}
	else
	{
		PalletName.SetText("Name:");
		PalletFile.SetText("File:");
		PalletSkinsCount.SetText("Skins:");
	}
	Trans.Update();
}

void UI::Control::PolyHedraObject::Change(::SceneObject_PolyHedraObject * obj)
{
	if (obj != nullptr)
	{ Object = &(obj -> Data); }
	else
	{ Object = nullptr; }

	if (Object != nullptr)
	{
		Show();
		Trans.Change(&(Object -> Data.Trans));
	}
	else
	{
		Hide();
		Trans.Change(nullptr);
	}
}
