#ifndef  UI_PARAMETER_CLICK_HPP
# define UI_PARAMETER_CLICK_HPP

#include "DataStruct/Point2D.hpp"

namespace UI
{

namespace Parameter
{

struct Click
{
	int code;
	int action;
	Point2D Absolute;
	Point2D Relative;
};

};

};

#endif