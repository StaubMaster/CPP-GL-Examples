#ifndef  NEW_POLYHEDRA_USER_INTERFACE_LAYOUT_HPP
# define NEW_POLYHEDRA_USER_INTERFACE_LAYOUT_HPP

# include "Graphics/Attribute/General/Layout.hpp"
# include "Graphics/Attribute/TypeDefs/VectorF2.hpp"
# include "Graphics/Attribute/TypeDefs/Matrix3x3.hpp"
# include "Graphics/Attribute/TypeDefs/Float.hpp"

namespace NewPolyHedra
{
namespace UserInterface
{
class BufferLayout : public ::Attribute::Layout
{
	public:
	::Attribute::VectorF2	Size;
	::Attribute::VectorF2	Pos;
	::Attribute::Matrix3x3	Rot;
	::Attribute::Float		Scale;
	public:
	BufferLayout();
};
};
};

#endif