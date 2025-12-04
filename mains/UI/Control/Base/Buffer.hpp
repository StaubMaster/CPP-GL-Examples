#ifndef  UI_CONTROL_BUFFER_HPP
# define UI_CONTROL_BUFFER_HPP

#include "Graphics/Buffer/BaseBufferArray.hpp"
#include "Graphics/Buffer/BaseBuffer.hpp"

#include "Graphics/Attribute/Base/AttributeBase.hpp"
#include "Graphics/Attribute/Point2D.hpp"
#include "Graphics/Attribute/Color.hpp"



namespace UI
{

namespace Control
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
		Attribute::Point2D	Min;
		Attribute::Point2D	Max;
		Attribute::FloatN	Layer;
		Attribute::Color	Col;
	public:
		Inst_Attribute(
			unsigned int divisor,
			unsigned int stride,
			unsigned int indexMin,
			unsigned int indexMax,
			unsigned int indexLayer,
			unsigned int indexCol
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