#ifndef  UI_CONTROL_GRAPHICS_LAYOUT_HPP
# define UI_CONTROL_GRAPHICS_LAYOUT_HPP

#include "Graphics/Uniform/General/Layout.hpp"
#include "Graphics/Uniform/_Include.hpp"

// this is a generic Layout
namespace UI
{
namespace Control
{
class ShaderLayout : public Uniform::Layout
{
	public:
	Uniform::DisplaySize	DisplaySize;
	public:
	ShaderLayout();
};
};
};

#endif