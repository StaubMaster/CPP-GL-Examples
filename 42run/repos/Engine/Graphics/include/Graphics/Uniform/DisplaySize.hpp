#ifndef  UNIFORM_DISPLAY_SIZE_HPP
# define UNIFORM_DISPLAY_SIZE_HPP

# include "Graphics/Uniform/General/TypeBase.hpp"
# include "Graphics/Uniform/AspectRatio.hpp"
# include "Graphics/Uniform/PixelSize.hpp"

struct DisplaySize;

namespace Uniform
{
class DisplaySize : public Uniform::TypeBase<::DisplaySize>
{
	private:
	Uniform::AspectRatio	Ratio;
	Uniform::PixelSize		Window;
	Uniform::PixelSize		Buffer;

	public:
	DisplaySize(std::string name, bool is_dynamic = false);
	DisplaySize(Uniform::Layout & layout, std::string name, bool is_dynamic = false);

	public:
	void Put(const ::DisplaySize & obj) override;
};
};

#endif