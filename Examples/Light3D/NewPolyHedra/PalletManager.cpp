#include "PalletManager.hpp"
#include "Pallet.hpp"

#include "Graphics/Buffer/VertexArray.hpp"



NewPolyHedra_PalletManager * NewPolyHedra_PalletManager::Current = nullptr;



NewPolyHedra_PalletManager::~NewPolyHedra_PalletManager()
{
	Current = nullptr;
}
NewPolyHedra_PalletManager::NewPolyHedra_PalletManager()
{
	Current = this;
}



NewPolyHedra_Pallet * NewPolyHedra_PalletManager::FindPallet(PolyHedra * polyhedra) const
{
	if (polyhedra == nullptr) { return nullptr; }
	for (unsigned int i = 0; i < Pallets.Count(); i++)
	{
		NewPolyHedra_Pallet * pallet = Pallets[i];
		if (pallet == nullptr) { continue; }
		if (pallet -> Is(polyhedra))
		{
			return pallet;
		}
	}
	return nullptr;
}
NewPolyHedra_Pallet * NewPolyHedra_PalletManager::MakePallet(PolyHedra * polyhedra)
{
	if (polyhedra == nullptr) { return nullptr; }
	NewPolyHedra_Pallet * pallet = new NewPolyHedra_Pallet(polyhedra);
	pallet -> Layout = PalletBufferLayout;
	pallet -> GraphicsCreate();
	pallet -> Put();
	Pallets.Insert(pallet);
	return pallet;
}
NewPolyHedra_Pallet * NewPolyHedra_PalletManager::FindMakePallet(PolyHedra * polyhedra)
{
	if (polyhedra == nullptr) { return nullptr; }
	NewPolyHedra_Pallet * pallet = FindPallet(polyhedra);
	if (pallet == nullptr)
	{
		pallet = MakePallet(polyhedra);
	}
	return pallet;
}



void NewPolyHedra_PalletManager::GraphicsCreate()
{
	for (unsigned int i = 0; i < Pallets.Count(); i++)
	{
		NewPolyHedra_Pallet * pallet = Pallets[i];
		if (pallet == nullptr) { continue; }
		pallet -> GraphicsCreate();
	}
}
void NewPolyHedra_PalletManager::GraphicsDelete()
{
	for (unsigned int i = 0; i < Pallets.Count(); i++)
	{
		NewPolyHedra_Pallet * pallet = Pallets[i];
		if (pallet == nullptr) { continue; }
		pallet -> GraphicsDelete();
	}
}



#include "NewPallet.hpp"

NewPolyHedra_Pallet * NewPallet(PolyHedra * polyhedra)
{
	if (polyhedra == nullptr) { return nullptr; }
	if (NewPolyHedra_PalletManager::Current != nullptr)
	{
		return NewPolyHedra_PalletManager::Current -> FindMakePallet(polyhedra);
	}
	return nullptr;
}
