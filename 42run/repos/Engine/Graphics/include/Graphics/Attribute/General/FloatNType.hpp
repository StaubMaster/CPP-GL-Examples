#ifndef  ATTRIBUTE_FLOAT_N_TYPE_HPP
# define ATTRIBUTE_FLOAT_N_TYPE_HPP

# include "Graphics/Attribute/General/FloatNBase.hpp"

# include "OpenGLTypes.hpp"
# include "OpenGL.hpp"

namespace Attribute
{
template<unsigned int Size0, unsigned int Size1>
class FloatNType : public Attribute::FloatNBase
{
	public:
	virtual ~FloatNType()
	{ }

	FloatNType() = delete;
	FloatNType(const FloatNType & other) = delete;

	FloatNType & operator=(const FloatNType & other) // = default;
	{
		Attribute::Base::operator=(other);
		return *this;
	}

	FloatNType(Layout & layout, bool is_dynamic = false)
		: FloatNBase(layout, is_dynamic)
	{ }
	FloatNType(Layout & layout, GL::AttributeLocation index, bool is_dynamic = false)
		: FloatNBase(layout, index, is_dynamic)
	{ }

	FloatNType(Layout & layout, const FloatNType & other, bool is_dynamic = false)
		: Attribute::FloatNBase(layout, other, is_dynamic)
	{ }

	public:
	void	Bind(GL::AttributeDivisor divisor, GL::AttributeStride stride, GL::AttributeOffset & offset) const override
	{
		for (unsigned int s = 0; s < Size1; s++)
		{
			if (Index != -1)
			{
				GL::EnableVertexAttribArray(Index + s);
				GL::VertexAttribDivisor(Index + s, divisor);
				GL::VertexAttribPointer(Index + s, Size0, GL::AttributeType::Float, GL_FALSE, stride, offset);
			}
			offset += Size0 * sizeof(float);
		}
	}

	public:
	unsigned int	CalcSize() const override
	{
		return Size0 * Size1 * sizeof(float);
	}

	public:
	void	LogInfo() const override
	{
		LogInfoBase(GL::AttributeType::Float, Size0, Size1);
	}
};
};

#endif