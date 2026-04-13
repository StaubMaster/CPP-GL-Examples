#ifndef  VOXEL_GRAPHICS_INST_BUFFER_HPP
# define VOXEL_GRAPHICS_INST_BUFFER_HPP

# include "Graphics/Buffer/Attribute.hpp"
# include "Graphics/Attribute/Point3D.hpp"

namespace VoxelGraphics
{
	struct InstBuffer : public ::Buffer::Attribute
	{
		::Attribute::Point3D	Pos;
		~InstBuffer();
		InstBuffer(::BufferArray::Base & buffer_array);
	};
};


#endif