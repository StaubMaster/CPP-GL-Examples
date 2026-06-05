#ifndef  UI_CONTROL_BUFFER_LAYOUT_HPP
# define UI_CONTROL_BUFFER_LAYOUT_HPP

# include "Graphics/Attribute/Layout.hpp"
# include "Graphics/Attribute/_Include.hpp"

namespace UI
{

namespace Control
{

namespace Main
{
class BufferLayout : public ::Attribute::Layout
{
	public:
	::Attribute::VectorF2	Pos;
	public:
	~BufferLayout();
	BufferLayout();
};
};

namespace Inst
{
class BufferLayout : public ::Attribute::Layout
{
	public:
	::Attribute::BoxF2		Box;
	::Attribute::Float		Layer;
	::Attribute::ColorF4	Col;
	public:
	~BufferLayout();
	BufferLayout();
};
};

};

};

#endif