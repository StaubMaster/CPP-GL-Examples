#include "NewPolyHedra/Pallet/Manager.hpp"
#include "NewPolyHedra/Pallet/.hpp"

#include "Graphics/VertexArray/Base.hpp"

#include "Generics/Loop.hpp"



NewPolyHedra::PalletManager::~PalletManager()
{
	if (IsCurrent()) { ClearCurrent(); }
	Container::Loop::Delete(Pallets);
}
NewPolyHedra::PalletManager::PalletManager()
	: Pallets()
//	, BufferFullLayout()
//	, BufferWireLayout()
{
	if (!CheckCurrent()) { MakeCurrent(); }
}



NewPolyHedra::Pallet * NewPolyHedra::PalletManager::Find(const PolyHedra & polyhedra) const
{
	return Container::Loop::Find(Pallets, &NewPolyHedra::Pallet::Equals, &polyhedra);
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

/*NewPolyHedra::Pallet * NewPolyHedra::PalletManager::Find(const PolyHedra * polyhedra) const
{
	if (polyhedra == nullptr) { return nullptr; }
	return Find(*polyhedra);
}*/
/*NewPolyHedra::Pallet * NewPolyHedra::PalletManager::Make(PolyHedra * polyhedra)
{
	if (polyhedra == nullptr) { return nullptr; }
	return &Make(*polyhedra);
}*/
/*NewPolyHedra::Pallet * NewPolyHedra::PalletManager::Take(PolyHedra * polyhedra)
{
	if (polyhedra == nullptr) { return nullptr; }
	return &Take(*polyhedra);
}*/



void NewPolyHedra::PalletManager::GraphicsCreate()
{
	Container::Loop::Invoke(Pallets, &NewPolyHedra::Pallet::GraphicsCreate);
}
void NewPolyHedra::PalletManager::GraphicsDelete()
{
	Container::Loop::Invoke(Pallets, &NewPolyHedra::Pallet::GraphicsDelete);
}





NewPolyHedra::PalletManager * NewPolyHedra::PalletManager::Current_ = nullptr;
NewPolyHedra::PalletManager & NewPolyHedra::PalletManager::Current() { return *Current_; }
bool NewPolyHedra::PalletManager::CheckCurrent() { return (Current_ != nullptr); }
void NewPolyHedra::PalletManager::ClearCurrent() { Current_ = nullptr; }
bool NewPolyHedra::PalletManager::IsCurrent() const { return (Current_ == this); }
void NewPolyHedra::PalletManager::MakeCurrent() { Current_ = this; }



NewPolyHedra::Pallet * NewPolyHedra::PalletManager::sFind(PolyHedra & polyhedra)
{
	if (!CheckCurrent()) { return nullptr; }
	return (Current().Find(polyhedra));
}
NewPolyHedra::Pallet * NewPolyHedra::PalletManager::sTake(PolyHedra & polyhedra)
{
	if (!CheckCurrent()) { return nullptr; }
	return &(Current().Take(polyhedra));
}
