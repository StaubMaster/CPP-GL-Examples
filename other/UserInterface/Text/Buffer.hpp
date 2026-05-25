#ifndef  UI_TEXT_BUFFER
# define UI_TEXT_BUFFER

#include "Graphics/Buffer/VertexArray.hpp"
#include "Graphics/Buffer/Array.hpp"

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