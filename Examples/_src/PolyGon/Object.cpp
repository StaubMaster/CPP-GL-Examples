#include "PolyGon/Object.hpp"
#include "PolyGon/ObjectData.hpp"
#include "PolyGon/Manager.hpp"



bool				PolyGonObject::Is() const { return (Data != nullptr); }
::PolyGon *			PolyGonObject::PolyGon() const { return (Data -> PolyGon); }

const Trans2D &		PolyGonObject::Trans() const { return (Data -> Trans); }
Trans2D &			PolyGonObject::Trans() { return (Data -> Trans); }



bool PolyGonObject::IsFullVisible() const { return (Data -> DrawFull); }
bool PolyGonObject::IsWireVisible() const { return (Data -> DrawWire); }

void PolyGonObject::HideFull() { (Data -> DrawFull) = false; }
void PolyGonObject::HideWire() { (Data -> DrawWire) = false; }

void PolyGonObject::ShowFull() { (Data -> DrawFull) = true; }
void PolyGonObject::ShowWire() { (Data -> DrawWire) = true; }




PolyGonObject::~PolyGonObject()
{
	if (Data != nullptr)
	{
		Data -> Remove = true;
	}
}
PolyGonObject::PolyGonObject()
	: Data(nullptr)
{ }

PolyGonObject::PolyGonObject(const PolyGonObject & other)
	: Data(PolyGonManager::Current().CopyObject(other.Data))
{ }
PolyGonObject & PolyGonObject::operator=(const PolyGonObject & other)
{
	if (Data != nullptr)
	{
		Data -> Remove = true;
	}
	Data = PolyGonManager::Current().CopyObject(other.Data);
	return *this;
}





PolyGonObject::PolyGonObject(unsigned int PolyGon)
	: Data(PolyGonManager::Current().PlaceObject(PolyGon, Trans2D()))
{ }
PolyGonObject::PolyGonObject(unsigned int PolyGon, Trans2D trans)
	: Data(PolyGonManager::Current().PlaceObject(PolyGon, trans))
{ }
PolyGonObject::PolyGonObject(unsigned int PolyGon, Point2D pos, Angle ang)
	: Data(PolyGonManager::Current().PlaceObject(PolyGon, Trans2D(pos, Angle2D((ang)))))
{ }
PolyGonObject::PolyGonObject(unsigned int PolyGon, Point2D pos)
	: Data(PolyGonManager::Current().PlaceObject(PolyGon, Trans2D(pos, Angle2D((Angle())))))
{ }



PolyGonObject::PolyGonObject(::PolyGon * PolyGon)
	: Data(PolyGonManager::Current().PlaceObject(PolyGon, Trans2D()))
{ }
PolyGonObject::PolyGonObject(::PolyGon * PolyGon, Trans2D trans)
	: Data(PolyGonManager::Current().PlaceObject(PolyGon, trans))
{ }
PolyGonObject::PolyGonObject(::PolyGon * PolyGon, Point2D pos, Angle ang)
	: Data(PolyGonManager::Current().PlaceObject(PolyGon, Trans2D(pos, Angle2D(ang))))
{ }
PolyGonObject::PolyGonObject(::PolyGon * PolyGon, Point2D pos)
	: Data(PolyGonManager::Current().PlaceObject(PolyGon, Trans2D(pos, Angle2D(Angle()))))
{ }





void PolyGonObject::Delete()
{
	if (Data != nullptr)
	{
		Data -> Remove = true;
		Data = nullptr;
	}
}
void PolyGonObject::Create(unsigned int PolyGon)
{
	if (Data == nullptr)
	{
		Data = PolyGonManager::Current().PlaceObject(PolyGon, Trans2D());
	}
}
void PolyGonObject::Create(::PolyGon * PolyGon)
{
	if (Data == nullptr)
	{
		Data = PolyGonManager::Current().PlaceObject(PolyGon, Trans2D());
	}
}
