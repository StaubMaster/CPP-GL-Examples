#ifndef  INSTANCE_BASIC_3D_LAYOUT_HPP
# define INSTANCE_BASIC_3D_LAYOUT_HPP

# include "Graphics/Attribute/General/Layout.hpp"
# include "Graphics/Attribute/TypeDefs/Matrix4x4.hpp"

namespace Instance
{
namespace Basic3D
{
class Layout : public ::Attribute::Layout
{
	public:
	::Attribute::Matrix4x4	Trans;
	::Attribute::Matrix4x4	Normal;
	public:
	~Layout();
	Layout();
	Layout(const Layout & other);
};
};
};

#endif