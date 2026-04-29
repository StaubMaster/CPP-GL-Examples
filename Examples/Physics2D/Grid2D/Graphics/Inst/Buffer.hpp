#ifndef  GRID_2D_GRAPHICS_INST_BUFFER_HPP
# define GRID_2D_GRAPHICS_INST_BUFFER_HPP

# include "Graphics/Buffer/Array.hpp"
# include "Graphics/Attribute/Point2D.hpp"
# include "Graphics/Attribute/Base/Float1.hpp"

namespace Grid2DGraphics
{
namespace Inst
{
struct Buffer : public ::Buffer::Array
{
	public:
	::Attribute::Point2D	Pos;
	::Attribute::Float1		Size;
	public:
	~Buffer();
	Buffer(VertexArray & vertex_array);
};
};
};

#endif