#ifndef  VOXEL_GRAPHICS_MAIN_BUFFER_HPP
# define VOXEL_GRAPHICS_MAIN_BUFFER_HPP

# include "Graphics/Buffer/Attribute.hpp"
# include "Graphics/Attribute/Point3D.hpp"
# include "Graphics/Attribute/ColorF4.hpp"

namespace VoxelGraphics
{
	struct MainBuffer : public ::Buffer::Attribute
	{
		::Attribute::Point3D	Pos;
		::Attribute::ColorF4	Col;
		~MainBuffer();
		MainBuffer(::BufferArray::Base & buffer_array);
	};
};

#endif