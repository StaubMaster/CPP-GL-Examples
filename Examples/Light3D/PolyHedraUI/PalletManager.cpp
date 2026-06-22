#include "PolyHedraUI/PalletManager.hpp"
#include "PolyHedraUI/Manager.hpp"
#include "PolyHedraUI/ObjectData.hpp"

#include "Miscellaneous/Container/Array.hpp"
#include "Miscellaneous/Container/Binary.hpp"

#include "PolyHedra/PolyHedra.hpp"
#include "PolyHedra/Data.hpp"

#include "PolyHedra/Graphics/Full/Main/Data.hpp"
#include "PolyHedra/Graphics/Wire/Main/Data.hpp"

#include "PolyHedra/Skin/Skin.hpp"



PolyHedraUIPalletManager::~PolyHedraUIPalletManager()
{ }

PolyHedraUIPalletManager::PolyHedraUIPalletManager(::PolyHedra * pallet)
	: Pallet(pallet)
	, DefaultVisibilityFull(true)
	, DefaultVisibilityWire(false)
	, ObjectDatas()
	, InstancesFull()
	, InstancesWire()
	, BufferFull()
	, BufferWire()
	, TextureFull()
	, GraphicsExist(false)
{ }



PolyHedraUIObjectData * PolyHedraUIPalletManager::PlaceObject()
{
	PolyHedraUIObjectData * obj = new PolyHedraUIObjectData(this);
	obj -> DrawFull = DefaultVisibilityFull;
	obj -> DrawWire = DefaultVisibilityWire;
	ObjectDatas.Insert(obj);
	return obj;
}
PolyHedraUIObjectData * PolyHedraUIPalletManager::CopyObject(const PolyHedraUIObjectData * other)
{
	PolyHedraUIObjectData * obj = new PolyHedraUIObjectData(this);
	*obj = *other;
	ObjectDatas.Insert(obj);
	return obj;
}



PolyHedraUIObjectData * PolyHedraUIPalletManager::TryPlaceObject(PolyHedraUIPalletManager * pallet)
{
	if (pallet == nullptr) { return nullptr; }
	return pallet -> PlaceObject();
}
PolyHedraUIObjectData * PolyHedraUIPalletManager::TryCopyObject(PolyHedraUIPalletManager * pallet, const PolyHedraUIObjectData * other)
{
	if (pallet == nullptr) { return nullptr; }
	return pallet -> CopyObject(other);
}



void PolyHedraUIPalletManager::MakeInstances()
{
	InstancesFull.Clear();
	InstancesWire.Clear();
	for (unsigned int i = 0; i < ObjectDatas.Count(); i++)
	{
		if (ObjectDatas[i] == nullptr) { continue; }
		const PolyHedraUIObjectData & obj = *ObjectDatas[i];
		if (obj.DrawFull)
		{
			InstancesFull.Insert(obj.ToData());
		}
		if (obj.DrawWire)
		{
			InstancesWire.Insert(obj.ToData());
		}
		if (obj.Remove)
		{
			ObjectDatas.RemoveAt(i);
			delete &obj;
			i--;
		}
	}
}



void PolyHedraUIPalletManager::ChangeMedia(PolyHedraUIManager & manager)
{
	BufferFull.MainBuffer.Init(manager.BufferLayoutFullMain);
	BufferFull.InstBuffer.Init(manager.BufferLayoutFullInst);
	BufferWire.MainBuffer.Init(manager.BufferLayoutWireMain);
	BufferWire.InstBuffer.Init(manager.BufferLayoutWireInst);
}
void PolyHedraUIPalletManager::GraphicsCreate()
{
	if (!GraphicsExist)
	{
		BufferFull.Create();
		BufferWire.Create();
		GraphicsExist = true;

		BufferFull.MainBuffer.DataWant = true;
		BufferWire.MainBuffer.DataWant = true;
		BufferWire.ElemBuffer.DataWant = true;
	}
}
void PolyHedraUIPalletManager::GraphicsDelete()
{
	if (GraphicsExist)
	{
		BufferFull.Delete();
		BufferWire.Delete();
		GraphicsExist = false;
	}
}



void PolyHedraUIPalletManager::UpdateFullBufferMain()
{
	if (Pallet == nullptr) { return; }

	if (BufferFull.MainBuffer.DataWant)
	{
		Pallet -> Calc_Face_Normals();
		Container::Array<PolyHedraFull::Main::Data> data = Pallet -> ToMainData();
		BufferFull.MainBuffer.DataFull(data.ToVoid());

		TextureFull.Delete();
		if (Pallet -> Skins.Count() == 1)
		{
			TextureFull = Pallet -> Skins[0] -> ToTexture();
		}

		BufferFull.MainBuffer.DataWant = false;
	}
}
void PolyHedraUIPalletManager::DrawFull()
{
	if (!GraphicsExist) { return; }
	BufferFull.Bind();
	BufferFull.MainBuffer.Update();
	BufferFull.InstBuffer.Update();
	UpdateFullBufferMain();
	BufferFull.InstBuffer.DataFull(InstancesFull.ToVoid());
	TextureFull.Bind();
	BufferFull.Draw();
}

void PolyHedraUIPalletManager::UpdateWireBufferMain()
{
	if (Pallet == nullptr) { return; }

	if (BufferWire.MainBuffer.DataWant)
	{
		Container::Binary<PolyHedraWire::Main::Data> data;
		for (unsigned int i = 0; i < Pallet -> Corners.Count(); i++)
		{
			data.Insert(PolyHedraWire::Main::Data(Pallet -> Corners[i].Position, ColorF4(1, 1, 1)));
		}
		BufferWire.MainBuffer.DataFull(data.ToVoid());
		BufferWire.MainBuffer.DataWant = false;
	}

	if (BufferWire.ElemBuffer.DataWant)
	{
		BufferWire.ElemBuffer.DataFull(Pallet -> Edges.ToVoid());
		BufferWire.ElemBuffer.DataWant = false;
	}
}
void PolyHedraUIPalletManager::DrawWire()
{
	if (!GraphicsExist) { return; }
	BufferWire.Bind();
	BufferWire.MainBuffer.Update();
	BufferWire.InstBuffer.Update();
	UpdateWireBufferMain();
	BufferWire.InstBuffer.DataFull(InstancesWire.ToVoid());
	BufferWire.Draw();
}
