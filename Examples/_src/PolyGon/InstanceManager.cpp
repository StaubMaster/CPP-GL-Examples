#include "PolyGon/InstanceManager.hpp"
#include "PolyGon/ObjectData.hpp"

#include "PolyGon/PolyGon.hpp"
#include "Miscellaneous/Container/Pointer.hpp"
#include "PolyGon/Graphics/Full/Main/Data.hpp"

#include "Miscellaneous/Container/Array.hpp"
#include <iostream>



PolyGonInstanceManager::~PolyGonInstanceManager()
{ }
PolyGonInstanceManager::PolyGonInstanceManager()
	: PolyGon(nullptr)
	, UpdateFullMain(false)
	, UpdateWireMain(false)
	, BufferFull(GL::DrawMode::Triangles)
	, BufferWire(GL::DrawMode::Lines, 2)
	, InstancesFull()
	, InstancesWire()
{ }
PolyGonInstanceManager::PolyGonInstanceManager(const PolyGonInstanceManager & other)
	: PolyGon(other.PolyGon)
	, UpdateFullMain(other.UpdateFullMain)
	, UpdateWireMain(other.UpdateWireMain)
	, BufferFull(other.BufferFull)
	, BufferWire(other.BufferWire)
	, InstancesFull()
	, InstancesWire()
{ }
PolyGonInstanceManager & PolyGonInstanceManager::operator=(const PolyGonInstanceManager & other)
{
	PolyGon = other.PolyGon;
	UpdateFullMain = other.UpdateFullMain;
	UpdateWireMain = other.UpdateWireMain;
	BufferFull = other.BufferFull;
	BufferWire = other.BufferWire;
	InstancesFull.Clear();
	InstancesWire.Clear();
	return *this;
}

PolyGonInstanceManager::PolyGonInstanceManager(::PolyGon * PolyGon)
	: PolyGon(PolyGon)
	, UpdateFullMain(true)
	, UpdateWireMain(true)
	, BufferFull(GL::DrawMode::Triangles)
	, BufferWire(GL::DrawMode::Lines, 2)
	, InstancesFull()
	, InstancesWire()
{ }
void PolyGonInstanceManager::Change(::PolyGon * PolyGon)
{
	PolyGon = PolyGon;
	UpdateFullMain = true;
	UpdateWireMain = true;
}



void PolyGonInstanceManager::GraphicsCreate()
{
	BufferFull.Create();
	BufferWire.Create();
}
void PolyGonInstanceManager::GraphicsDelete()
{
	BufferFull.Delete();
	BufferWire.Delete();
}

void PolyGonInstanceManager::InitExternal()
{
	{
		BufferFull.Main.Pos.Change(0);
		BufferFull.Main.Col.Change(1);
		BufferFull.Inst.Trans.Change(2, 3, 4);
	}
	{
		BufferWire.Main.Pos.Change(0);
		BufferWire.Main.Col.Change(1);
		BufferWire.Inst.Trans.Change(2, 3, 4);
	}
}
void PolyGonInstanceManager::InitInternal()
{
	{
		BufferFull.Main.Init();
		BufferFull.Inst.Init();
	}
	{
		BufferWire.Main.Init();
		BufferWire.Elem.Init();
		BufferWire.Inst.Init();
	}
}



void PolyGonInstanceManager::UpdateBufferFullMain()
{
	if (PolyGon == nullptr) { return; }

	Container::Pointer<PolyGonFull::Main::Data> data = PolyGon -> ToFullData();
	BufferFull.Main.Change(data);
	data.Delete();
}
void PolyGonInstanceManager::UpdateBufferFullInst()
{
	BufferFull.Inst.Change(InstancesFull);
}
void PolyGonInstanceManager::DrawFull()
{
	if (UpdateFullMain)
	{
		UpdateBufferFullMain();
		UpdateFullMain = false;
	}
	UpdateBufferFullInst();
	BufferFull.Draw();
}



void PolyGonInstanceManager::UpdateBufferWireMain()
{
	if (PolyGon == nullptr) { return; }

	BufferWire.Main.Change(PolyGon -> Corners);
	BufferWire.Elem.Change(PolyGon -> Edges);
}
void PolyGonInstanceManager::UpdateBufferWireInst()
{
	BufferWire.Inst.Change(InstancesWire);
}
void PolyGonInstanceManager::DrawWire()
{
	if (UpdateWireMain)
	{
		UpdateBufferWireMain();
		UpdateWireMain = false;
	}
	UpdateBufferWireInst();
	BufferWire.Draw();
}



void PolyGonInstanceManager::ClearInstances()
{
	InstancesFull.Clear();
	InstancesWire.Clear();
}
void PolyGonInstanceManager::PlaceInstance(const PolyGonObjectData & obj)
{
	if (obj.PolyGon == PolyGon)
	{
		if (obj.DrawFull)
		{
			InstancesFull.Insert(Instance::Basic2D::Data(obj.Trans));
		}
		if (obj.DrawWire)
		{
			InstancesWire.Insert(Instance::Basic2D::Data(obj.Trans));
		}
	}
}
void PolyGonInstanceManager::PlaceInstances(const Container::Member<PolyGonObjectData> & objs)
{
	for (unsigned int i = 0; i < objs.Count(); i++)
	{
		PlaceInstance(objs[i]);
	}
}
