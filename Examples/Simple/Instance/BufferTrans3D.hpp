#ifndef  INSTANCE_BUFFER_TRANS_3D_HPP
# define INSTANCE_BUFFER_TRANS_3D_HPP

# include "Graphics/Buffer/Attribute.hpp"
# include "Graphics/Attribute/Trans3D.hpp"
# include "Graphics/Attribute/Base/Float4x4.hpp"
# include "Graphics/Attribute/Base/Float3x3.hpp"

namespace Instance
{
class BufferTrans3D : public ::Buffer::Attribute
{
	public:
//	::Attribute::Trans3D	Data;
	::Attribute::Float4x4	Data;
	public:
	BufferTrans3D(BufferArray::Base & buffer_array);
};
};

#endif