#ifndef  UNIFORM_LIGHT_DIRECTION_HPP
# define UNIFORM_LIGHT_DIRECTION_HPP

# include "Graphics/Uniform/General/TypeBase.hpp"
# include "Graphics/Uniform/Light/Base.hpp"
# include "Graphics/Uniform/TypeDefs/VectorF3.hpp"

struct LightDirection;

namespace Uniform
{
class LightDirection : public Uniform::TypeBase<::LightDirection>
{
	private:
	Uniform::LightBase	Base;
	Uniform::VectorF3	Dir;

	public:
	LightDirection(std::string name, bool is_dynamic = false);
	LightDirection(Uniform::Layout & layout, std::string name, bool is_dynamic = false);

	public:
	void Put(const ::LightDirection & obj) override;
};
};

#endif