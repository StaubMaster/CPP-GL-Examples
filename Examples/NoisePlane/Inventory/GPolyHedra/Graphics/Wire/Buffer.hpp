#ifndef  POLYHEDRA_GRAPHICS_ELEM_BUFFER_HPP
# define POLYHEDRA_GRAPHICS_ELEM_BUFFER_HPP

# include "Graphics/Buffer/MainElemInst.hpp"
# include "PolyHedra/Graphics/Wire/Main/Buffer.hpp"
# include "PolyHedra/Graphics/Wire/Elem/Buffer.hpp"
# include "Instance/Basic3D/Buffer.hpp"

# include "OpenGLTypes.hpp"

namespace PolyHedraWire
{
class Buffer : public ::BufferArray::MainElemInst<
	PolyHedraWire::Main::Buffer,
	PolyHedraWire::Elem::Buffer,
	Instance::Basic3D::Buffer
>
{
	public:
	~Buffer();
	Buffer();
};
};

#endif