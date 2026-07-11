#ifndef  UI_CONTROL_WINDOW_HPP
# define UI_CONTROL_WINDOW_HPP

# include "Control/General/Base.hpp"



namespace UI
{

namespace Control
{

class Window : public Base
{
	public:
	Window();
	~Window();

	public:
	void UpdateWindowSize(VectorF2 size);
};

};

};

#endif