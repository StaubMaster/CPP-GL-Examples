#ifndef  VOXEL_GRAPHICS_INST_BUFFER_HPP
# define VOXEL_GRAPHICS_INST_BUFFER_HPP

# include "Graphics/Buffer/Array.hpp"
# include "Graphics/Attribute/General/Layout.hpp"
# include "Graphics/Attribute/_Include.hpp"

namespace VoxelGraphics
{
	struct InstLayout : public ::Attribute::Layout
	{
		::Attribute::VectorF3	Pos;
		~InstLayout();
		InstLayout();
	};
};


#endif