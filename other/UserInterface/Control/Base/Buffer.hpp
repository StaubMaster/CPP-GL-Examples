#ifndef  UI_CONTROL_BUFFER_HPP
# define UI_CONTROL_BUFFER_HPP

#include "Graphics/Buffer/ArrayBase.hpp"
#include "Graphics/Buffer/Attribute.hpp"

#include "Graphics/Attribute/Base/Base.hpp"
#include "Graphics/Attribute/Point2D.hpp"
#include "Graphics/Attribute/ColorF4.hpp"
#include "Graphics/Attribute/Base/Float1.hpp"



namespace UI
{

namespace Control
{

class Main_Buffer : public ::Buffer::Attribute
{
	private:
	::Attribute::Point2D	Pos;
	public:
	Main_Buffer(
		::BufferArray::Base & buffer_array,
		unsigned int indexPos
	);
};

class Inst_Buffer : public Buffer::Attribute
{
	private:
	::Attribute::Point2D	Min;
	::Attribute::Point2D	Max;
	::Attribute::Float1		Layer;
	::Attribute::ColorF4	Col;
	public:
	Inst_Buffer(
		::BufferArray::Base & buffer_array,
		unsigned int indexMin,
		unsigned int indexMax,
		unsigned int indexLayer,
		unsigned int indexCol
	);
};

class BufferArray : public ::BufferArray::Base
{
	public:
	Main_Buffer		Main;
	Inst_Buffer		Inst;
	GL::DrawMode	DrawMode;

	public:
	BufferArray();

	public:
	void Draw();
};

};

};

#endif