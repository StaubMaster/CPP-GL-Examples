#ifndef  NEW_POLYHEDRA_DATA_TYPE_TRANS_SCALE_COLOR_3D_LAYOUT_HPP
# define NEW_POLYHEDRA_DATA_TYPE_TRANS_SCALE_COLOR_3D_LAYOUT_HPP

# include "Graphics/Attribute/General/Layout.hpp"
# include "Graphics/Attribute/TypeDefs/Matrix4x4.hpp"
# include "Graphics/Attribute/TypeDefs/ColorF4.hpp"

namespace TransScaleColor3D
{
struct BufferLayout : public ::Attribute::Layout
{
	public:
	::Attribute::Matrix4x4	Trans;
	::Attribute::ColorF4	Color;
	public:
	BufferLayout();
};
};

#endif