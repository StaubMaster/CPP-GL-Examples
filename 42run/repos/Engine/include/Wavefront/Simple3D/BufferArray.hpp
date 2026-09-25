#ifndef  WAVEFRONT_OBJ_SIMPLE3D_BUFFER_ARRAY_HPP
# define WAVEFRONT_OBJ_SIMPLE3D_BUFFER_ARRAY_HPP

# include "Graphics/Buffer/VertexArray.hpp"
# include "Wavefront/Main/Buffer.hpp"
# include "InstanceData/Simple3D/Buffer.hpp"

namespace Wavefront
{
namespace Simple3D
{
class BufferArray : public ::VertexArray
{
	public:
	Main::Buffer			Main;
	::Simple3D::Buffer		Inst;
	GL::DrawMode			DrawMode;

	public:
	~BufferArray();
	BufferArray();

	BufferArray(const BufferArray & other) = delete;
	BufferArray & operator=(const BufferArray & other) = delete;

	void Draw();
};
};
};

#endif