#include "NewPolyHedra/Type/Logical/Data.hpp"
#include "NewPolyHedra/Type/Logical/DataManager.hpp"



template<typename TypeData> const void * NewPolyHedra::TypeLogicalData<TypeData>::DataVoid() const
{
	return &Data;
}



template<typename TypeData> NewPolyHedra::TypeLogicalData<TypeData> * NewPolyHedra::TypeLogicalData<TypeData>::New(Pallet * pallet)
{
	//if (TypeLogicalDataManager<TypeData>::Current == nullptr) { return nullptr; }
	//return TypeLogicalDataManager<TypeData>::Current -> NewType(pallet);
	return TypeLogicalDataManager<TypeData>::sNewType(pallet);
}
/*template<typename TypeData> NewPolyHedra::TypeLogicalData<TypeData> * NewPolyHedra::TypeLogicalData<TypeData>::New(PolyHedra * polyhedra)
{
	//if (TypeLogicalDataManager<TypeData>::Current == nullptr) { return nullptr; }
	//return TypeLogicalDataManager<TypeData>::Current -> NewType(polyhedra);
	return TypeLogicalDataManager<TypeData>::sNewType(polyhedra);
}*/
