#ifndef  LAYOUT_UNIFORM_DISPLAY_HPP
# define LAYOUT_UNIFORM_DISPLAY_HPP

# include "Graphics/Uniform/General/Layout.hpp"
# include "Graphics/Uniform/DisplaySize.hpp"

class LayoutUniformDisplay : public Uniform::Layout
{
	public:
	Uniform::DisplaySize	DisplaySize;
	public:
	LayoutUniformDisplay();
};

#endif