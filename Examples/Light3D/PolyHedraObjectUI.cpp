#include "PolyHedraObjectUI.hpp"

#include <iostream>

PolyHedraObjectUI::~PolyHedraObjectUI()
{ }
PolyHedraObjectUI::PolyHedraObjectUI()
	: UI::Control::Form()
	, Pallet()
	, PalletName()
	, PalletFile()
	, PalletSkinsCount()
	, Trans()
	, TransPos()
	, TransPosX()
	, TransPosZ()
	, TransPosY()
	, TransRot()
	, TransRotX()
	, TransRotZ()
	, TransRotY()
{
	PalletName.Anchor.X.AnchorBoth(0, 0);
	PalletFile.Anchor.X.AnchorBoth(0, 0);
	PalletSkinsCount.Anchor.X.AnchorBoth(0, 0);

	PalletName.Anchor.Y.AnchorMin(0);
	PalletFile.Anchor.Y.AnchorMin(PalletName.Anchor.Y.GetMinSize());
	PalletSkinsCount.Anchor.Y.AnchorMin(PalletFile.Anchor.Y.GetMinSize());

	Pallet.Anchor.X.AnchorBoth(0, 0);
	Pallet.Anchor.Y.AnchorMin(0, PalletSkinsCount.Anchor.Y.GetMinSize() + PalletSkinsCount.AnchorMargin.Max.Y + Pallet.AnchorBoarder.Max.Y + Pallet.AnchorPadding.Max.Y);

	TransPosX.Anchor.X.AnchorBoth(0, 0);
	TransPosY.Anchor.X.AnchorBoth(0, 0);
	TransPosZ.Anchor.X.AnchorBoth(0, 0);

	TransPosX.Anchor.Y.AnchorMin(0);
	TransPosY.Anchor.Y.AnchorMin(TransPosX.Anchor.Y.GetMinSize());
	TransPosZ.Anchor.Y.AnchorMin(TransPosY.Anchor.Y.GetMinSize());

	TransPos.Anchor.X.AnchorBoth(0, 0);
	TransPos.Anchor.Y.AnchorMin(0, TransPosZ.Anchor.Y.GetMinSize() + TransPosZ.AnchorMargin.Max.Y + TransPos.AnchorBoarder.Max.Y + TransPos.AnchorPadding.Max.Y);

	TransRotX.Anchor.X.AnchorBoth(0, 0);
	TransRotY.Anchor.X.AnchorBoth(0, 0);
	TransRotZ.Anchor.X.AnchorBoth(0, 0);

	TransRotX.Anchor.Y.AnchorMin(0);
	TransRotY.Anchor.Y.AnchorMin(TransRotX.Anchor.Y.GetMinSize());
	TransRotZ.Anchor.Y.AnchorMin(TransRotY.Anchor.Y.GetMinSize());

	TransRot.Anchor.X.AnchorBoth(0, 0);
	TransRot.Anchor.Y.AnchorMin(TransPos.Anchor.Y.GetMinSize(), TransRotZ.Anchor.Y.GetMinSize() + TransRotZ.AnchorMargin.Max.Y + TransRot.AnchorBoarder.Max.Y + TransRot.AnchorPadding.Max.Y);

	Trans.Anchor.X.AnchorBoth(0, 0);
	Trans.Anchor.Y.AnchorMin(Pallet.Anchor.Y.GetMinSize(), TransRot.Anchor.Y.GetMinSize() + TransRot.AnchorMargin.Max.Y + Trans.AnchorBoarder.Max.Y + Trans.AnchorPadding.Max.Y);

	ChildInsert(Pallet);
	Pallet.ChildInsert(PalletName);
	Pallet.ChildInsert(PalletFile);
	Pallet.ChildInsert(PalletSkinsCount);
	ChildInsert(Trans);
	Trans.ChildInsert(TransPos);
	TransPos.ChildInsert(TransPosX);
	TransPos.ChildInsert(TransPosZ);
	TransPos.ChildInsert(TransPosY);
	Trans.ChildInsert(TransRot);
	TransRot.ChildInsert(TransRotX);
	TransRot.ChildInsert(TransRotZ);
	TransRot.ChildInsert(TransRotY);

	Change(nullptr);
}

#include "PolyHedra/Object.hpp"
#include "PolyHedra/PolyHedra.hpp"
#include "General/UnitToString.hpp"
#include <sstream>

void PolyHedraObjectUI::Change(PolyHedraObject * obj)
{
	Object = obj;
	if (Object != nullptr)
	{
		std::stringstream ss;

		ss.str(std::string()); ss << "Name:" << (obj -> Pallet() -> Name); PalletName.SetText(ss.str());
		ss.str(std::string()); ss << "File:" << (obj -> Pallet() -> File.Path); PalletFile.SetText(ss.str());
		ss.str(std::string()); ss << "Skins :" << (obj -> Pallet() -> Skins.Count()); PalletSkinsCount.SetText(ss.str());

		const Trans3D & trans = obj -> Trans();

		ss.str(std::string()); ss << "X:" << ToString(trans.Position.X); TransPosX.SetText(ss.str());
		ss.str(std::string()); ss << "Y:" << ToString(trans.Position.Y); TransPosY.SetText(ss.str());
		ss.str(std::string()); ss << "Z:" << ToString(trans.Position.Z); TransPosZ.SetText(ss.str());

		ss.str(std::string()); ss << "Z0:" << ToString(trans.Rotation.Z0.ToDegrees()); TransRotX.SetText(ss.str());
		ss.str(std::string()); ss << "X1:" << ToString(trans.Rotation.X1.ToDegrees()); TransRotY.SetText(ss.str());
		ss.str(std::string()); ss << "Y2:" << ToString(trans.Rotation.Y2.ToDegrees()); TransRotZ.SetText(ss.str());
	}
	else
	{
		PalletName.SetText("Name:");
		PalletFile.SetText("File:");
		PalletSkinsCount.SetText("Skins:");

		TransPosX.SetText("X:");
		TransPosY.SetText("Y:");
		TransPosZ.SetText("Z:");

		TransRotX.SetText("Z0:");
		TransRotY.SetText("X1:");
		TransRotZ.SetText("Y2:");
	}
}
