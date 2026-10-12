#ifndef  NEW_POLYHEDRA_BASE_MANAGER_HPP
# define NEW_POLYHEDRA_BASE_MANAGER_HPP

namespace NewPolyHedra
{
struct BaseLogicalDataManager;
struct BaseDisplayDataManager;
struct BaseManager
{
	public:
	virtual ~BaseManager() = default;
	BaseManager() = default;
	BaseManager(const BaseManager & other) = delete;
	BaseManager & operator=(const BaseManager & other) = delete;

	public:
	virtual			BaseLogicalDataManager &	LogicalBase()			= 0;
	virtual const	BaseLogicalDataManager &	LogicalBase() const		= 0;
	virtual			BaseDisplayDataManager &	DisplayBase()			= 0;
	virtual const	BaseDisplayDataManager &	DisplayBase() const		= 0;

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