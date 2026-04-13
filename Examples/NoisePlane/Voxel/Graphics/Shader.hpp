#ifndef  VOXEL_GRAPHICS_SHADER_HPP
# define VOXEL_GRAPHICS_SHADER_HPP

# include "Graphics/Shader/Base.hpp"
# include "Graphics/Uniform/_Include.hpp"

namespace VoxelGraphics
{
	struct Shader : public ::Shader::Base
	{
		::Uniform::DisplaySize		DisplaySize;
		::Uniform::Matrix4x4		View;
		::Uniform::Depth			Depth;
		::Uniform::Angle			FOV;
		~Shader();
		Shader();
	};
};

#endif