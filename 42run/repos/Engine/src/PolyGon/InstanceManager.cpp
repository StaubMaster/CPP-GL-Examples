#include "PolyGon/InstanceManager.hpp"
#include "PolyGon/ObjectData.hpp"

#include "PolyGon/PolyGon.hpp"
#include "PolyGon/Graphics/Full/Main/Data.hpp"

#include "Generics/Container/Array.hpp"
#include <iostream>



PolyGonInstanceManager::~PolyGonInstanceManager()
{ }
PolyGonInstanceManager::PolyGonInstanceManager()
	: PolyGon(nullptr)
	, UpdateFullMain(false)
	, UpdateWireMain(false)
	, BufferFull()
	, BufferWire()
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
	, BufferFull()
	, BufferWire()
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
	//BufferFull.MainBuffer.Init(LayoutMainFull);
	//BufferWire.MainBuffer.Init(LayoutMainWire);
	//BufferFull.InstBuffer.Init(LayoutInstFull);
	//BufferWire.InstBuffer.Init(LayoutInstWire);
	//BufferFull.ChangeAttributeLayoutMain(LayoutMainFull);
	//BufferFull.ChangeAttributeLayoutInst(LayoutInstFull);
	//BufferWire.ChangeAttributeLayoutMain(LayoutMainWire);
	//BufferWire.ChangeAttributeLayoutInst(LayoutInstWire);

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
		LayoutMainFull.Pos.Change(0);
		LayoutMainFull.Col.Change(1);
		LayoutInstFull.Trans.Change(2);

		//BufferFull.MainBuffer.Init(LayoutMainFull);
		//BufferFull.InstBuffer.Init(LayoutInstFull);
		//BufferFull.ChangeAttributeLayoutMain(LayoutMainFull);
		//BufferFull.ChangeAttributeLayoutInst(LayoutInstFull);
	}
	{
		LayoutMainWire.Pos.Change(0);
		LayoutMainWire.Col.Change(1);
		LayoutInstWire.Trans.Change(2);

		//BufferWire.MainBuffer.Init(LayoutMainWire);
		//BufferWire.InstBuffer.Init(LayoutInstWire);
		//BufferWire.ChangeAttributeLayoutMain(LayoutMainWire);
		//BufferWire.ChangeAttributeLayoutInst(LayoutInstWire);
	}
}
void PolyGonInstanceManager::InitInternal()
{
	{
		//BufferFull.MainBuffer.Update();
		//BufferFull.InstBuffer.Update();
		//BufferFull.InitAttributeLayoutMain(BufferFull.MainBuffer);
		//BufferFull.InitAttributeLayoutInst(BufferFull.InstBuffer);
	}
	{
		//BufferWire.MainBuffer.Update();
		//BufferWire.ElemBuffer.Update();
		//BufferWire.InstBuffer.Update();
		//BufferWire.InitAttributeLayoutMain(BufferWire.MainBuffer);
		//BufferWire.InitAttributeLayoutInst(BufferWire.InstBuffer);
	}
}



void PolyGonInstanceManager::UpdateBufferFullMain()
{
	if (PolyGon == nullptr) { return; }

	Container::Array<PolyGonFull::Main::Data> data = PolyGon -> ToFullData();
	BufferFull.MainBuffer.DataFull(data.ToVoid());
	BufferFull.MainBuffer.Count = data.Length();
}
void PolyGonInstanceManager::UpdateBufferFullInst()
{
	BufferFull.InstBuffer.DataFull(InstancesFull.ToVoid());
	BufferFull.InstBuffer.Count = InstancesFull.Count();
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

	BufferWire.MainBuffer.DataFull(PolyGon -> Corners.ToVoid());
	BufferWire.ElemBuffer.DataFull(PolyGon -> Edges.ToVoid());
	BufferWire.MainBuffer.Count = PolyGon -> Corners.Count();
	BufferWire.ElemBuffer.Count = PolyGon -> Edges.Count();
}
void PolyGonInstanceManager::UpdateBufferWireInst()
{
	BufferWire.InstBuffer.DataFull(InstancesWire.ToVoid());
	BufferWire.InstBuffer.Count = InstancesWire.Count();
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
void PolyGonInstanceManager::PlaceInstances(const Container::Array<PolyGonObjectData> & objs)
{
	for (unsigned int i = 0; i < objs.Length(); i++)
	{
		PlaceInstance(objs[i]);
	}
}
