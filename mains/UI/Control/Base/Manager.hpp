#ifndef  CONTROL_MANAGER_HPP
# define CONTROL_MANAGER_HPP

#include "Data.hpp"
#include "Buffer.hpp"
#include "Shader.hpp"
#include "Base.hpp"

#include "DataInclude.hpp"

#include "Miscellaneous/Container/Dynamic.hpp"
#include "Miscellaneous/EntryContainer/Dynamic.hpp"

#include "OpenGL/openGL.h"

class DirectoryContext;

namespace Control
{
//class Base;

struct Manager
{
	public:
		Point2D ViewPortSize;

		Container::Dynamic<Control::Main_Data> Main_Data_Container;
		EntryContainer::Dynamic<Control::Inst_Data> Inst_Data_Container;

		BaseShader Shader;
		BufferArray BufferArray;

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

#endif