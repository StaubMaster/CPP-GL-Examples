#ifndef  UI_TEXT_BUFFER
# define UI_TEXT_BUFFER

#include "Graphics/Buffer/ArrayBase.hpp"
#include "Graphics/Buffer/Attribute.hpp"

# include "Graphics/Attribute/Base/Base.hpp"
# include "Graphics/Attribute/Point2D.hpp"
# include "Graphics/Attribute/AxisBox2D.hpp"
# include "Graphics/Attribute/ColorF4.hpp"



namespace UI
{

namespace Text
{

class Main_Buffer : public ::Buffer::Attribute
{
	public:
	::Attribute::Point2D	Pos;
	public:
	Main_Buffer(::BufferArray::Base & buffer_array);
};

class Inst_Buffer : public ::Buffer::Attribute
{
	public:
	::Attribute::Point2D	Pos;
	::Attribute::AxisBox2D	Pallet;
	::Attribute::AxisBox2D	Bound;
	::Attribute::ColorF4	Color;
	public:
	Inst_Buffer(::BufferArray::Base & buffer_array);
};

class Buffer : public ::BufferArray::Base
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