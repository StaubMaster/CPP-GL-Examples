#ifndef  UNIFORM_LIGHT_BASE_HPP
# define UNIFORM_LIGHT_BASE_HPP

# include "Graphics/Uniform/General/TypeBase.hpp"
# include "Graphics/Uniform/TypeDefs/Float.hpp"
# include "Graphics/Uniform/TypeDefs/ColorF4.hpp"

struct LightBase;

namespace Uniform
{
class LightBase : public Uniform::TypeBase<::LightBase>
{
	private:
	Uniform::Float		Intensity;
	Uniform::ColorF4	Color;

	public:
	LightBase(std::string name, bool is_dynamic = false);
	LightBase(Uniform::Layout & layout, std::string name, bool is_dynamic = false);

	public:
	void Put(const ::LightBase & obj) override;
};
};

#endif