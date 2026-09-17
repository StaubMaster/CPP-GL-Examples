#ifndef  NEW_POLYHEDRA_TEST_TYPE_TRANS_SCALE_COLOR_3D_LAYOUT_HPP
# define NEW_POLYHEDRA_TEST_TYPE_TRANS_SCALE_COLOR_3D_LAYOUT_HPP

# include "Graphics/Attribute/General/Layout.hpp"
# include "Graphics/Attribute/_Include.hpp"

namespace TransScaleColor3D
{
struct BufferLayout : public ::Attribute::Layout
{
	public:
	::Attribute::Matrix4x4	Trans;
	::Attribute::Matrix4x4	Normal;
	::Attribute::Float		Scale;
	::Attribute::ColorF4	Color;
	public:
	~BufferLayout();
	BufferLayout();
};
};

#endif