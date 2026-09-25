#ifndef  UNIFORM_DEPTH_HPP
# define UNIFORM_DEPTH_HPP

# include "Graphics/Uniform/General/TypeBase.hpp"
# include "Graphics/Uniform/TypeDefs/DepthFactors.hpp"
# include "Graphics/Uniform/RangeF.hpp"
# include "Graphics/Uniform/TypeDefs/ColorF4.hpp"

struct Depth;

namespace Uniform
{
class Depth : public Uniform::TypeBase<::Depth>
{
	private:
	Uniform::DepthFactors	Factors;
	Uniform::RangeF			Range;
	Uniform::ColorF4		Color;

	public:
	Depth(std::string name, bool is_dynamic = false);
	Depth(Uniform::Layout & layout, std::string name, bool is_dynamic = false);

	public:
	void Put(const ::Depth & obj) override;
};
};

#endif