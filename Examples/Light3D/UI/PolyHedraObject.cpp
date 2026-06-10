#include "UI/PolyHedraObject.hpp"



UI::PolyHedraObject::~PolyHedraObject()
{ }
UI::PolyHedraObject::PolyHedraObject()
	: UI::Control::Form()
	, Pallet()
	, PalletName()
	, PalletFile()
	, PalletSkinsCount()
	, Trans()
	, TransPos()
	, TransRot()
{
	PalletName.Anchor.X.AnchorBoth(0, 0);
	PalletFile.Anchor.X.AnchorBoth(0, 0);
	PalletSkinsCount.Anchor.X.AnchorBoth(0, 0);

	PalletName.Anchor.Y.AnchorMin(0);
	PalletFile.Anchor.Y.AnchorMin(PalletName.Anchor.Y.GetMinSize());
	PalletSkinsCount.Anchor.Y.AnchorMin(PalletFile.Anchor.Y.GetMinSize());

	Pallet.Anchor.X.AnchorBoth(0, 0);
	Pallet.Anchor.Y.AnchorMin(0, PalletSkinsCount.Anchor.Y.GetMinSize() + PalletSkinsCount.AnchorMargin.Max.Y + Pallet.AnchorBoarder.Max.Y + Pallet.AnchorPadding.Max.Y);

	TransPos.Anchor.X.AnchorBoth(0, 0);
	TransPos.Anchor.Y.AnchorMin(0);

	TransRot.Anchor.X.AnchorBoth(0, 0);
	TransRot.Anchor.Y.AnchorMin(TransPos.Anchor.Y.GetMinSize());

	Trans.Anchor.X.AnchorBoth(0, 0);
	Trans.Anchor.Y.AnchorMin(Pallet.Anchor.Y.GetMinSize(), TransRot.Anchor.Y.GetMinSize() + TransRot.AnchorMargin.Max.Y + Trans.AnchorBoarder.Max.Y + Trans.AnchorPadding.Max.Y);

	Anchor.X.AnchorMin(0, 400);
	Anchor.Y.AnchorMin(0, Trans.Anchor.Y.GetMinSize() + Trans.AnchorMargin.Max.Y + AnchorBoarder.Max.Y + AnchorPadding.Max.Y);

	ChildInsert(Pallet);
	Pallet.ChildInsert(PalletName);
	Pallet.ChildInsert(PalletFile);
	Pallet.ChildInsert(PalletSkinsCount);
	ChildInsert(Trans);
	Trans.ChildInsert(TransPos);
	Trans.ChildInsert(TransRot);

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

		Trans3D & trans = Object -> Trans();

		TransPos.Change(&trans.Position);
		TransRot.Change(&trans.Rotation);
	}
	else
	{
		PalletName.SetText("Name:");
		PalletFile.SetText("File:");
		PalletSkinsCount.SetText("Skins:");

		TransPos.Change(nullptr);
		TransRot.Change(nullptr);
	}
}
