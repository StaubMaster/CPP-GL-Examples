#include "ObjectData.hpp"
#include "InstanceData.hpp"

#include "NewPolyHedra/Type/Manager.cpp"
#include "NewPolyHedra/Type/Logical/Data.cpp"
#include "NewPolyHedra/Type/Logical/DataManager.cpp"
#include "NewPolyHedra/Type/Display/Data.cpp"
#include "NewPolyHedra/Type/Display/DataManager.cpp"
#include "NewPolyHedra/Type/Object.cpp"

namespace NewPolyHedra
{
typedef Basic3D::ObjectData TypeData;
typedef Basic3D::InstanceData TypeInstanceData;
template struct DataManager					<TypeData>;
template struct TypeManager					<TypeData, TypeInstanceData>;
template struct TypeLogicalData				<TypeData>;
template struct TypeLogicalDataManager		<TypeData>;
template struct TypeDisplayData				<TypeData, TypeInstanceData>;
template struct DataDisplayDataManager		<TypeData>;
template struct TypeDisplayDataManager		<TypeData, TypeInstanceData>;
template struct Type_Object					<TypeData>;
};
