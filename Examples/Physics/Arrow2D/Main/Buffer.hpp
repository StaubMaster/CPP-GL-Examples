#ifndef  ARROW_2D_MAIN_BUFFER_HPP
# define ARROW_2D_MAIN_BUFFER_HPP

# include "Graphics/Buffer/Attribute.hpp"
# include "Graphics/Attribute/Point2D.hpp"
# include "Graphics/Attribute/Point3D.hpp"

namespace BufferArray { class Base; };

namespace Arrow2D
{
namespace Main
{
class Buffer : public ::Buffer::Attribute
{
	private:
	::Attribute::Point2D	Pos;
	::Attribute::Point3D	Tex;
	public:
	Buffer(
		BufferArray::Base & buffer_array,
		unsigned int indexPos,
		unsigned int indexTex
	);
};
};
};

#endif