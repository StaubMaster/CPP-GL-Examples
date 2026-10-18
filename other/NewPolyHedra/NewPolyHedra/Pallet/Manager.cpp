#include "NewPolyHedra/Pallet/Manager.hpp"
#include "NewPolyHedra/Pallet/.hpp"

#include "Graphics/VertexArray/Base.hpp"

#include "Generics/Loop.hpp"



NewPolyHedra::PalletManager * NewPolyHedra::PalletManager::Current = nullptr;

NewPolyHedra::Pallet * NewPolyHedra::PalletManager::sFind(PolyHedra * polyhedra)
{
	if (Current == nullptr) { return nullptr; }
	return Current -> Find(polyhedra);
}
NewPolyHedra::Pallet * NewPolyHedra::PalletManager::sTake(PolyHedra * polyhedra)
{
	if (Current == nullptr) { return nullptr; }
	return Current -> Take(polyhedra);
}

NewPolyHedra::PalletManager::~PalletManager()
{
	Current = nullptr;
	Container::Loop::Delete(Pallets);
}
NewPolyHedra::PalletManager::PalletManager()
	: Pallets()
//	, BufferFullLayout()
//	, BufferWireLayout()
{
	Current = this;
}



NewPolyHedra::Pallet * NewPolyHedra::PalletManager::Find(const PolyHedra & polyhedra) const
{
	return Container::Loop::Find(Pallets, NewPolyHedra::Pallet::Equals, &polyhedra);
}
NewPolyHedra::Pallet & NewPolyHedra::PalletManager::Make(PolyHedra & polyhedra)
{
	NewPolyHedra::Pallet * pallet = new NewPolyHedra::Pallet(&polyhedra);
//	pallet -> BufferFull.AssignLayout(BufferFullLayout);
//	pallet -> BufferWire.AssignLayout(BufferWireLayout);
	pallet -> GraphicsCreate();
	pallet -> GraphicsPut();
	Pallets.Insert(pallet);
	return *pallet;
}
NewPolyHedra::Pallet & NewPolyHedra::PalletManager::Take(PolyHedra & polyhedra)
{
	NewPolyHedra::Pallet * pallet = Find(polyhedra);
	if (pallet != nullptr)
	{
		return *pallet;
	}
	return Make(polyhedra);
}

NewPolyHedra::Pallet * NewPolyHedra::PalletManager::Find(const PolyHedra * polyhedra) const
{
	if (polyhedra == nullptr) { return nullptr; }
	return Find(*polyhedra);
}
NewPolyHedra::Pallet * NewPolyHedra::PalletManager::Make(PolyHedra * polyhedra)
{
	if (polyhedra == nullptr) { return nullptr; }
	return &Make(*polyhedra);
}
NewPolyHedra::Pallet * NewPolyHedra::PalletManager::Take(PolyHedra * polyhedra)
{
	if (polyhedra == nullptr) { return nullptr; }
	return &Take(*polyhedra);
}



void NewPolyHedra::PalletManager::GraphicsCreate()
{
	Container::Loop::Invoke(Pallets, NewPolyHedra::Pallet::GraphicsCreate);
}
void NewPolyHedra::PalletManager::GraphicsDelete()
{
	Container::Loop::Invoke(Pallets, NewPolyHedra::Pallet::GraphicsDelete);
}
