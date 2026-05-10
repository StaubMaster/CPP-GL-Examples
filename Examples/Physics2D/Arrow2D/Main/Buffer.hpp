#ifndef  ARROW_2D_MAIN_BUFFER_HPP
# define ARROW_2D_MAIN_BUFFER_HPP

# include "Graphics/Buffer/Array.hpp"
# include "Graphics/Attribute/VectorF2.hpp"
# include "Graphics/Attribute/VectorF3.hpp"

namespace BufferArray { class Base; };

namespace Arrow2D
{
namespace Main
{
class Buffer : public ::Buffer::Array
{
	public:
	::Attribute::VectorF2	Pos;
	::Attribute::VectorF3	Tex;
	public:
	Buffer(VertexArray & vertex_array);
};
};
};

#endif