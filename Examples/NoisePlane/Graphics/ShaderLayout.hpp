#ifndef  VOXEL_GRAPHICS_SHADER_HPP
# define VOXEL_GRAPHICS_SHADER_HPP

# include "Graphics/Shader/Base.hpp"
# include "Graphics/Uniform/General/Layout.hpp"
# include "Graphics/Uniform/_Include.hpp"

namespace VoxelGraphics
{
	struct ShaderLayout : public Uniform::Layout
	{
		::Uniform::DisplaySize		DisplaySize;
		::Uniform::Matrix4x4		View;
		::Uniform::Depth			Depth;
		::Uniform::Angle			FOV;

		::Uniform::LightBase		LightAmbient;
		::Uniform::LightSolar		LightSolar;
		::Uniform::LightSpot		LightSpot;
		::Uniform::UInt				LightSpotCount;

		~ShaderLayout();
		ShaderLayout();
	};
};

#endif