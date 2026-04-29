#ifndef  UI_CONTROL_BUFFER_HPP
# define UI_CONTROL_BUFFER_HPP

#include "Graphics/Buffer/VertexArray.hpp"
#include "Graphics/Buffer/Array.hpp"

#include "Graphics/Attribute/Base/Base.hpp"
#include "Graphics/Attribute/VectorF2.hpp"
#include "Graphics/Attribute/ColorF4.hpp"
#include "Graphics/Attribute/Float.hpp"



namespace UI
{

namespace Control
{

class Main_Buffer : public ::Buffer::Array
{
	public:
	::Attribute::VectorF2	Pos;
	public:
	~Main_Buffer();
	Main_Buffer(::VertexArray & vertex_array);
};

class Inst_Buffer : public ::Buffer::Array
{
	public:
	::Attribute::VectorF2	Min;
	::Attribute::VectorF2	Max;
	::Attribute::Float		Layer;
	::Attribute::ColorF4	Col;
	public:
	~Inst_Buffer();
	Inst_Buffer(::VertexArray & vertex_array);
};

class Buffer : public ::VertexArray
{
	public:
	Main_Buffer		Main;
	Inst_Buffer		Inst;
	GL::DrawMode	DrawMode;
	public:
	~Buffer();
	Buffer();
	public:
	void Draw();
};

};

};

#endif