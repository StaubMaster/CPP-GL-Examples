#include "PalletManager.hpp"
#include "Pallet.hpp"

#include "Graphics/VertexArray/Base.hpp"



NewPolyHedra::PalletManager * NewPolyHedra::PalletManager::Current = nullptr;



NewPolyHedra::PalletManager::~PalletManager()
{
	Current = nullptr;
}
NewPolyHedra::PalletManager::PalletManager()
	: Pallets()
	, BufferFullLayout(nullptr)
	, BufferWireLayout(nullptr)
{
	Current = this;
}



NewPolyHedra::Pallet * NewPolyHedra::PalletManager::FindPallet(PolyHedra * polyhedra) const
{
	if (polyhedra == nullptr) { return nullptr; }
	for (unsigned int i = 0; i < Pallets.Count(); i++)
	{
		NewPolyHedra::Pallet * pallet = Pallets[i];
		if (pallet == nullptr) { continue; }
		if (pallet -> Object == polyhedra)
		{
			return pallet;
		}
	}
	return nullptr;
}
NewPolyHedra::Pallet * NewPolyHedra::PalletManager::MakePallet(PolyHedra * polyhedra)
{
	if (polyhedra == nullptr) { return nullptr; }
	NewPolyHedra::Pallet * pallet = new NewPolyHedra::Pallet(polyhedra);
	pallet -> BufferFull.Layout = BufferFullLayout;
	pallet -> BufferWire.Layout = BufferWireLayout;
	pallet -> GraphicsCreate();
	pallet -> GraphicsPut();
	Pallets.Insert(pallet);
	return pallet;
}
NewPolyHedra::Pallet * NewPolyHedra::PalletManager::FindMakePallet(PolyHedra * polyhedra)
{
	if (polyhedra == nullptr) { return nullptr; }
	NewPolyHedra::Pallet * pallet = FindPallet(polyhedra);
	if (pallet == nullptr)
	{
		pallet = MakePallet(polyhedra);
	}
	return pallet;
}



void NewPolyHedra::PalletManager::GraphicsCreate()
{
	for (unsigned int i = 0; i < Pallets.Count(); i++)
	{
		NewPolyHedra::Pallet * pallet = Pallets[i];
		if (pallet == nullptr) { continue; }
		pallet -> GraphicsCreate();
	}
}
void NewPolyHedra::PalletManager::GraphicsDelete()
{
	for (unsigned int i = 0; i < Pallets.Count(); i++)
	{
		NewPolyHedra::Pallet * pallet = Pallets[i];
		if (pallet == nullptr) { continue; }
		pallet -> GraphicsDelete();
	}
}
