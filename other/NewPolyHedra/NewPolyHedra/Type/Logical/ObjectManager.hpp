#ifndef  NEW_POLYHEDRA_TYPE_LOGICAL_OBJECT_MANAGER_HPP
# define NEW_POLYHEDRA_TYPE_LOGICAL_OBJECT_MANAGER_HPP

# include "NewPolyHedra/Base/Logical/ObjectManager.hpp"

namespace NewPolyHedra
{
template<typename LogicalData> struct TypeLogicalObject;
template<typename LogicalData> struct TypeLogicalObjectManager : public BaseLogicalObjectManager
{
	private:
	static TypeLogicalObjectManager *	Current;
	public:
	static TypeLogicalObject<LogicalData> *		sNewType(Pallet * pallet);

	public:
	virtual ~TypeLogicalObjectManager();
	TypeLogicalObjectManager();
	TypeLogicalObjectManager(const TypeLogicalObjectManager & other) = delete;
	TypeLogicalObjectManager & operator=(const TypeLogicalObjectManager & other) = delete;

	public:
	BaseLogicalObject *					NewBase(Pallet * pallet) override;
	TypeLogicalObject<LogicalData> *	NewType(Pallet * pallet);
};
};

#endif