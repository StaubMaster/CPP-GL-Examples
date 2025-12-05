#ifndef  UI_CONTROL_MANAGER_HPP
# define UI_CONTROL_MANAGER_HPP

#include "Data.hpp"
#include "Buffer.hpp"
#include "Shader.hpp"
#include "Base.hpp"

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

		void UpdateSize(Point2D size);
		void UpdateMouse(Point2D mouse);

		void Click(unsigned char action, unsigned char code);
		void Key(int key, int scancode, int action, int mods);
		void DoText(unsigned int codepoint);
};

};

};

#endif