#ifndef  NEW_POLYHEDRA_BASE_LOGICAL_OBJECT_MANAGER_HPP
# define NEW_POLYHEDRA_BASE_LOGICAL_OBJECT_MANAGER_HPP

# include "Generics/Container/Binary.hpp"

namespace NewPolyHedra
{
struct Pallet;

struct BaseLogicalObject;
struct BaseLogicalObjectManager
{
//	protected:
//	Container::Binary<BaseLogicalObject*>		Datas;
	public:
	virtual unsigned int	Count() const = 0;

	public:
	virtual BaseLogicalObject &		New(Pallet & pallet) = 0;

	public:
	virtual void	Clean() = 0;

	public:
	virtual void	InstancesMake() = 0;
};
};

#endif