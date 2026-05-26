#ifndef  VOXEL_GRAPHICS_SHADER_HPP
# define VOXEL_GRAPHICS_SHADER_HPP

# include "Graphics/Shader/Base.hpp"
# include "Graphics/Uniform/Layout.hpp"
# include "Graphics/Uniform/_Include.hpp"

namespace VoxelGraphics
{
	struct Shader : public ::Shader::Base
	{
		~Shader();
		Shader();
	};
	struct Layout : public Uniform::Layout
	{
		::Uniform::DisplaySize		DisplaySize;
		::Uniform::Matrix4x4		View;
		::Uniform::Depth			Depth;
		::Uniform::Angle			FOV;
		~Layout();
		Layout();
	};
};

#endif