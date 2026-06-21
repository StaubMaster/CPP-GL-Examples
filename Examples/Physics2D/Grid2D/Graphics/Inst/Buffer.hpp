#ifndef  GRID_2D_GRAPHICS_INST_BUFFER_HPP
# define GRID_2D_GRAPHICS_INST_BUFFER_HPP

# include "Graphics/Buffer/Array.hpp"
# include "Graphics/Attribute/VectorF2.hpp"
# include "Graphics/Attribute/General/Float1.hpp"

namespace Grid2DGraphics
{
namespace Inst
{
struct Buffer : public ::Buffer::Array
{
	public:
	::Attribute::VectorF2	Pos;
	::Attribute::Float1		Size;
	public:
	~Buffer();
	Buffer(VertexArray & vertex_array);
};
};
};

#endif