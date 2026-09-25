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



#include "NewPolyHedra/Type/ObjectManager.cpp"
#include "NewPolyHedra/Type/PalletObjectManager.cpp"
#include "NewPolyHedra/Type/PalletObjectData.cpp"
#include "NewPolyHedra/Type/Object.cpp"

namespace NewPolyHedra
{
typedef UserInterface::ObjectData TypeData;
typedef UserInterface::InstanceData TypeInstanceData;
template struct Type_Data_ObjectManager<TypeData>;
template struct Type_ObjectManager<TypeData, TypeInstanceData>;
template struct Type_PalletObjectManager<TypeData, TypeInstanceData>;
template struct Type_PalletObjectData<TypeData>;
template struct Type_Object<TypeData>;
};


