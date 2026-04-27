#ifndef  POLYHEDRA_GRAPHICS_WIRE_MAIN_BUFFER_HPP
# define POLYHEDRA_GRAPHICS_WIRE_MAIN_BUFFER_HPP

# include "Graphics/Buffer/Attribute.hpp"
# include "Graphics/Attribute/Point3D.hpp"
# include "Graphics/Attribute/ColorF4.hpp"

namespace PolyHedraWire
{
namespace Main
{
class Buffer : public ::Buffer::Attribute
{
	public:
	::Attribute::Point3D	Pos;
	::Attribute::ColorF4	Col;
	public:
	~Buffer();
	Buffer(BufferArray::Base & buffer_array);
};
};
};

#endif