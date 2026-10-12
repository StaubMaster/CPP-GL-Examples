#ifndef  NEW_POLYHEDRA_BASE_LOGICAL_DATA_MANAGER_HPP
# define NEW_POLYHEDRA_BASE_LOGICAL_DATA_MANAGER_HPP

# include "Generics/Container/Binary.hpp"

namespace NewPolyHedra
{
struct Pallet;

struct BaseLogicalData;
struct BaseLogicalDataManager
{
	protected:
	Container::Binary<BaseLogicalData*>		Datas;
	public:
	unsigned int	Count() const;

	public:
	virtual BaseLogicalData * NewBase(Pallet * pallet) = 0;

	public:
	void	Clean();

	public:
	void	InstancesMake();
};
};

#endif