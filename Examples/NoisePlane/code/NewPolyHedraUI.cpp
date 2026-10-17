#include "NewPolyHedraUI.hpp"



NewPolyHedra::UserInterface::InstanceData::InstanceData(const ObjectData & data)
	: Size(data.Size)
	, Pos(data.Pos)
	, Rot(Matrix3x3::Rotation(data.Rot))
	, Scale(data.Scale)
{ }

NewPolyHedra::UserInterface::BufferLayout::~BufferLayout()
{ }
NewPolyHedra::UserInterface::BufferLayout::BufferLayout()
	: ::Attribute::Layout(1, sizeof(InstanceData))
	, Size(*this)
	, Pos(*this)
	, Rot(*this)
	, Scale(*this)
{ }



#include "NewPolyHedra/Type/Manager.cpp"
#include "NewPolyHedra/Type/Logical/Data.cpp"
#include "NewPolyHedra/Type/Logical/DataManager.cpp"
#include "NewPolyHedra/Type/Display/Data.cpp"
#include "NewPolyHedra/Type/Display/DataManager.cpp"
#include "NewPolyHedra/Type/Object.cpp"

namespace NewPolyHedra
{
typedef UserInterface::ObjectData TypeData;
typedef UserInterface::InstanceData TypeInstanceData;
template struct DataManager					<TypeData>;
template struct TypeManager					<TypeData, TypeInstanceData>;
template struct TypeLogicalData				<TypeData>;
template struct TypeLogicalDataManager		<TypeData>;
template struct TypeDisplayData				<TypeData, TypeInstanceData>;
template struct DataDisplayDataManager		<TypeData>;
template struct TypeDisplayDataManager		<TypeData, TypeInstanceData>;
template struct Type_Object					<TypeData>;
};
