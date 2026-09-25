#ifndef  NEW_POLYHEDRA_DATA_TYPE_BASIC_3D_LAYOUT_HPP
# define NEW_POLYHEDRA_DATA_TYPE_BASIC_3D_LAYOUT_HPP

# include "Graphics/Attribute/General/Layout.hpp"
# include "Graphics/Attribute/TypeDefs/Matrix4x4.hpp"

namespace NewPolyHedra
{
namespace Basic3D
{
class BufferLayout : public ::Attribute::Layout
{
	public:
	::Attribute::Matrix4x4	Trans;
	::Attribute::Matrix4x4	Normal;
	public:
	~BufferLayout();
	BufferLayout();
};
};
};

#endif