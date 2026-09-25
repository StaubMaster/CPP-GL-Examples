#ifndef  UNIFORM_LIGHT_SPOT_HPP
# define UNIFORM_LIGHT_SPOT_HPP

# include "Graphics/Uniform/General/TypeBase.hpp"
# include "Graphics/Uniform/Light/Base.hpp"
# include "Graphics/Uniform/TypeDefs/VectorF3.hpp"
# include "Graphics/Uniform/RangeF.hpp"

struct LightSpot;

namespace Uniform
{
class LightSpot : public Uniform::TypeBase<::LightSpot>
{
	private:
	Uniform::LightBase	Base;
	Uniform::VectorF3	Pos;
	Uniform::VectorF3	Dir;
	Uniform::RangeF		Range;

	public:
	LightSpot(std::string name, bool is_dynamic = false);
	LightSpot(Uniform::Layout & layout, std::string name, bool is_dynamic = false);

	public:
	void Put(const ::LightSpot & obj) override;
};
};

#endif