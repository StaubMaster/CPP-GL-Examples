#ifndef  NEW_POLYHEDRA_BASE_LOGICAL_OBJECT_MANAGER_HPP
# define NEW_POLYHEDRA_BASE_LOGICAL_OBJECT_MANAGER_HPP

# include "Generics/Container/Binary.hpp"

namespace NewPolyHedra
{
struct Pallet;

struct BaseLogicalObject;
struct BaseLogicalObjectManager
{
	protected:
	Container::Binary<BaseLogicalObject*>		Datas;
	public:
	unsigned int	Count() const;

	public:
	virtual BaseLogicalObject *		NewBase(Pallet * pallet) = 0;

	public:
	void	Clean();

	public:
	void	InstancesMake();
};
};

#endif