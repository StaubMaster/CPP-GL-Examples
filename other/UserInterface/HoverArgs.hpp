#ifndef  HOVER_ARGS_HPP
# define HOVER_ARGS_HPP

# include "Display/DisplayPosition.hpp"

enum class HoverType
{
	Enter,
	Move,
	Leave,
};
struct HoverArgs
{
	HoverType			Type;
	DisplayPosition		Position;

	HoverArgs(HoverType type, DisplayPosition position);
};

#endif