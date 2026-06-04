#ifndef  UI_CONTROL_MANAGER_HPP
# define UI_CONTROL_MANAGER_HPP

# include "Data.hpp"
# include "Buffer.hpp"
# include "ShaderLayout.hpp"
# include "Graphics/Shader/Base.hpp"

# include "Control/Window.hpp"

# include "Display/DisplaySize.hpp"

# include "User/MouseArgs.hpp"
# include "User/KeyBoardArgs.hpp"

# include "Miscellaneous/Container/Binary.hpp"

# include "OpenGL.hpp"



class DirectoryInfo;

namespace UI
{

namespace Control
{
class Base;
class Form;

struct ObjectData;

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

	UI::Control::Buffer				Buffer;
	UI::Control::Main_Layout		BufferLayoutMain;
	UI::Control::Inst_Layout		BufferLayoutInst;

	Container::Binary<ObjectData*>			ObjectDatas;
	Container::Binary<Control::Inst_Data>	Instances;

	public:
	~Manager();
	Manager();
	Manager(const Manager & other) = delete;
	Manager & operator=(const Manager & other) = delete;

	public:
	ObjectData *	PlaceObject();
	ObjectData *	CopyObject(const ObjectData * obj);
	// give these functions static Variants that return if no Current
	// else they do the stuff with current

	public:
	void	ChangeMedia(const DirectoryInfo & dir);

	private:
	bool	GraphicsExist;
	public:
	void	GraphicsCreate();
	void	GraphicsDelete();

	private:
	bool	GraphicsNeedMain;

	private:
	void	GraphicsMain();
	void	GraphicsInst();

	private:
	void	PlaceInstance(const ObjectData & obj);
	public:
	void	MakeInstances();

	public:
	void	Draw();
};

};

};

#endif