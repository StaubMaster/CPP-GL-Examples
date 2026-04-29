#ifndef  VOXEL_GRAPHICS_INST_BUFFER_HPP
# define VOXEL_GRAPHICS_INST_BUFFER_HPP

# include "Graphics/Buffer/Array.hpp"
# include "Graphics/Attribute/Point3D.hpp"

namespace VoxelGraphics
{
	struct InstBuffer : public ::Buffer::Array
	{
		::Attribute::Point3D	Pos;
		~InstBuffer();
		InstBuffer(::VertexArray & vertex_array);
	};
};


#endif