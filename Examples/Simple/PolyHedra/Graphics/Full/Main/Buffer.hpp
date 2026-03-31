#ifndef  POLYHEDRA_GRAPHICS_FULL_MAIN_BUFFER_HPP
# define POLYHEDRA_GRAPHICS_FULL_MAIN_BUFFER_HPP

# include "Graphics/Buffer/Attribute.hpp"
# include "Graphics/Attribute/Point3D.hpp"

namespace PolyHedraFull
{
namespace Main
{
class Buffer : public ::Buffer::Attribute
{
	public:
	::Attribute::Point3D	Position;
	::Attribute::Point3D	Normal;
	::Attribute::Point3D	Texture;

	public:
	Buffer(BufferArray::Base & buffer_array);
};
};
};

#endif