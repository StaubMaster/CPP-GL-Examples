#ifndef  UI_CONTROL_BUFFER_HPP
# define UI_CONTROL_BUFFER_HPP

# include "Graphics/Buffer/VertexArray.hpp"
# include "Graphics/Buffer/Array.hpp"

# include "Graphics/Attribute/Layout.hpp"
# include "Graphics/Attribute/_Include.hpp"



namespace UI
{

namespace Control
{

class Main_Layout : public ::Attribute::Layout
{
	public:
	::Attribute::VectorF2	Pos;
	public:
	~Main_Layout();
	Main_Layout();
};

class Inst_Layout : public ::Attribute::Layout
{
	public:
	::Attribute::VectorF2	Min;
	::Attribute::VectorF2	Max;
	::Attribute::Float		Layer;
	::Attribute::ColorF4	Col;
	public:
	~Inst_Layout();
	Inst_Layout();
};

class Buffer : public ::VertexArray
{
	public:
	::Buffer::Array		Main;
	::Buffer::Array		Inst;
	GL::DrawMode		DrawMode;
	public:
	~Buffer();
	Buffer();
	public:
	void Draw();
};

};

};

#endif