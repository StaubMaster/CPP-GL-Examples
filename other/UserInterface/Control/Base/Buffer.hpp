#ifndef  UI_CONTROL_BUFFER_HPP
# define UI_CONTROL_BUFFER_HPP

# include "Graphics/Buffer/MainInst.hpp"

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

typedef ::BufferArray::MainInst<
	GL::BufferDataUsage::StaticDraw,
	GL::BufferDataUsage::StreamDraw,
	GL::DrawMode::Triangles
> Buffer;

};

};

#endif