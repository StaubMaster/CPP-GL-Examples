#ifndef  NEW_POLYHEDRA_OBJECT_MANAGER_HPP
# define NEW_POLYHEDRA_OBJECT_MANAGER_HPP

# include "Generics/Container/Binary.hpp"
# include "Graphics/Shader/Base.hpp"
# include "Graphics/Attribute/General/Layout.hpp"
# include "Graphics/Buffer/Uniform.hpp"

class PolyHedra;

namespace NewPolyHedra
{
struct Pallet;
struct PalletObjectManager;
struct PalletObjectData;
struct ObjectData;

struct ObjectManager
{
	~ObjectManager() = default;
	ObjectManager() = default;
	ObjectManager(const ObjectManager & other) = delete;
	ObjectManager & operator=(const ObjectManager & other) = delete;


	Container::Binary<PalletObjectManager*>	Managers;

	virtual PalletObjectManager *	NewPalletObjectManager() = 0;

	PalletObjectManager *	FindPalletObjectManager(Pallet * pallet) const;
	PalletObjectManager *	MakePalletObjectManager(Pallet * pallet);
	PalletObjectManager *	FindMakePalletObjectManager(Pallet * pallet);

	PalletObjectManager *	FindPalletObjectManager(PolyHedra * polyhedra) const;
	PalletObjectManager *	MakePalletObjectManager(PolyHedra * polyhedra);
	PalletObjectManager *	FindMakePalletObjectManager(PolyHedra * polyhedra);



	Container::Binary<PalletObjectData*>	PalletObjectDatas;

	virtual PalletObjectData *		NewPalletObjectData() = 0;
	PalletObjectData *				NewPalletObjectData(Pallet * pallet);

	void	UpdatePalletObjectDatas(); // RemovePalletObjectDatas();



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
};

#endif