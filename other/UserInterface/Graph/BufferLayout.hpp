#ifndef  UI_GRAPH_BUFFER_LAYOUT_HPP
# define UI_GRAPH_BUFFER_LAYOUT_HPP

# include "Graphics/Attribute/General/Layout.hpp"
# include "Graphics/Attribute/_Include.hpp"

namespace UI
{

namespace Graph
{

class BufferLayout : public ::Attribute::Layout
{
	public:
	// do Box with Uniform like with Text
	// do a Zoom / Offset for Graph
	// draw Grid Lines ?
	::Attribute::BoxF2		Box;
	::Attribute::VectorF2	Pos;
	::Attribute::ColorF4	Col;
	public:
	~BufferLayout();
	BufferLayout();
};

};

};

#endif