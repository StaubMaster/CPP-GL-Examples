#ifndef  UI_CONTROL_WINDOW_HPP
# define UI_CONTROL_WINDOW_HPP

#include "Base/Base.hpp"



namespace UI
{

namespace Control
{

class Window : public Base
{
	public:
		Window(Manager & manager);
		~Window();

	public:
		void UpdateWindowSize(Point2D size);
};

};

};

#endif