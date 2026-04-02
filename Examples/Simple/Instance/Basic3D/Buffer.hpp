#ifndef  INSTANCE_BASIC_3D_BUFFER_HPP
# define INSTANCE_BASIC_3D_BUFFER_HPP

# include "Graphics/Buffer/Attribute.hpp"
# include "Graphics/Attribute/Base/Float4x4.hpp"

namespace Instance
{
namespace Basic3D
{
class Buffer : public ::Buffer::Attribute
{
	public:
	::Attribute::Float4x4	Trans;
	::Attribute::Float4x4	Normal;
	public:
	~Buffer();
	Buffer(BufferArray::Base & buffer_array);
};
};
};

#endif