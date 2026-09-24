#ifndef  NEW_POLYHEDRA_OBJECT_MANAGER_HPP
# define NEW_POLYHEDRA_OBJECT_MANAGER_HPP

# include "Generics/Container/Binary.hpp"
# include "Graphics/Shader/Base.hpp"
# include "Graphics/Attribute/General/Layout.hpp"
# include "Graphics/Buffer/Uniform.hpp"

class PolyHedra;

/* split ?
PalletObjectManagerManager
PalletObjectDataManager
*/

namespace NewPolyHedra
{
struct Pallet;
struct PalletObjectManager;
struct PalletObjectData;
struct ObjectData;

struct ObjectManager
{
	public:
	virtual ~ObjectManager();
	ObjectManager() = default;
	ObjectManager(const ObjectManager & other) = delete;
	ObjectManager & operator=(const ObjectManager & other) = delete;



	private:
	Container::Binary<PalletObjectManager*>		Managers;
	public:
	unsigned int	ManagersCount() const;

	private:
	virtual PalletObjectManager *	NewPalletObjectManager() = 0;

	public:
	PalletObjectManager *	FindPalletObjectManager(Pallet * pallet) const;
	private:
	PalletObjectManager *	MakePalletObjectManager(Pallet * pallet);
	public:
	PalletObjectManager *	FindMakePalletObjectManager(Pallet * pallet);

	public:
	PalletObjectManager *	FindPalletObjectManager(PolyHedra * polyhedra) const;
	private:
	PalletObjectManager *	MakePalletObjectManager(PolyHedra * polyhedra);
	public:
	PalletObjectManager *	FindMakePalletObjectManager(PolyHedra * polyhedra);

	// FindName



	private:
	Container::Binary<PalletObjectData*>	PalletObjectDatas;
	public:
	unsigned int	PalletObjectDatasCount() const;

	public:
	virtual PalletObjectData *		NewPalletObjectData() = 0;
	PalletObjectData *				NewPalletObjectData(Pallet * pallet);

	public:
	void	UpdatePalletObjectDatas(); // RemovePalletObjectDatas();



	public:
	::Shader::Base	ShaderFull;
	::Shader::Base	ShaderWire;

	::Attribute::Layout *	BufferFullLayout = nullptr;
	::Attribute::Layout *	BufferWireLayout = nullptr;

	unsigned int	InstanceFullCount() const;
	unsigned int	InstanceWireCount() const;

	void	InstancesClear();
	void	InstancesMake();

	void	GraphicsCreate();
	void	GraphicsDelete();
	void	GraphicsDrawFull();
	void	GraphicsDrawWire();
};
};

#endif