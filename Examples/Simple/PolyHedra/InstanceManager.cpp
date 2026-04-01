#include "PolyHedra/InstanceManager.hpp"
#include "PolyHedra/ObjectData.hpp"

#include "PolyHedra/PolyHedra.hpp"
#include "PolyHedra/Main/Data.hpp"
#include "Miscellaneous/Container/Pointer.hpp"
#include "PolyHedra/Graphics/Full/Main/Data.hpp"
#include "Miscellaneous/Container/Array.hpp"



PolyHedraInstanceManager::~PolyHedraInstanceManager()
{ }
PolyHedraInstanceManager::PolyHedraInstanceManager()
	: PolyHedra(nullptr)
	, Buffer(GL::DrawMode::Triangles)
	, Instances()
{ }
PolyHedraInstanceManager::PolyHedraInstanceManager(const PolyHedraInstanceManager & other)
	: PolyHedra(other.PolyHedra)
	, Buffer(other.Buffer)
	, Instances()
{ }
PolyHedraInstanceManager & PolyHedraInstanceManager::operator=(const PolyHedraInstanceManager & other)
{
	PolyHedra = other.PolyHedra;
	Buffer = other.Buffer;
	Instances.Clear();
	return *this;
}

PolyHedraInstanceManager::PolyHedraInstanceManager(::PolyHedra * polyhedra)
	: PolyHedra(polyhedra)
	, PolyHedraChanged(true)
	, Buffer(GL::DrawMode::Triangles)
	, Instances()
{ }
void PolyHedraInstanceManager::Change(::PolyHedra * polyhedra)
{
	PolyHedra = polyhedra;
	PolyHedraChanged = true;
}



void PolyHedraInstanceManager::GraphicsCreate()
{
	Buffer.Create();
}
void PolyHedraInstanceManager::GraphicsDelete()
{
	Buffer.Delete();
}

void PolyHedraInstanceManager::InitExternal()
{
	Buffer.Main.Position.Change(0);
	Buffer.Main.Normal.Change(1);
	Buffer.Main.Texture.Change(2);
	Buffer.Inst.Data.Pos.Change(3);
	Buffer.Inst.Data.Rot.Change(4, 5, 6);
}
void PolyHedraInstanceManager::InitInternal()
{
	Buffer.Main.ChangeAttributeBinding();
	Buffer.Inst.ChangeAttributeBinding();
}



void PolyHedraInstanceManager::UpdateBufferMain()
{
	if (PolyHedra == nullptr) { return; }

	Container::Pointer<PolyHedra_Main::Data> data0 = PolyHedra -> ToMainData();
	Container::Array<PolyHedraFull::Main::Data> data1(data0.Count());
	for (unsigned int i = 0; i < data1.Count(); i++)
	{
		data1[i].Position = data0[i].Position;
		data1[i].Normal = data0[i].Normal;
		data1[i].Texture = data0[i].Texture;
	}
	Buffer.Main.Change(data1);
	data0.Clear();
}
void PolyHedraInstanceManager::UpdateBufferInst()
{
	Buffer.Inst.Change(Instances);
}
void PolyHedraInstanceManager::Draw()
{
	if (PolyHedraChanged)
	{
		UpdateBufferMain();
		PolyHedraChanged = false;
	}
	UpdateBufferInst();
	Buffer.Draw();
}



void PolyHedraInstanceManager::Clear()
{
	Instances.Clear();
}
void PolyHedraInstanceManager::Place(const PolyHedraObjectData & obj)
{
	if (obj.PolyHedra == PolyHedra)
	{
		Instances.Insert(obj.Trans);
	}
}
void PolyHedraInstanceManager::Place(const Container::Member<PolyHedraObjectData> & objs)
{
	for (unsigned int i = 0; i < objs.Count(); i++)
	{
		Place(objs[i]);
	}
}
