#include "PolyHedraUI/ObjectData.hpp"
#include "PolyHedraUI/PalletManager.hpp"



PolyHedraUIObjectData::~PolyHedraUIObjectData()
{ }
PolyHedraUIObjectData::PolyHedraUIObjectData()
	: Remove(false)
	, DrawFull(true)
	, DrawWire(false)
	, PalletManager(nullptr)
	, Trans()
	, Scale(1.0f)
	, Color()
{ }
/*PolyHedraUIObjectData::PolyHedraUIObjectData(const PolyHedraUIObjectData & other)
	: Remove(other.Remove)
	, DrawFull(other.DrawFull)
	, DrawWire(other.DrawWire)
	, PalletManager(other.PalletManager)
	, Trans(other.Trans)
{ }*/
PolyHedraUIObjectData & PolyHedraUIObjectData::operator=(const PolyHedraUIObjectData & other)
{
	Remove = other.Remove;
	DrawFull = other.DrawFull;
	DrawWire = other.DrawWire;
	PalletManager = other.PalletManager;
	Trans = other.Trans;
	Scale = other.Scale;
	Color = other.Color;
	return *this;
}



PolyHedraUIObjectData::PolyHedraUIObjectData(::PolyHedraUIPalletManager * manager)
	: Remove(false)
	, DrawFull(true)
	, DrawWire(false)
	, PalletManager(manager)
	, Trans()
	, Scale(1.0f)
	, Color()
{ }



PolyHedraUIData PolyHedraUIObjectData::ToData() const
{
	PolyHedraUIData data;
	data.Trans = Matrix4x4::TransformForward(Trans);
	data.Normal = Matrix4x4::Rotation(Trans.Rotation);
	data.Scale = Scale;
	data.Color = Color;
	return data;
}
