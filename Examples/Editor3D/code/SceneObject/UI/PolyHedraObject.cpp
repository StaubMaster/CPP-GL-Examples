#include "SceneObject/UI/PolyHedraObject.hpp"



UI::Control_::PolyHedraObject::~PolyHedraObject()
{ }
UI::Control_::PolyHedraObject::PolyHedraObject()
	: GroupBox()
	, Pallet()
	, PalletName()
	, PalletFile()
	, PalletSkinsCount()
	, PalletChange()
	, Trans("Trans")
{
	//AutoAnchorYType = EAutoAnchorType::StackMinFit;
	AutoAnchorYType = EAutoAnchorType::StackMin;
	//Anchor.X.AnchorBoth(0, 0);
	//Anchor.Y.AnchorMin(0, 0);
	Make_Anchor_X_Both(nullptr, nullptr);
	Make_Anchor_Y_Min(nullptr, 200);

	//Pallet.AutoAnchorYType = EAutoAnchorType::StackMinFit;
	Pallet.AutoAnchorYType = EAutoAnchorType::StackMin;
	//Pallet.Anchor.X.AnchorBoth(0, 0);
	//PalletName.Anchor.X.AnchorBoth(0, 0);
	//PalletFile.Anchor.X.AnchorBoth(0, 0);
	//PalletSkinsCount.Anchor.X.AnchorBoth(0, 0);
	//PalletChange.Anchor.X.AnchorBoth(0, 0);
	Pallet.Make_Anchor_X_Both(nullptr, nullptr);

	PalletName.Make_Anchor_X_Both(nullptr, nullptr);
	PalletFile.Make_Anchor_X_Both(nullptr, nullptr);
	PalletSkinsCount.Make_Anchor_X_Both(nullptr, nullptr);
	PalletChange.Make_Anchor_X_Both(nullptr, nullptr);

	PalletChange.SetText("Change Pallet");

	//Trans.Anchor.X.AnchorBoth(0, 0);
	Trans.Make_Anchor_X_Both(nullptr, nullptr);

	ChildInsert(Pallet);
	Pallet.ChildInsert(PalletName);
	Pallet.ChildInsert(PalletFile);
	Pallet.ChildInsert(PalletSkinsCount);
	Pallet.ChildInsert(PalletChange);
	ChildInsert(Trans);

	//Pallet.UpdateAutoAnchor();
	//Trans.UpdateAutoAnchor();
	//UpdateAutoAnchor();

	Change(nullptr);
}



//#include "NewPolyHedra/PalletObjectManager.hpp"
#include "NewPolyHedra/Base/Display/Object.hpp"
#include "NewPolyHedra/Pallet/.hpp"

#include "PolyHedra/PolyHedra.hpp"

#include "SceneObject/PolyHedraObject.hpp"
#include "UnitToString.hpp"
#include <sstream>

void UI::Control_::PolyHedraObject::Syncronize()
{
	if (Object != nullptr)
	{
		const PolyHedra & polyhedra = *(Object -> DisplayObject -> PalletObject.Object);
		// Find PolyHedraEntry
		std::stringstream ss;
		//ss.str(std::string()); ss << "Name:" << (polyhedra.Name); PalletName.SetText(ss.str());
		//ss.str(std::string()); ss << "Name:" << (polyhedra.File.Name()); PalletName.SetText(ss.str());
		//ss.str(std::string()); ss << "File:" << (polyhedra.File.Path); PalletFile.SetText(ss.str());
		//FIX: FILE NOW IN ENTRY
		ss.str(std::string()); ss << "Skin:" << (polyhedra.Skin); PalletSkinsCount.SetText(ss.str());
	}
	else
	{
		PalletName.SetText("Name:");
		PalletFile.SetText("File:");
		PalletSkinsCount.SetText("Skins:");
	}
	Trans.Syncronize();
}

void UI::Control_::PolyHedraObject::Change(::SceneObject_PolyHedraObject * obj)
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
