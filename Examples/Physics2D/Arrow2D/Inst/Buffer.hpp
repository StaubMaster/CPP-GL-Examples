#ifndef  ARROW_2D_INST_BUFFER_HPP
# define ARROW_2D_INST_BUFFER_HPP

# include "Graphics/Buffer/Array.hpp"
# include "Graphics/Attribute/VectorF2.hpp"
# include "Graphics/Attribute/ColorF4.hpp"
# include "Graphics/Attribute/General/Float1.hpp"

namespace Arrow2D
{
namespace Inst
{
class Buffer : public ::Buffer::Array
{
	public:
	::Attribute::VectorF2	Pos0;
	::Attribute::VectorF2	Pos1;
	::Attribute::Float1		Size;
	::Attribute::ColorF4	Col;
	public:
	Buffer(VertexArray & vertex_array);
};
};
};

#endif