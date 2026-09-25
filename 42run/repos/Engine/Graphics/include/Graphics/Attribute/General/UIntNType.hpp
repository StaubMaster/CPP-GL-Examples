#ifndef  ATTRIBUTE_UINT_N_TYPE_HPP
# define ATTRIBUTE_UINT_N_TYPE_HPP

# include "Graphics/Attribute/General/UIntNBase.hpp"

# include "OpenGLTypes.hpp"
# include "OpenGL.hpp"

namespace Attribute
{
template<unsigned int Size0, unsigned int Size1>
class UIntNType : public Attribute::UIntNBase
{
	public:
	virtual ~UIntNType()
	{ }

	UIntNType() = delete;
	UIntNType(const UIntNType & other) = delete;

	UIntNType & operator=(const UIntNType & other)
	{
		Attribute::Base::operator=(other);
		return *this;
	}

	public:
	UIntNType(Layout & layout, bool is_dynamic = false)
		: UIntNBase(layout, is_dynamic)
	{ }
	UIntNType(Layout & layout, const UIntNType & other, bool is_dynamic = false)
		: Attribute::UIntNBase(layout, other, is_dynamic)
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
				GL::VertexAttribIPointer(Index + s, Size0, GL::AttributeIntType::UnsignedInt, stride, offset);
			}
			offset += Size0 * sizeof(unsigned int);
		}
	}

	public:
	unsigned int	CalcSize() const override
	{
		return Size0 * Size1 * sizeof(unsigned int);
	}

	public:
	void	LogInfo() const override
	{
		LogInfoBase(GL::AttributeIntType::UnsignedInt, Size0, Size1);
	}
};
};

#endif