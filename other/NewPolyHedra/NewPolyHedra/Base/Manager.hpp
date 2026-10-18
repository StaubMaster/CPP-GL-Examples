#ifndef  NEW_POLYHEDRA_BASE_MANAGER_HPP
# define NEW_POLYHEDRA_BASE_MANAGER_HPP

namespace NewPolyHedra
{
struct BaseLogicalObjectManager;
struct BaseDisplayObjectManager;
struct BaseManager
{
	public:
	virtual ~BaseManager() = default;
	BaseManager() = default;
	BaseManager(const BaseManager & other) = delete;
	BaseManager & operator=(const BaseManager & other) = delete;

	public:
	virtual			BaseLogicalObjectManager &		LogicalBase()			= 0;
	virtual const	BaseLogicalObjectManager &		LogicalBase() const		= 0;
	virtual			BaseDisplayObjectManager &		DisplayBase()			= 0;
	virtual const	BaseDisplayObjectManager &		DisplayBase() const		= 0;

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