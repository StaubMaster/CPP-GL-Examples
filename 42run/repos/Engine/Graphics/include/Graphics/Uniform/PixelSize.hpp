#ifndef  UNIFORM_PIXEL_SIZE_HPP
# define UNIFORM_PIXEL_SIZE_HPP

# include "Graphics/Uniform/General/TypeBase.hpp"
# include "Graphics/Uniform/TypeDefs/VectorF2.hpp"

struct PixelSize;

namespace Uniform
{
class PixelSize : public Uniform::TypeBase<::PixelSize>
{
	private:
	Uniform::VectorF2	Full;
	Uniform::VectorF2	Half;

	public:
	PixelSize(std::string name, bool is_dynamic = false);
	PixelSize(Uniform::Layout & layout, std::string name, bool is_dynamic = false);

	public:
	void	Put(const ::PixelSize & obj) override;
};
};

#endif