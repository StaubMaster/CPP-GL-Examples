#ifndef  UI_CONTROL_MANAGER_HPP
# define UI_CONTROL_MANAGER_HPP

# include "ShaderLayout.hpp"
# include "BufferLayout.hpp"
# include "BufferData.hpp"
# include "Buffer.hpp"

# include "Graphics/VertexArray/MainInst.hpp"
# include "Graphics/Buffer/Array.hpp"

# include "Graphics/Shader/Base.hpp"

# include "Generics/Container/Binary.hpp"



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

	VertexArray::MainInst				Buffer;
	UI::Control::Main::BufferLayout		BufferLayoutMain;
	UI::Control::Inst::BufferLayout		BufferLayoutInst;

	Container::Binary<ObjectData*>					ObjectDatas;
	Container::Binary<Control::Inst::BufferData>	Instances;

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
	void	GraphicsInit();

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