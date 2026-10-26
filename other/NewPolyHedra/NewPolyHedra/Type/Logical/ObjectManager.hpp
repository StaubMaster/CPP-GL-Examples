#ifndef  NEW_POLYHEDRA_TYPE_LOGICAL_OBJECT_MANAGER_HPP
# define NEW_POLYHEDRA_TYPE_LOGICAL_OBJECT_MANAGER_HPP

# include "NewPolyHedra/Base/Logical/ObjectManager.hpp"
# include "NewPolyHedra/Type/Logical/Object.hpp"

namespace NewPolyHedra
{
template<typename LogicalData> struct TypeLogicalObjectManager : public BaseLogicalObjectManager
{
	private:
	static TypeLogicalObjectManager *	Current;
	public:
	static TypeLogicalObject<LogicalData> *		sNew(Pallet & pallet);
	static TypeLogicalObject<LogicalData> *		sNew(Pallet * pallet);

	public:
	virtual ~TypeLogicalObjectManager();
	TypeLogicalObjectManager();
	TypeLogicalObjectManager(const TypeLogicalObjectManager & other) = delete;
	TypeLogicalObjectManager & operator=(const TypeLogicalObjectManager & other) = delete;

	private:
	Container::Binary<TypeLogicalObject<LogicalData> *>		Objects;

	public:
	unsigned int	Count() const override;

	public:
	TypeLogicalObject<LogicalData> &	New(Pallet & pallet) override;

	public:
	void	Clean() override;

	public:
	void	InstancesMake() override;
};
};

#endif