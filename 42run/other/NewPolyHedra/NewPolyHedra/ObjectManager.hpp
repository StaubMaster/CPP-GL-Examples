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
	Container::Binary<PalletObjectManager*>		PalletObjectManagers;
	public:
	unsigned int	PalletObjectManagersCount() const;

	private:
	virtual PalletObjectManager *	PalletObjectManagersNew() = 0;

	public:
	PalletObjectManager *	PalletObjectManagersFind(Pallet * pallet) const;
	private:
	PalletObjectManager *	PalletObjectManagersMake(Pallet * pallet);
	public:
	PalletObjectManager *	PalletObjectManagersFindMake(Pallet * pallet);

	public:
	PalletObjectManager *	PalletObjectManagersFind(PolyHedra * polyhedra) const;
	private:
	PalletObjectManager *	PalletObjectManagersMake(PolyHedra * polyhedra);
	public:
	PalletObjectManager *	PalletObjectManagersFindMake(PolyHedra * polyhedra);



	private:
	Container::Binary<PalletObjectData*>	PalletObjectDatas;
	public:
	unsigned int	PalletObjectDatasCount() const;

	public:
	virtual PalletObjectData *		PalletObjectDatasNew() = 0;
	PalletObjectData *				PalletObjectDatasNew(Pallet * pallet);
	PalletObjectData *				PalletObjectDatasNew(PolyHedra * polyhedra);

	public:
	void	PalletObjectDatasRemove();



	public:
	::Shader::Base	ShaderFull;
	::Shader::Base	ShaderWire;

	::Attribute::Layout *	BufferFullLayout = nullptr;
	::Attribute::Layout *	BufferWireLayout = nullptr;

	unsigned int	InstancesFullCount() const;
	unsigned int	InstancesWireCount() const;

	void	InstancesClear();
	void	InstancesMake();

	void	GraphicsCreate();
	void	GraphicsDelete();
	void	GraphicsDrawFull();
	void	GraphicsDrawWire();
};
};

#endif