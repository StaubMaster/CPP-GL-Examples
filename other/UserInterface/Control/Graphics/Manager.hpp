#ifndef  UI_CONTROL_MANAGER_HPP
# define UI_CONTROL_MANAGER_HPP
// move this out of Control/General into Control/ ?
// rename to "Graphics" so it is UI::Control::Graphics ?
// maybe GraphicsManager

# include "Graphics/Shader/Base.hpp"
# include "Graphics/VertexArray/MainInst.hpp"
# include "Graphics/Buffer/Array.hpp"

# include "Main/Layout.hpp"
# include "Inst/Layout.hpp"
# include "Layout.hpp"

# include "Main/Data.hpp"
# include "Inst/Data.hpp"

# include "Generics/Container/Binary.hpp"



class DirectoryInfo;

namespace UI
{
namespace Control
{
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
	void	InstancesClear();
//	void	InstancesMake();
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
	void	GraphicsDraw();
};
};
};

#endif