#include "PolyHedraUI/Manager.hpp"
#include "PolyHedraUI/ObjectData.hpp"
#include "PolyHedraUI/PalletManager.hpp"

#include "DirectoryInfo.hpp"
#include "Graphics/Shader/Code.hpp"
#include "Miscellaneous/Container/Array.hpp"





PolyHedraUIBufferLayoutInst::~PolyHedraUIBufferLayoutInst()
{ }
PolyHedraUIBufferLayoutInst::PolyHedraUIBufferLayoutInst()
	: ::Attribute::Layout(1, sizeof(PolyHedraUIData))
	, Trans(*this)
	, Normal(*this)
	, Scale(*this)
	, Color(*this)
{ }
PolyHedraUIBufferLayoutInst::PolyHedraUIBufferLayoutInst(const PolyHedraUIBufferLayoutInst & other)
	: ::Attribute::Layout(other)
	, Trans(*this, other.Trans)
	, Normal(*this, other.Normal)
	, Scale(*this, other.Scale)
	, Color(*this, other.Color)
{ }





PolyHedraUIManager * PolyHedraUIManager::CurrentPointer = nullptr;
PolyHedraUIManager & PolyHedraUIManager::Current() { return *CurrentPointer; }
bool PolyHedraUIManager::CheckCurrent() { return (PolyHedraUIManager::CurrentPointer != nullptr); }
void PolyHedraUIManager::ClearCurrent() { PolyHedraUIManager::CurrentPointer = nullptr; }
bool PolyHedraUIManager::IsCurrent() const { return (PolyHedraUIManager::CurrentPointer == this); }
void PolyHedraUIManager::MakeCurrent() { PolyHedraUIManager::CurrentPointer = this; }





PolyHedraUIManager::~PolyHedraUIManager()
{ }
PolyHedraUIManager::PolyHedraUIManager()
	: InstanceManagers()
	, GraphicsExist(false)
	, ShaderFullDefault()
	, ShaderWireDefault()
	, ShaderFullOther(nullptr)
	, ShaderWireOther(nullptr)
	, ShaderLayoutFullDefault()
	, BufferLayoutFullMain()
	, BufferLayoutFullInst()
	, ShaderLayoutWireDefault()
	, BufferLayoutWireMain()
	, BufferLayoutWireInst()
{
	ShaderFullDefault.UniformLayout = &ShaderLayoutFullDefault;
	ShaderLayoutFullDefault.Shader = &ShaderFullDefault;

	ShaderWireDefault.UniformLayout = &ShaderLayoutWireDefault;
	ShaderLayoutWireDefault.Shader = &ShaderWireDefault;
}



void PolyHedraUIManager::MakeInstances()
{
	for (unsigned int i = 0; i < InstanceManagers.Count(); i++)
	{
		if (InstanceManagers[i] != nullptr)
		{
			InstanceManagers[i] -> MakeInstances();
		}
	}
}

::PolyHedraUIPalletManager * PolyHedraUIManager::FindPallet(::PolyHedra * pallet)
{
	for (unsigned int i = 0; i < InstanceManagers.Count(); i++)
	{
		if (InstanceManagers[i] != nullptr)
		{
			if (InstanceManagers[i] -> Pallet == pallet)
			{
				return InstanceManagers[i];
			}
		}
	}
	return nullptr;
}
::PolyHedraUIPalletManager * PolyHedraUIManager::PlacePallet(::PolyHedra * pallet)
{
	unsigned int idx = InstanceManagers.Count();
	InstanceManagers.Insert(new PolyHedraUIPalletManager(pallet));
	if (GraphicsExist)
	{
		if (InstanceManagers[idx] != nullptr)
		{
			InstanceManagers[idx] -> ChangeMedia(*this);
			InstanceManagers[idx] -> GraphicsCreate();
		}
	}
	return InstanceManagers[idx];
}



PolyHedraUIObjectData * PolyHedraUIManager::PlaceObject(::PolyHedraUIPalletManager * pallet)
{
	if (pallet == nullptr) { return nullptr; }
	return pallet -> PlaceObject();
}
PolyHedraUIObjectData * PolyHedraUIManager::PlaceObject(::PolyHedra * pallet)
{
	::PolyHedraUIPalletManager * manager = FindPallet(pallet);
	if (manager == nullptr)
	{
		manager = PlacePallet(pallet);
	}
	return PlaceObject(manager);
}



PolyHedraUIObjectData * PolyHedraUIManager::TryPlaceObject(PolyHedraUIManager * manager, ::PolyHedraUIPalletManager * pallet)
{
	if (manager == nullptr) { manager = PolyHedraUIManager::CurrentPointer; }
	if (manager == nullptr) { return nullptr; }
	return manager -> PlaceObject(pallet);
}
PolyHedraUIObjectData * PolyHedraUIManager::TryPlaceObject(PolyHedraUIManager * manager, ::PolyHedra * pallet)
{
	if (manager == nullptr) { manager = PolyHedraUIManager::CurrentPointer; }
	if (manager == nullptr) { return nullptr; }
	return manager -> PlaceObject(pallet);
}



void PolyHedraUIManager::ChangeMedia(const DirectoryInfo & dir)
{
	{
		ShaderFullDefault.Change({
			//dir.File("Shaders/Basic3D/FullUI.vert"),
			//dir.File("Shaders/Basic3D/FullUI.frag"),
			dir.File("Shaders/PolyHedra/UserInterface.vert"),
			dir.File("Shaders/PolyHedra/TexturedNoLight.frag"),
		});
	}
	{
		BufferLayoutFullMain.Position.Change(0);
		BufferLayoutFullMain.Normal.Change(1);
		BufferLayoutFullMain.Texture.Change(2);

		BufferLayoutFullInst.Trans.Change(3);
		BufferLayoutFullInst.Normal.Change(7);
		BufferLayoutFullInst.Scale.Change(11);
		BufferLayoutFullInst.Color.Change(12);
	}
	{
		ShaderWireDefault.Change({
			dir.File("Shaders/Basic3D/Wire.vert"),
			dir.File("Shaders/Basic3D/Wire.frag"),
		});
	}
	{
		BufferLayoutWireMain.Pos.Change(0);
		BufferLayoutWireMain.Col.Change(1);

		BufferLayoutWireInst.Trans.Change(3);
		BufferLayoutWireInst.Normal.Change(-1);
	}
}

void PolyHedraUIManager::GraphicsCreate()
{
	if (GraphicsExist) { return; }

	ShaderFullDefault.Create();
	ShaderWireDefault.Create();
	for (unsigned int i = 0; i < InstanceManagers.Count(); i++)
	{
		if (InstanceManagers[i] != nullptr)
		{
			InstanceManagers[i] -> ChangeMedia(*this);
			InstanceManagers[i] -> GraphicsCreate();
		}
	}

	GraphicsExist = true;
}
void PolyHedraUIManager::GraphicsDelete()
{
	if (!GraphicsExist) { return; }

	ShaderFullDefault.Delete();
	ShaderWireDefault.Delete();
	for (unsigned int i = 0; i < InstanceManagers.Count(); i++)
	{
		if (InstanceManagers[i] != nullptr)
		{
			InstanceManagers[i] -> GraphicsDelete();
		}
	}

	GraphicsExist = false;
}

void PolyHedraUIManager::DrawFull()
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
		if (InstanceManagers[i] != nullptr)
		{
			InstanceManagers[i] -> DrawFull();
		}
	}
}
void PolyHedraUIManager::DrawWire()
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
		if (InstanceManagers[i] != nullptr)
		{
			InstanceManagers[i] -> DrawWire();
		}
	}
}
