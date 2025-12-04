#ifndef  UI_TEXT_BUFFER
# define UI_TEXT_BUFFER

# include "Graphics/Buffer/BaseBufferArray.hpp"
# include "Graphics/Buffer/BaseBuffer.hpp"

# include "Graphics/Attribute/Base/AttributeBase.hpp"
# include "Graphics/Attribute/Point2D.hpp"



namespace UI
{

namespace Text
{

class Main_Attribute : public Attribute::Base
{
	private:
		Attribute::Point2D	Pos;
	public:
		Main_Attribute(
			unsigned int divisor,
			unsigned int stride,
			unsigned int indexPos
		);
	public:
		void Bind(const unsigned char * & offset) const override;
};

class Inst_Attribute : public Attribute::Base
{
	private:
		Attribute::Point2D	Pos;
		Attribute::Point2D	Pallet;
	public:
		Inst_Attribute(
			unsigned int divisor,
			unsigned int stride,
			unsigned int indexPos,
			unsigned int indexPallet
		);
	public:
		void Bind(const unsigned char * & offset) const override;
};

class BufferArray : public BaseBufferArray
{
	public:
		BaseBuffer Main;
		BaseBuffer Inst;

	public:
		BufferArray();

	public:
		void Draw() override;
};

};

};

#endif