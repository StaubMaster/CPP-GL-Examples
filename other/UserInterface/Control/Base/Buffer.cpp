#include "Buffer.hpp"
#include "Data.hpp"

#include "OpenGL.hpp"



UI::Control::Main_Buffer::Main_Buffer(
	::BufferArray::Base & buffer_array,
	unsigned int indexPos
)	: ::Buffer::Attribute(buffer_array, GL::BufferDataUsage::StaticDraw, 0, sizeof(Main_Data))
	, Pos()
{
	Attributes.Allocate(1);
	Attributes.Insert(&Pos);

	Pos.Change(indexPos);
}



UI::Control::Inst_Buffer::Inst_Buffer(
	::BufferArray::Base & buffer_array,
	unsigned int indexMin,
	unsigned int indexMax,
	unsigned int indexLayer,
	unsigned int indexCol
)	: ::Buffer::Attribute(buffer_array, GL::BufferDataUsage::StreamDraw, 1, sizeof(Inst_Data))
	, Min()
	, Max()
	, Layer()
	, Col()
{
	Attributes.Allocate(4);
	Attributes.Insert(&Min);
	Attributes.Insert(&Max);
	Attributes.Insert(&Layer);
	Attributes.Insert(&Col);

	Min.Change(indexMin);
	Max.Change(indexMax);
	Layer.Change(indexLayer);
	Col.Change(indexCol);
}



UI::Control::BufferArray::BufferArray()
	: ::BufferArray::Base()
	, Main(*this, 0)
	, Inst(*this, 1, 2, 3, 4)
	, DrawMode(GL::DrawMode::Triangles)
{
	Buffers.Allocate(2);
	Buffers.Insert(&Main);
	Buffers.Insert(&Inst);
}
void UI::Control::BufferArray::Draw()
{
	Bind();
	GL::DrawArraysInstanced(DrawMode, 0, Main.DrawCount, Inst.DrawCount);
}
