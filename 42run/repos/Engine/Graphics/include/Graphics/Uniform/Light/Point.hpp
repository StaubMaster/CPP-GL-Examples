#ifndef  UNIFORM_LIGHT_POINT_HPP
# define UNIFORM_LIGHT_POINT_HPP

# include "Graphics/Uniform/General/TypeBase.hpp"
# include "Graphics/Uniform/Light/Base.hpp"
# include "Graphics/Uniform/TypeDefs/VectorF3.hpp"

struct LightPoint;

namespace Uniform
{
class LightPoint : public Uniform::TypeBase<::LightPoint>
{
	private:
	Uniform::LightBase	Base;
	Uniform::VectorF3	Pos;

	public:
	LightPoint(std::string name, bool is_dynamic = false);
	LightPoint(Uniform::Layout & layout, std::string name, bool is_dynamic = false);

	public:
	void Put(const ::LightPoint & obj) override;
};
};

#endif