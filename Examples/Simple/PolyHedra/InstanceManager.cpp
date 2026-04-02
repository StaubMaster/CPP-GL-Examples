#include "PolyHedra/InstanceManager.hpp"
#include "PolyHedra/ObjectData.hpp"

#include "PolyHedra/PolyHedra.hpp"
#include "PolyHedra/Main/Data.hpp"
#include "Miscellaneous/Container/Pointer.hpp"
#include "PolyHedra/Graphics/Full/Main/Data.hpp"
#include "Miscellaneous/Container/Array.hpp"

#include "PolyHedra/Skin/Skin2DA.hpp"



PolyHedraInstanceManager::~PolyHedraInstanceManager()
{ }
PolyHedraInstanceManager::PolyHedraInstanceManager()
	: PolyHedra(nullptr)
	, PolyHedraChanged(false)
	, BufferFull(GL::DrawMode::Triangles)
	, Instances()
{ }
PolyHedraInstanceManager::PolyHedraInstanceManager(const PolyHedraInstanceManager & other)
	: PolyHedra(other.PolyHedra)
	, PolyHedraChanged(other.PolyHedraChanged)
	, BufferFull(other.BufferFull)
	, Instances()
{ }
PolyHedraInstanceManager & PolyHedraInstanceManager::operator=(const PolyHedraInstanceManager & other)
{
	PolyHedra = other.PolyHedra;
	PolyHedraChanged = other.PolyHedraChanged;
	BufferFull = other.BufferFull;
	Instances.Clear();
	return *this;
}

PolyHedraInstanceManager::PolyHedraInstanceManager(::PolyHedra * polyhedra)
	: PolyHedra(polyhedra)
	, PolyHedraChanged(true)
	, BufferFull(GL::DrawMode::Triangles)
	, Instances()
{ }
void PolyHedraInstanceManager::Change(::PolyHedra * polyhedra)
{
	PolyHedra = polyhedra;
	PolyHedraChanged = true;
}



void PolyHedraInstanceManager::GraphicsCreate()
{
	BufferFull.Create();
}
void PolyHedraInstanceManager::GraphicsDelete()
{
	BufferFull.Delete();
}

void PolyHedraInstanceManager::InitExternal()
{
	BufferFull.Main.Position.Change(0);
	BufferFull.Main.Normal.Change(1);
	BufferFull.Main.Texture.Change(2);
	//BufferFull.Inst.Data.Pos.Change(3);
	//BufferFull.Inst.Data.Rot.Change(4, 5, 6);
	BufferFull.Inst.Data.Change(3, 4, 5, 6);
}
void PolyHedraInstanceManager::InitInternal()
{
	BufferFull.Main.ChangeAttributeBinding();
	BufferFull.Inst.ChangeAttributeBinding();
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
	BufferFull.Main.Change(data1);
	data0.Clear();

	if (PolyHedra -> Skin != NULL)
	{
		//_Texture = _PolyHedra -> Skin -> ToTexture();
		Skin2DA * skin = (Skin2DA*)(PolyHedra -> Skin);
		//skin -> ToTexture(Buffer.Texture);
		skin -> ToTexture(Texture);
	}
	else
	{
		//_Texture = NULL;
		//Buffer.Texture.Delete();
		Texture.Delete();
	}
}
void PolyHedraInstanceManager::UpdateBufferInst()
{
	BufferFull.Inst.Change(Instances);
}
void PolyHedraInstanceManager::DrawFull()
{
	if (PolyHedraChanged)
	{
		UpdateBufferMain();
		PolyHedraChanged = false;
	}
	UpdateBufferInst();
	Texture.Bind();
	BufferFull.Draw();
}



void PolyHedraInstanceManager::Clear()
{
	Instances.Clear();
}
void PolyHedraInstanceManager::Place(const PolyHedraObjectData & obj)
{
	if (obj.PolyHedra == PolyHedra)
	{
		Instances.Insert(obj.Trans.ToMatrixForward());
	}
}
void PolyHedraInstanceManager::Place(const Container::Member<PolyHedraObjectData> & objs)
{
	for (unsigned int i = 0; i < objs.Count(); i++)
	{
		Place(objs[i]);
	}
}
