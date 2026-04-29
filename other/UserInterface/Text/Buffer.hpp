#ifndef  UI_TEXT_BUFFER
# define UI_TEXT_BUFFER

#include "Graphics/Buffer/VertexArray.hpp"
#include "Graphics/Buffer/Array.hpp"

# include "Graphics/Attribute/Base/Base.hpp"
# include "Graphics/Attribute/VectorF2.hpp"
# include "Graphics/Attribute/BoxF2.hpp"
# include "Graphics/Attribute/ColorF4.hpp"



namespace UI
{

namespace Text
{

class Main_Buffer : public ::Buffer::Array
{
	public:
	::Attribute::VectorF2	Pos;
	public:
	Main_Buffer(::VertexArray & vertex_array);
};

class Inst_Buffer : public ::Buffer::Array
{
	public:
	::Attribute::VectorF2	Pos;
	::Attribute::BoxF2		Pallet;
	::Attribute::BoxF2		Bound;
	::Attribute::ColorF4	Color;
	public:
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