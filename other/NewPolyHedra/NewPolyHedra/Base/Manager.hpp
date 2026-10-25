#ifndef  NEW_POLYHEDRA_BASE_MANAGER_HPP
# define NEW_POLYHEDRA_BASE_MANAGER_HPP

namespace NewPolyHedra
{
struct Pallet;

struct BaseLogicalObject;
struct BaseLogicalObjectManager;
struct BaseDisplayObject;
struct BaseDisplayObjectManager;
struct BaseManager
{
	public:
	virtual			BaseLogicalObjectManager &	LogicalManager()					= 0;
	virtual const	BaseLogicalObjectManager &	LogicalManager() const				= 0;

	public:
	virtual			BaseDisplayObjectManager &	DisplayManager()							= 0;
	virtual const	BaseDisplayObjectManager &	DisplayManager() const						= 0;
	virtual			BaseDisplayObject *			FindDisplayObject(const Pallet & pallet)	= 0;
	virtual			BaseDisplayObject &			TakeDisplayObject(      Pallet & pallet)	= 0;

	public:
	virtual ~BaseManager() = default;
	BaseManager() = default;
	BaseManager(const BaseManager & other) = delete;
	BaseManager & operator=(const BaseManager & other) = delete;

	public:
	void	CleanObjects();

	public:
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