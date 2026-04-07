#ifndef  UI_CONTROL_MANAGER_HPP
# define UI_CONTROL_MANAGER_HPP

#include "Data.hpp"
#include "Buffer.hpp"
#include "Shader.hpp"

#include "Control/Window.hpp"

#include "Display/DisplaySize.hpp"

#include "User/MouseArgs.hpp"
#include "User/KeyBoardArgs.hpp"

#include "Miscellaneous/Container/Binary.hpp"
#include "Miscellaneous/EntryContainer/Binary.hpp"



namespace UI
{

namespace Control
{
class Base;

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
	UI::Control::Shader		Shader;
	UI::Control::Buffer		Buffer;

	EntryContainer::Binary<Control::Inst_Data> Inst_Data_Container;

	Container::Binary<ObjectData*>			ObjectDatas;
	Container::Binary<Control::Inst_Data>	Instances;

	DisplaySize		WindowSize;

	UI::Control::Window		Window;

	Base *	Hovering;
	Base *	Selected;

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

	private:
	bool	GraphicsExist;
	public:
	void	GraphicsCreate();
	void	GraphicsDelete();

	private:
	bool	GraphicsNeedInit;
	bool	GraphicsNeedMain;
	private:
	void	GraphicsInit();
	void	GraphicsMain();
	void	GraphicsInst();

	private:
	void			PlaceInstance(const ObjectData & obj);

	public:
	void	Draw();

	void UpdateSize(const DisplaySize & window_size);
	void UpdateMouse(Point2D mouse);

	void RelayClick(ClickArgs args);
	void RelayScroll(ScrollArgs args);
	void RelayCursorDrag(DragArgs args);

	void RelayKey(KeyArgs args);
	void RelayText(TextArgs args);
};

};

};

#endif