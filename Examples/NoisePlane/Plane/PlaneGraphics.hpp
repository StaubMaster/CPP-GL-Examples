#ifndef  PLANE_GRAPHICS_HPP
# define PLANE_GRAPHICS_HPP

# include "ValueType/VectorF3.hpp"
# include "ValueType/ColorF4.hpp"

# include "Graphics/Buffer/MainInst.hpp"
# include "Graphics/Buffer/Array.hpp"
# include "Graphics/Attribute/VectorF3.hpp"
# include "Graphics/Attribute/ColorF4.hpp"

# include "Graphics/Shader/Base.hpp"
# include "Graphics/Uniform/_Include.hpp"

namespace PlaneGraphics
{
	struct MainData
	{
		VectorF3		Pos;
		ColorF4		Col;
	};
	struct InstData
	{
		VectorF3		Pos;
	};
	struct MainBuffer : public ::Buffer::Array
	{
		::Attribute::VectorF3	Pos;
		::Attribute::ColorF4	Col;
		~MainBuffer();
		MainBuffer(::VertexArray & vertex_array);
	};
	struct InstBuffer : public ::Buffer::Array
	{
		::Attribute::VectorF3	Pos;
		~InstBuffer();
		InstBuffer(::VertexArray & vertex_array);
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