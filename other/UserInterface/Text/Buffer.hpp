#ifndef  UI_TEXT_BUFFER
# define UI_TEXT_BUFFER

# include "Graphics/Buffer/MainInst.hpp"

# include "Graphics/Attribute/Layout.hpp"
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
	::Attribute::VectorF2	Pos;
	::Attribute::UInt		PalletIdx;
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