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



#include "NewPolyHedra/Type/PalletObjectData.cpp"
#include "NewPolyHedra/Type/Object.cpp"

namespace NewPolyHedra
{
template struct Type_PalletObjectData<UserInterface::ObjectData>;
template struct Type_Object<UserInterface::ObjectData>;
};


