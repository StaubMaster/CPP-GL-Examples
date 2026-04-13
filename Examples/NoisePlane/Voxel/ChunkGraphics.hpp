#ifndef  CHUNK_GRAPHICS_HPP
# define CHUNK_GRAPHICS_HPP

# include "ValueType/Point3D.hpp"
# include "ValueType/ColorF4.hpp"

# include "Graphics/Buffer/MainInst.hpp"
# include "Graphics/Buffer/Attribute.hpp"
# include "Graphics/Attribute/Point3D.hpp"
# include "Graphics/Attribute/ColorF4.hpp"

# include "Graphics/Shader/Base.hpp"
# include "Graphics/Uniform/_Include.hpp"

namespace ChunkGraphics
{
	struct MainData
	{
		Point3D		Pos;
		ColorF4		Col;
	};
	struct InstData
	{
		Point3D		Pos;
	};
	struct VoxelData
	{
		MainData	Data[8];
	};
	struct MainBuffer : public ::Buffer::Attribute
	{
		::Attribute::Point3D	Pos;
		::Attribute::ColorF4	Col;
		~MainBuffer();
		MainBuffer(::BufferArray::Base & buffer_array);
	};
	struct InstBuffer : public ::Buffer::Attribute
	{
		::Attribute::Point3D	Pos;
		~InstBuffer();
		InstBuffer(::BufferArray::Base & buffer_array);
	};
	struct Buffer : public ::BufferArray::MainInst<MainBuffer, InstBuffer>
	{
		~Buffer();
		Buffer();
	};
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