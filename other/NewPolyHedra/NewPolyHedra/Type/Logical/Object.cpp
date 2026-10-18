#include "NewPolyHedra/Type/Logical/Object.hpp"
#include "NewPolyHedra/Type/Logical/ObjectManager.hpp"



template<typename LogicalData> const void * NewPolyHedra::TypeLogicalObject<LogicalData>::DataVoid() const
{
	return &Data;
}



/*template<typename LogicalData> NewPolyHedra::TypeLogicalObject<LogicalData> * NewPolyHedra::TypeLogicalObject<LogicalData>::New(Pallet * pallet)
{
	return TypeLogicalObjectManager<LogicalData>::sNewType(pallet);
}*/
