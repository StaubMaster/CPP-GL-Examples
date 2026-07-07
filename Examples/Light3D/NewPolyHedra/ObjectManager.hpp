#ifndef  NEW_POLYHEDRA_OBJECT_MANAGER_HPP
# define NEW_POLYHEDRA_OBJECT_MANAGER_HPP

# include "Miscellaneous/Container/Binary.hpp"
# include "Graphics/Shader/Base.hpp"
# include "Graphics/Attribute/General/Layout.hpp"
# include "Graphics/Buffer/Uniform.hpp"

class PolyHedra;
struct NewPolyHedra_Pallet;
struct NewPolyHedra_PalletObjectManager;
struct NewPolyHedra_PalletObjectData;
struct NewPolyHedra_ObjectData;

struct NewPolyHedra_ObjectManager
{
	Container::Binary<NewPolyHedra_PalletObjectManager*>	Managers;

	virtual NewPolyHedra_PalletObjectManager *	NewPalletObjectManager() = 0;

	NewPolyHedra_PalletObjectManager *	FindPalletObjectManager(NewPolyHedra_Pallet * pallet) const;
	NewPolyHedra_PalletObjectManager *	MakePalletObjectManager(NewPolyHedra_Pallet * pallet);
	NewPolyHedra_PalletObjectManager *	FindMakePalletObjectManager(NewPolyHedra_Pallet * pallet);

	NewPolyHedra_PalletObjectManager *	FindPalletObjectManager(PolyHedra * polyhedra) const;
	NewPolyHedra_PalletObjectManager *	MakePalletObjectManager(PolyHedra * polyhedra);
	NewPolyHedra_PalletObjectManager *	FindMakePalletObjectManager(PolyHedra * polyhedra);



	Container::Binary<NewPolyHedra_PalletObjectData*>	PalletObjectDatas;

	virtual NewPolyHedra_PalletObjectData *		NewPalletObjectData() = 0;
	NewPolyHedra_PalletObjectData *				NewPalletObjectData(NewPolyHedra_Pallet * pallet);

	void	UpdatePalletObjectDatas();



	::Shader::Base	ShaderFull;
	::Shader::Base	ShaderWire;

	::Attribute::Layout *	BufferFullLayout = nullptr;
	::Attribute::Layout *	BufferWireLayout = nullptr;
	::Buffer::Uniform *		BufferUniform = nullptr;

	void	InstancesClear();
	void	InstancesMake();

	void	GraphicsCreate();
	void	GraphicsDelete();
	void	GraphicsDrawFull();
	void	GraphicsDrawWire();
};

#endif