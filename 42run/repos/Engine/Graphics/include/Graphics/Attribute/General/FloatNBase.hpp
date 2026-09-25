#ifndef  ATTRIBUTE_FLOAT_N_BASE_HPP
# define ATTRIBUTE_FLOAT_N_BASE_HPP

# include "Graphics/Attribute/General/Base.hpp"
# include "OpenGLTypes.hpp"

namespace Attribute
{
class FloatNBase : public Attribute::Base
{
	protected:
	GL::AttributeLocation	Index = -1;

	public:
	virtual ~FloatNBase();

	public:
	FloatNBase() = delete;
	FloatNBase(const FloatNBase & other) = delete;
	FloatNBase & operator=(const FloatNBase & other); // = default;

	public:
	FloatNBase(Layout & layout, bool is_dynamic);
	FloatNBase(Layout & layout, GL::AttributeLocation index, bool is_dynamic);
	FloatNBase(Layout & layout, const FloatNBase & other, bool is_dynamic);

	public:
	void	Change(GL::AttributeLocation index);

	protected:
	void	LogInfoBase(GL::AttributeType type, unsigned int size0, unsigned int size1) const;
};
};

#endif