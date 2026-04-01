#include "PolyHedra/Manager.hpp"
#include "PolyHedra/ObjectData.hpp"

#include "DirectoryInfo.hpp"
#include "Graphics/Shader/Code.hpp"
#include "Miscellaneous/Container/Array.hpp"





PolyHedraManager * PolyHedraManager::CurrentPointer = nullptr;
PolyHedraManager & PolyHedraManager::Current() { return *CurrentPointer; }
bool PolyHedraManager::CheckCurrent() { return (PolyHedraManager::CurrentPointer != nullptr); }
void PolyHedraManager::ClearCurrent() { PolyHedraManager::CurrentPointer = nullptr; }
bool PolyHedraManager::IsCurrent() const { return (PolyHedraManager::CurrentPointer == this); }
void PolyHedraManager::MakeCurrent() { PolyHedraManager::CurrentPointer = this; }





PolyHedraManager::~PolyHedraManager()
{ }
PolyHedraManager::PolyHedraManager()
	: ObjectDatas()
	, ShaderFullDefault()
	, ShaderFullOther(nullptr)
	, InstanceManagers()
{ }



void PolyHedraManager::GraphicsCreate()
{
	ShaderFullDefault.Create();
	for (unsigned int i = 0; i < InstanceManagers.Count(); i++)
	{
		InstanceManagers[i].GraphicsCreate();
	}
}
void PolyHedraManager::GraphicsDelete()
{
	ShaderFullDefault.Delete();
	for (unsigned int i = 0; i < InstanceManagers.Count(); i++)
	{
		InstanceManagers[i].GraphicsDelete();
	}
}

void PolyHedraManager::InitExternal(DirectoryInfo & media_dir)
{
	{
		Container::Array<Shader::Code> code({
			Shader::Code(media_dir.File("Shaders/PH/Simple3D.vert")),
			Shader::Code(media_dir.File("Shaders/PH/Full.frag")),
		});
		ShaderFullDefault.Change(code);
	}
	for (unsigned int i = 0; i < InstanceManagers.Count(); i++)
	{
		InstanceManagers[i].InitExternal();
	}
}
void PolyHedraManager::InitInternal()
{
	for (unsigned int i = 0; i < InstanceManagers.Count(); i++)
	{
		InstanceManagers[i].InitInternal();
	}
}



unsigned int PolyHedraManager::FindPolyHedra(::PolyHedra * polyhedra)
{
	for (unsigned int i = 0; i < InstanceManagers.Count(); i++)
	{
		if (InstanceManagers[i].PolyHedra == polyhedra)
		{
			return i;
		}
	}
	return 0xFFFFFFFF;
}
unsigned int PolyHedraManager::PlacePolyHedra(::PolyHedra * polyhedra)
{
	unsigned int idx = InstanceManagers.Count();
	InstanceManagers.Insert(PolyHedraInstanceManager(polyhedra));
	return idx;
}

PolyHedraObjectData * PolyHedraManager::PlaceObject(unsigned int polyhedra, Trans3D trans)
{
	PolyHedraObjectData * obj = new PolyHedraObjectData(InstanceManagers[polyhedra].PolyHedra, trans);
	ObjectDatas.Insert(obj);
	return obj;
}
PolyHedraObjectData * PolyHedraManager::PlaceObject(::PolyHedra * polyhedra, Trans3D trans)
{
	unsigned int idx = FindPolyHedra(polyhedra);
	if (idx == 0xFFFFFFFF)
	{
		idx = PlacePolyHedra(polyhedra);
	}
	return PlaceObject(idx, trans);
}
PolyHedraObjectData * PolyHedraManager::CopyObject(const PolyHedraObjectData * obj)
{
	if (obj == nullptr) { return nullptr; }
	return PlaceObject(obj -> PolyHedra, obj -> Trans);
}



void PolyHedraManager::ClearInstances()
{
	for (unsigned int i = 0; i < InstanceManagers.Count(); i++)
	{
		InstanceManagers[i].Clear();
	}
}
void PolyHedraManager::PlaceInstance(const PolyHedraObjectData & obj)
{
	for (unsigned int i = 0; i < InstanceManagers.Count(); i++)
	{
		InstanceManagers[i].Place(obj);
	}
}



void PolyHedraManager::Update()
{
	ClearInstances();
	for (unsigned int i = 0; i < ObjectDatas.Count(); i++)
	{
		if (ObjectDatas[i] != nullptr)
		{
			PolyHedraObjectData & obj = *ObjectDatas[i];
			if (obj.Draw)
			{
				PlaceInstance(obj);
			}
			if (obj.Remove)
			{
				ObjectDatas.Remove(i);
				delete &obj;
				i--;
			}
		}
	}
}
void PolyHedraManager::Draw()
{
	if (ShaderFullOther == nullptr)
	{
		ShaderFullDefault.Bind();
	}
	else
	{
		ShaderFullOther -> Bind();
	}
	for (unsigned int i = 0; i < InstanceManagers.Count(); i++)
	{
		InstanceManagers[i].DrawFull();
	}
}
