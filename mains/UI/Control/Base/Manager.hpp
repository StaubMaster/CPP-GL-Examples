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

class Manager
{
	public:
		BaseShader Shader;
		BufferArray BufferArray;

		Container::Dynamic<Control::Main_Data> Main_Data_Container;
		EntryContainer::Dynamic<Control::Inst_Data> Inst_Data_Container;

		Point2D ViewPortSize;

		Base * Hovering;
		Base * Selected;

	public:
		Manager(const DirectoryContext & dir);
		~Manager();

		void BufferUpdate();
		void BufferDraw();

		void ChangeHover(Base * control);
		void Click(unsigned char clickType, unsigned char clickButton);
};

};

};

#endif