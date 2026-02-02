#ifndef  UI_TEXT_BUFFER
# define UI_TEXT_BUFFER

#include "Graphics/Buffer/ArrayBase.hpp"
#include "Graphics/Buffer/Attribute.hpp"

# include "Graphics/Attribute/Base/Base.hpp"
# include "Graphics/Attribute/Point2D.hpp"



namespace UI
{

namespace Text
{

class Main_Buffer : public ::Buffer::Attribute
{
	private:
	::Attribute::Point2D	Pos;
	public:
	Main_Buffer(
		unsigned int indexPos
	);
};

class Inst_Buffer : public ::Buffer::Attribute
{
	private:
	::Attribute::Point2D	Pos;
	::Attribute::Point2D	PalletMin;
	::Attribute::Point2D	PalletMax;
	::Attribute::Point2D	BoundMin;
	::Attribute::Point2D	BoundMax;
	public:
	Inst_Buffer(
		unsigned int indexPos,
		unsigned int indexPalletMin,
		unsigned int indexPalletMax,
		unsigned int indexBoundMin,
		unsigned int indexBoundMax
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