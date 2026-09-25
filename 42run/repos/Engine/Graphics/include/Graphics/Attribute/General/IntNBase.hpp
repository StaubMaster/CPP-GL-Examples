#ifndef  ATTRIBUTE_INT_N_BASE_HPP
# define ATTRIBUTE_INT_N_BASE_HPP

# include "Graphics/Attribute/General/Base.hpp"
# include "OpenGLTypes.hpp"

namespace Attribute
{
class IntNBase : public Attribute::Base
{
	protected:
	GL::AttributeLocation	Index = -1;

	public:
	virtual ~IntNBase();

	public:
	IntNBase() = delete;
	IntNBase(const IntNBase & other) = delete;
	IntNBase & operator=(const IntNBase & other);

	public:
	IntNBase(Layout & layout, bool is_dynamic);
	IntNBase(Layout & layout, const IntNBase & other, bool is_dynamic);

	public:
	void	Change(GL::AttributeLocation index);

	protected:
	void	LogInfoBase(GL::AttributeIntType type, unsigned int size0, unsigned int size1) const;
};
};

#endif