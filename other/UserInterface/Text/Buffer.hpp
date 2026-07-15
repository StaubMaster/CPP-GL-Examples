#ifndef  UI_TEXT_BUFFER
# define UI_TEXT_BUFFER

# include "Graphics/Buffer/MainInst.hpp"

# include "Graphics/Attribute/General/Layout.hpp"
# include "Graphics/Attribute/_Include.hpp"



namespace UI
{

namespace Text
{

class Main_Layout : public ::Attribute::Layout
{
	public:
	::Attribute::VectorF2	Pos;
	public:
	Main_Layout();
};

class Inst_Layout : public ::Attribute::Layout
{
	public:
	::Attribute::VectorF2	TextPos;
	::Attribute::UInt		CharIdx;
	::Attribute::UInt		TextIdx;
	public:
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