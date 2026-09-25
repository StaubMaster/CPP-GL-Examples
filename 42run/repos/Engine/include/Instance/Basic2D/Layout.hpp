#ifndef  INSTANCE_BASIC_2D_LAYOUT_HPP
# define INSTANCE_BASIC_2D_LAYOUT_HPP

# include "Graphics/Attribute/General/Layout.hpp"
# include "Graphics/Attribute/TypeDefs/Matrix3x3.hpp"

namespace Instance
{
namespace Basic2D
{
class Layout : public ::Attribute::Layout
{
	public:
	::Attribute::Matrix3x3	Trans;
	public:
	~Layout();
	Layout();
	Layout(const Layout & other);
};
};
};

#endif