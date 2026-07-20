#ifndef  NEW_POLYHEDRA_UI_HPP
# define NEW_POLYHEDRA_UI_HPP

# include "ValueType/Vector/F2.hpp"
# include "ValueType/EulerAngle3D.hpp"
# include "ValueType/Matrix/3x3.hpp"

# include "Graphics/Attribute/General/Layout.hpp"
# include "Graphics/Attribute/TypeDefs/VectorF2.hpp"
# include "Graphics/Attribute/TypeDefs/Matrix3x3.hpp"

# include "NewPolyHedra/Type/Object.hpp"
# include "NewPolyHedra/Type/PalletObjectData.hpp"
# include "NewPolyHedra/Type/ObjectManager.hpp"

namespace NewPolyHedra
{
namespace UserInterface
{
struct ObjectData
{
	VectorF2		Size;
	VectorF2		Pos;
	EulerAngle3D	Rot;
};
struct InstanceData
{
	VectorF2	Size;
	VectorF2	Pos;
	Matrix3x3	Rot;
	~InstanceData() = default;
	InstanceData() = default;
	InstanceData(const ObjectData & data);
};
class BufferLayout : public ::Attribute::Layout
{
	public:
	::Attribute::VectorF2	Size;
	::Attribute::VectorF2	Pos;
	::Attribute::Matrix3x3	Rot;
	public:
	~BufferLayout();
	BufferLayout();
};
typedef Type_PalletObjectData<ObjectData> PalletObjectData;
typedef Type_Object<ObjectData> Object;
typedef Type_ObjectManager<ObjectData, InstanceData> ObjectManager;
};
};

#endif