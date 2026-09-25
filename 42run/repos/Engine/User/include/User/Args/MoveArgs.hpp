#ifndef  USER_ARGS_MOVE_HPP
# define USER_ARGS_MOVE_HPP

# include "Display/DisplayPosition.hpp"

struct MoveArgs
{
	DisplayPosition		Position;

	MoveArgs(DisplayPosition pos);
};

#endif