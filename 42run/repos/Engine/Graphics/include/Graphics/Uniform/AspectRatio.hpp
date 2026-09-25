#ifndef  UNIFORM_ASPECT_RATIO_HPP
# define UNIFORM_ASPECT_RATIO_HPP

# include "Graphics/Uniform/General/TypeBase.hpp"
# include "Graphics/Uniform/TypeDefs/VectorF2.hpp"

struct AspectRatio;

namespace Uniform
{
class AspectRatio : public Uniform::TypeBase<::AspectRatio>
{
	private:
	Uniform::VectorF2	Value;

	public:
	AspectRatio(std::string name, bool is_dynamic = false);
	AspectRatio(Uniform::Layout & layout, std::string name, bool is_dynamic = false);

	public:
	void	Put(const ::AspectRatio & obj) override;
};
};

#endif