#ifndef  ATTRIB_BOX_F_2_HPP
# define ATTRIB_BOX_F_2_HPP

# include "Graphics/Attribute/General/Base.hpp"
# include "Graphics/Attribute/TypeDefs/VectorF2.hpp"

namespace Attribute
{
class BoxF2 : public Attribute::Base
{
	public:
	Attribute::VectorF2		Min;
	Attribute::VectorF2		Max;

	public:
	~BoxF2();
	BoxF2() = delete;
	BoxF2(const BoxF2 & other) = delete;
	BoxF2 & operator=(const BoxF2 & other) = delete;

	BoxF2(Layout & layout, bool is_dynamic = false);
	BoxF2(Layout & layout, const BoxF2 & other, bool is_dynamic = false);

	public:
	void	Bind(GL::AttributeDivisor divisor, GL::AttributeStride stride, GL::AttributeOffset & offset) const override;

	public:
	unsigned int	CalcSize() const override;
};
typedef BoxF2 BoxF2;
};

#endif