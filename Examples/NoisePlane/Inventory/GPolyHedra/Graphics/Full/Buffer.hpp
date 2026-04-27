#ifndef  G_POLYHEDRA_GRAPHICS_FULL_BUFFER_HPP
# define G_POLYHEDRA_GRAPHICS_FULL_BUFFER_HPP

# include "Graphics/Buffer/MainInst.hpp"
# include "GPolyHedra/Graphics/Full/Main/Buffer.hpp"
# include "Instance/Basic3D/Buffer.hpp"

# include "OpenGLTypes.hpp"

namespace GPolyHedraFull
{
class Buffer : public ::BufferArray::MainInst<
	GPolyHedraFull::Main::Buffer,
	Instance::Basic3D::Buffer
>
{
	public:
	~Buffer();
	Buffer();
};
};

#endif