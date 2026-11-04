#ifndef  UI_CONTROL_MANAGER_HPP
# define UI_CONTROL_MANAGER_HPP

# include "Graphics/Shader/Base.hpp"
# include "Graphics/VertexArray/MainInst.hpp"
# include "Graphics/Buffer/Array.hpp"

# include "Graphics/Layout.hpp"
# include "Graphics/MainLayout.hpp"
# include "Graphics/InstLayout.hpp"


# include "Generics/Container/Binary.hpp"
# include "Graphics/MainData.hpp"
# include "Graphics/InstData.hpp"



class DirectoryInfo;

namespace UI
{

namespace Control
{
class Base;
class Form;

//struct ObjectData;

class Manager
{
	public:
	static Manager * CurrentPointer;
	static Manager & Current();
	static bool CheckCurrent();
	static void ClearCurrent();
	bool IsCurrent() const;
	void MakeCurrent();





	public:
	::Shader::Base					Shader;
	UI::Control::ShaderLayout		ShaderLayout;

	public:
	VertexArray::MainInst			Buffer;
	UI::Control::Main::Layout		BufferLayoutMain;
	UI::Control::Inst::Layout		BufferLayoutInst;

	public:
	~Manager();
	Manager();
	Manager(const Manager & other) = delete;
	Manager & operator=(const Manager & other) = delete;

	public:
	Container::Binary<Control::Inst::Data>		Instances;
	void	InstancePut(const Control::Inst::Data & data);

	public:
	void	ChangeMedia(const DirectoryInfo & dir);

	private:
	bool	GraphicsExist = false;
	public:
	void	GraphicsCreate();
	void	GraphicsDelete();
	void	GraphicsInit();

	private:
	bool	GraphicsNeedMain = false;

	private:
	void	GraphicsPutMain();
	void	GraphicsPutInst();

	public:
	void	GraphicsClear();
	void	GraphicsMake();

	public:
	void	GraphicsDraw();
};

};

};

#endif