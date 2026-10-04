#ifndef  LAYOUT_MULTIFORM_DISPLAY_HPP
# define LAYOUT_MULTIFORM_DISPLAY_HPP

# include "Graphics/Multiform/General/Layout.hpp"
# include "Graphics/Multiform/TypeDefs/DisplaySize.hpp"

class LayoutMultiformDisplay : public Multiform::Layout
{
	public:
	Multiform::DisplaySize		DisplaySize;
	public:
	LayoutMultiformDisplay();
};

#endif