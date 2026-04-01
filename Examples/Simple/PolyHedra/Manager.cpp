#include "PolyHedra/Manager.hpp"
#include "PolyHedra/ObjectData.hpp"

#include "DirectoryInfo.hpp"
#include "Graphics/Shader/Code.hpp"
#include "Miscellaneous/Container/Array.hpp"



PolyHedraManager::~PolyHedraManager()
{ }
PolyHedraManager::PolyHedraManager()
	: InstanceManagers()
	, FullShader()
{ }



void PolyHedraManager::GraphicsCreate()
{
	FullShader.Create();
	for (unsigned int i = 0; i < InstanceManagers.Count(); i++)
	{
		InstanceManagers[i].GraphicsCreate();
	}
}
void PolyHedraManager::GraphicsDelete()
{
	FullShader.Delete();
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
		FullShader.Change(code);
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



Undex PolyHedraManager::Find(::PolyHedra * polyhedra)
{
	for (unsigned int i = 0; i < InstanceManagers.Count(); i++)
	{
		if (InstanceManagers[i].PolyHedra == polyhedra)
		{
			return Undex(i);
		}
	}
	return Undex::Invalid();
}
Undex PolyHedraManager::Place(::PolyHedra * polyhedra)
{
	Undex u(InstanceManagers.Count());
	InstanceManagers.Insert(PolyHedraInstanceManager(polyhedra));
	return u;
}

PolyHedraObjectData PolyHedraManager::Place(Undex polyhedra_undex, Trans3D data)
{
	return PolyHedraObjectData(InstanceManagers[polyhedra_undex].PolyHedra, data);
}
PolyHedraObjectData PolyHedraManager::Place(::PolyHedra * polyhedra, Trans3D data)
{
	Undex u = Find(polyhedra);
	if (!u.IsValid())
	{
		u = Place(polyhedra);
	}
	return Place(u, data);
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
void PolyHedraManager::PlaceInstance(const Container::Member<PolyHedraObjectData> & objs)
{
	for (unsigned int i = 0; i < InstanceManagers.Count(); i++)
	{
		InstanceManagers[i].Place(objs);
	}
}
void PolyHedraManager::Draw()
{
	for (unsigned int i = 0; i < InstanceManagers.Count(); i++)
	{
		InstanceManagers[i].Draw();
	}
}
