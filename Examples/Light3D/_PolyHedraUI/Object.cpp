#include "PolyHedraUI/Object.hpp"
#include "PolyHedraUI/ObjectData.hpp"
#include "PolyHedraUI/Manager.hpp"
#include "PolyHedraUI/PalletManager.hpp"



bool PolyHedraUIObject::Is() const
{
	if (Data != nullptr)
	{
		return (Data -> PalletManager != nullptr);
	}
	return false;
}

bool PolyHedraUIObject::VisFull() const { if (Data != nullptr) { return (Data -> DrawFull); } throw ExceptionNullObject(); }
bool PolyHedraUIObject::VisWire() const { if (Data != nullptr) { return (Data -> DrawWire); } throw ExceptionNullObject(); }

void PolyHedraUIObject::HideFull() { if (Data != nullptr) { (Data -> DrawFull) = false; } }
void PolyHedraUIObject::HideWire() { if (Data != nullptr) { (Data -> DrawWire) = false; } }

void PolyHedraUIObject::ShowFull() { if (Data != nullptr) { (Data -> DrawFull) = true; } }
void PolyHedraUIObject::ShowWire() { if (Data != nullptr) { (Data -> DrawWire) = true; } }



::PolyHedraUIPalletManager * PolyHedraUIObject::PalletManager() const
{
	if (Data != nullptr)
	{
		return (Data -> PalletManager);
	}
	throw ExceptionNullObject();
}
::PolyHedra * PolyHedraUIObject::Pallet() const
{
	if (Data != nullptr)
	{
		if (Data -> PalletManager != nullptr)
		{
			return (Data -> PalletManager -> Pallet);
		}
	}
	throw ExceptionNullObject();
}



const Trans3D &		PolyHedraUIObject::Trans() const	{ if (Data != nullptr) { return (Data -> Trans); } throw ExceptionNullObject(); }
Trans3D &			PolyHedraUIObject::Trans()			{ if (Data != nullptr) { return (Data -> Trans); } throw ExceptionNullObject(); }

const float &		PolyHedraUIObject::Scale() const	{ if (Data != nullptr) { return (Data -> Scale); } throw ExceptionNullObject(); }
float &				PolyHedraUIObject::Scale()			{ if (Data != nullptr) { return (Data -> Scale); } throw ExceptionNullObject(); }

const ColorF4 &		PolyHedraUIObject::Color() const	{ if (Data != nullptr) { return (Data -> Color); } throw ExceptionNullObject(); }
ColorF4 &			PolyHedraUIObject::Color()			{ if (Data != nullptr) { return (Data -> Color); } throw ExceptionNullObject(); }


PolyHedraUIObject::~PolyHedraUIObject()
{
	if (Data != nullptr)
	{
		if (Data -> PalletManager != nullptr)
		{
			Data -> Remove = true;
		}
		else
		{
			delete Data;
		}
		Data = nullptr;
	}
}
PolyHedraUIObject::PolyHedraUIObject()
	: Data(nullptr)
{ }

// dont copy in current, copy in same
PolyHedraUIObject::PolyHedraUIObject(const PolyHedraUIObject & other)
//	: Data(PolyHedraUIManager::sCopyObject(other.Data))
//	: Data(other.Data)
	: Data(nullptr)
{
	if (other.Data != nullptr)
	{
		if (other.Data -> PalletManager != nullptr)
		{
			Data = other.Data -> PalletManager -> CopyObject(other.Data);
		}
	}
}
PolyHedraUIObject & PolyHedraUIObject::operator=(const PolyHedraUIObject & other)
{
	if (Data != nullptr)
	{
		Data -> Remove = true;
	}
	//Data = PolyHedraUIManager::TryCopyObject(nullptr, other.Data);
	Data = nullptr;
	if (other.Data != nullptr)
	{
		if (other.Data -> PalletManager != nullptr)
		{
			Data = other.Data -> PalletManager -> CopyObject(other.Data);
		}
	}
	return *this;
}





// Data should be nullptr if no Current
PolyHedraUIObject::PolyHedraUIObject(::PolyHedraUIPalletManager * pallet)
	: Data(PolyHedraUIManager::TryPlaceObject(nullptr, pallet))
{ }
PolyHedraUIObject::PolyHedraUIObject(::PolyHedraUIPalletManager * pallet, Trans3D trans)
	: Data(PolyHedraUIManager::TryPlaceObject(nullptr, pallet))
{
	if (Data != nullptr)
	{
		Data -> Trans = trans;
	}
}



PolyHedraUIObject::PolyHedraUIObject(::PolyHedra * pallet)
	: Data(PolyHedraUIManager::TryPlaceObject(nullptr, pallet))
{ }
PolyHedraUIObject::PolyHedraUIObject(::PolyHedra * pallet, Trans3D trans)
	: Data(PolyHedraUIManager::TryPlaceObject(nullptr, pallet))
{
	if (Data != nullptr)
	{
		Data -> Trans = trans;
	}
}





void PolyHedraUIObject::Delete()
{
	if (Data != nullptr)
	{
		Data -> Remove = true;
		Data = nullptr;
	}
}
void PolyHedraUIObject::Create(::PolyHedraUIPalletManager * pallet)
{
	Delete();
	Data = PolyHedraUIManager::TryPlaceObject(nullptr, pallet);
}
void PolyHedraUIObject::Create(::PolyHedra * pallet)
{
	Delete();
	Data = PolyHedraUIManager::TryPlaceObject(nullptr, pallet);
}





const char * PolyHedraUIObject::ExceptionNullObject::what() const noexcept
{
	return "Attampted to access Null Object.";
}
