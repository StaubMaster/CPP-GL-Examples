#ifndef  PLANE_GRAPHICS_HPP
# define PLANE_GRAPHICS_HPP

# include "ValueType/Point3D.hpp"
# include "ValueType/ColorF4.hpp"

# include "Graphics/Buffer/MainInst.hpp"
# include "Graphics/Buffer/Array.hpp"
# include "Graphics/Attribute/Point3D.hpp"
# include "Graphics/Attribute/ColorF4.hpp"

# include "Graphics/Shader/Base.hpp"
# include "Graphics/Uniform/_Include.hpp"

namespace PlaneGraphics
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
	struct MainBuffer : public ::Buffer::Array
	{
		::Attribute::Point3D	Pos;
		::Attribute::ColorF4	Col;
		~MainBuffer();
		MainBuffer(::VertexArray & vertex_array);
	};
	struct InstBuffer : public ::Buffer::Array
	{
		::Attribute::Point3D	Pos;
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