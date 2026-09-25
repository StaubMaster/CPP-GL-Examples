#ifndef  UNIFORM_RANGE_F_HPP
# define UNIFORM_RANGE_F_HPP

# include "Graphics/Uniform/General/TypeBase.hpp"
# include "Graphics/Uniform/TypeDefs/Float.hpp"

struct RangeF;

namespace Uniform
{
class RangeF : public Uniform::TypeBase<::RangeF>
{
	private:
	Uniform::Float	Min;
	Uniform::Float	Len;
	Uniform::Float	Max;

	public:
	RangeF(std::string name, bool is_dynamic = false);
	RangeF(Uniform::Layout & layout, std::string name, bool is_dynamic = false);

	public:
	void	Put(const ::RangeF & obj) override;
};
};

#endif