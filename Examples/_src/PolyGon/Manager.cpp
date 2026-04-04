#include "PolyGon/Manager.hpp"
#include "PolyGon/ObjectData.hpp"

#include "DirectoryInfo.hpp"
#include "Graphics/Shader/Code.hpp"
#include "Miscellaneous/Container/Array.hpp"





PolyGonManager * PolyGonManager::CurrentPointer = nullptr;
PolyGonManager & PolyGonManager::Current() { return *CurrentPointer; }
bool PolyGonManager::CheckCurrent() { return (PolyGonManager::CurrentPointer != nullptr); }
void PolyGonManager::ClearCurrent() { PolyGonManager::CurrentPointer = nullptr; }
bool PolyGonManager::IsCurrent() const { return (PolyGonManager::CurrentPointer == this); }
void PolyGonManager::MakeCurrent() { PolyGonManager::CurrentPointer = this; }





PolyGonManager::~PolyGonManager()
{ }
PolyGonManager::PolyGonManager()
	: ObjectDatas()
	, ShaderFullDefault()
	, ShaderWireDefault()
	, ShaderFullOther(nullptr)
	, ShaderWireOther(nullptr)
	, InstanceManagers()
{ }



void PolyGonManager::GraphicsCreate()
{
	ShaderFullDefault.Create();
	ShaderWireDefault.Create();
	for (unsigned int i = 0; i < InstanceManagers.Count(); i++)
	{
		InstanceManagers[i].GraphicsCreate();
	}
}
void PolyGonManager::GraphicsDelete()
{
	ShaderFullDefault.Delete();
	ShaderWireDefault.Delete();
	for (unsigned int i = 0; i < InstanceManagers.Count(); i++)
	{
		InstanceManagers[i].GraphicsDelete();
	}
}

void PolyGonManager::InitExternal(DirectoryInfo & media_dir)
{
	{
		Container::Array<Shader::Code> code({
			Shader::Code(media_dir.File("Shaders/Basic2D/Full.vert")),
			Shader::Code(media_dir.File("Shaders/Basic2D/Basic.frag")),
		});
		ShaderFullDefault.Change(code);
	}
	{
		Container::Array<Shader::Code> code({
			Shader::Code(media_dir.File("Shaders/Basic2D/Wire.vert")),
			Shader::Code(media_dir.File("Shaders/Basic2D/Basic.frag")),
		});
		ShaderWireDefault.Change(code);
	}
	for (unsigned int i = 0; i < InstanceManagers.Count(); i++)
	{
		InstanceManagers[i].InitExternal();
	}
}
void PolyGonManager::InitInternal()
{
	for (unsigned int i = 0; i < InstanceManagers.Count(); i++)
	{
		InstanceManagers[i].InitInternal();
	}
}



unsigned int PolyGonManager::FindPolyGon(::PolyGon * PolyGon)
{
	for (unsigned int i = 0; i < InstanceManagers.Count(); i++)
	{
		if (InstanceManagers[i].PolyGon == PolyGon)
		{
			return i;
		}
	}
	return 0xFFFFFFFF;
}
unsigned int PolyGonManager::PlacePolyGon(::PolyGon * PolyGon)
{
	unsigned int idx = InstanceManagers.Count();
	InstanceManagers.Insert(PolyGonInstanceManager(PolyGon));
	return idx;
}

PolyGonObjectData * PolyGonManager::PlaceObject(unsigned int PolyGon, Trans2D trans)
{
	PolyGonObjectData * obj = new PolyGonObjectData(InstanceManagers[PolyGon].PolyGon, trans);
	ObjectDatas.Insert(obj);
	return obj;
}
PolyGonObjectData * PolyGonManager::PlaceObject(::PolyGon * PolyGon, Trans2D trans)
{
	unsigned int idx = FindPolyGon(PolyGon);
	if (idx == 0xFFFFFFFF)
	{
		idx = PlacePolyGon(PolyGon);
	}
	return PlaceObject(idx, trans);
}
PolyGonObjectData * PolyGonManager::CopyObject(const PolyGonObjectData * obj)
{
	if (obj == nullptr) { return nullptr; }
	return PlaceObject(obj -> PolyGon, obj -> Trans);
}



void PolyGonManager::ClearInstances()
{
	for (unsigned int i = 0; i < InstanceManagers.Count(); i++)
	{
		InstanceManagers[i].ClearInstances();
	}
}
void PolyGonManager::PlaceInstance(const PolyGonObjectData & obj)
{
	for (unsigned int i = 0; i < InstanceManagers.Count(); i++)
	{
		InstanceManagers[i].PlaceInstance(obj);
	}
}



void PolyGonManager::Update()
{
	ClearInstances();
	for (unsigned int i = 0; i < ObjectDatas.Count(); i++)
	{
		if (ObjectDatas[i] != nullptr)
		{
			PolyGonObjectData & obj = *ObjectDatas[i];
			PlaceInstance(obj);
			if (obj.Remove)
			{
				ObjectDatas.Remove(i);
				delete &obj;
				i--;
			}
		}
	}
}
void PolyGonManager::DrawFull()
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
void PolyGonManager::DrawWire()
{
	if (ShaderWireOther == nullptr)
	{
		ShaderWireDefault.Bind();
	}
	else
	{
		ShaderWireOther -> Bind();
	}
	for (unsigned int i = 0; i < InstanceManagers.Count(); i++)
	{
		InstanceManagers[i].DrawWire();
	}
}
