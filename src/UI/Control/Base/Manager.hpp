#ifndef  UI_CONTROL_MANAGER_HPP
# define UI_CONTROL_MANAGER_HPP

#include "Data.hpp"
#include "Buffer.hpp"
#include "Shader.hpp"
//#include "Base.hpp"

#include "Display/WindowBufferSize2D.hpp"

//#include "UserParameter/Mouse/Click.hpp"
//#include "UserParameter/Mouse/Scroll.hpp"
//#include "UserParameter/Mouse/Drag.hpp"
#include "UserParameter/MouseDeclare.hpp"

#include "UserParameter/KeyBoard/Key.hpp"
#include "UserParameter/KeyBoard/Text.hpp"

#include "Miscellaneous/Container/Binary.hpp"
#include "Miscellaneous/EntryContainer/Binary.hpp"



class DirectoryInfo;



namespace UI
{

namespace Control
{
class Base;

class Window;

class Manager
{
	public:
		Shader Shader;
		BufferArray BufferArray;

		Container::Binary<Control::Main_Data> Main_Data_Container;
		EntryContainer::Binary<Control::Inst_Data> Inst_Data_Container;

		WindowBufferSize2D WindowSize;

		UI::Control::Window * Window;

		Base * Hovering;
		Base * Selected;

	public:
		Manager(const DirectoryInfo & dir);
		~Manager();

		void Draw();

		void UpdateSize(const WindowBufferSize2D & window_size);
		void UpdateMouse(Point2D mouse);

		void RelayClick(UserParameter::Mouse::Click params);
		void RelayScroll(UserParameter::Mouse::Scroll params);
		void RelayCursorDrag(UserParameter::Mouse::Drag params);

		void RelayKey(UserParameter::KeyBoard::Key params);
		void RelayText(UserParameter::KeyBoard::Text params);
};

};

};

#endif