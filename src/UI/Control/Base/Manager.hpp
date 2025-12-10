#ifndef  UI_CONTROL_MANAGER_HPP
# define UI_CONTROL_MANAGER_HPP

#include "Data.hpp"
#include "Buffer.hpp"
#include "Shader.hpp"
#include "Base.hpp"

#include "UserParameter/Click.hpp"
#include "UserParameter/Scroll.hpp"
#include "UserParameter/Key.hpp"
#include "UserParameter/Text.hpp"

#include "Miscellaneous/Container/Dynamic.hpp"
#include "Miscellaneous/EntryContainer/Dynamic.hpp"



class DirectoryContext;



namespace UI
{

namespace Control
{
//class Base;

class Window;

class Manager
{
	public:
		BaseShader Shader;
		BufferArray BufferArray;

		Container::Dynamic<Control::Main_Data> Main_Data_Container;
		EntryContainer::Dynamic<Control::Inst_Data> Inst_Data_Container;

		Point2D ViewPortSize;

		UI::Control::Window * Window;

		Base * Hovering;
		Base * Selected;

	public:
		Manager(const DirectoryContext & dir);
		~Manager();

		void Draw();

		void UpdateSize(const SizeRatio2D & ViewPortSizeRatio);
		void UpdateMouse(Point2D mouse);

		void RelayClick(UserParameter::Click params);
		void RelayScroll(UserParameter::Scroll params);
		void RelayKey(UserParameter::Key params);
		void RelayText(UserParameter::Text params);
};

};

};

#endif