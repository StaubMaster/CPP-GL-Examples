#ifndef  ATTRIBUTE_INT_N_TYPE_HPP
# define ATTRIBUTE_INT_N_TYPE_HPP

# include "Graphics/Attribute/General/IntNBase.hpp"

# include "OpenGLTypes.hpp"
# include "OpenGL.hpp"

namespace Attribute
{
template<unsigned int Size0, unsigned int Size1>
class IntNType : public Attribute::IntNBase
{
	public:
	virtual ~IntNType()
	{ }

	IntNType() = delete;
	IntNType(const IntNType & other) = delete;

	IntNType & operator=(const IntNType & other)
	{
		Attribute::Base::operator=(other);
		return *this;
	}

	IntNType(Layout & layout, bool is_dynamic = false)
		: IntNBase(layout, is_dynamic)
	{ }
	IntNType(Layout & layout, const IntNType & other, bool is_dynamic = false)
		: Attribute::IntNBase(layout, other, is_dynamic)
	{ }

	public:
	void	Change(GL::AttributeLocation index)
	{
		Index = index;
	}

	public:
	void	Bind(GL::AttributeDivisor divisor, GL::AttributeStride stride, GL::AttributeOffset & offset) const override
	{
		for (unsigned int s = 0; s < Size1; s++)
		{
			if (Index != -1)
			{
				GL::EnableVertexAttribArray(Index + s);
				GL::VertexAttribDivisor(Index + s, divisor);
				GL::VertexAttribIPointer(Index + s, Size0, GL::AttributeIntType::Int, stride, offset);
			}
			offset += Size0 * sizeof(int);
		}
	}

	public:
	unsigned int	CalcSize() const override
	{
		return Size0 * Size1 * sizeof(int);
	}

	public:
	void	LogInfo() const override
	{
		LogInfoBase(GL::AttributeIntType::Int, Size0, Size1);
	}
};
};

#endif