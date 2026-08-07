#ifndef  UI_CONTROL_BASE_HPP
# define UI_CONTROL_BASE_HPP

#include "BufferData.hpp"

#include "Anchor2D.hpp"

#include "User/MouseArgs.hpp"
#include "User/KeyBoardArgs.hpp"

#include "ValueType/_Include.hpp"

#include "Generics/Container/Binary.hpp"

#include "Object.hpp"

#include "AnchorEnum.hpp"

/* what do Controls do ?

handle Events and/or Relay to children
change Size relative to Parent
change Visibility
change Layer (Depth)
change Color

*/

/* UpdateSize
Window Size changes
ControlManager is told that Size changed
Control::Window is told that Size changed
Control tells children that Size changed

should this be done immedeatly or be delayed ?
doing it immedeatly seems fine

it also sets a Flag that Anchor Size changed
*/

/* UpdateEntrys
is done every frame, before Draw
changes GraphicalBox, does not calculate
changes Color

why is this delayed ?
something else might also change it ?
the delayed stuff is assigning, which is the fastest part
if anything, delay the calculating ?
*/

/*
change in Enabled
	changes this

change in Visibility
	changes this
	changes Children

change in Transparency
	change this

change in Color
	changes this

change in Box
	changes this
	changes children
*/

enum class HoverType
{
	Enter,
	Move,
	Leave,
};
struct HoverArgs
{
	HoverType			Type;
	DisplayPosition		Position;

	HoverArgs(HoverType type, DisplayPosition position);
};

namespace UI
{
class Manager;
namespace Control
{
class Base
{
	protected:
	UI::Manager *	Manager;

	public:
	void	ChangeManager(UI::Manager * manager);
	void	ChangeManager(UI::Manager & manager);



	protected: public:
	Base *	Parent;

	public:
	unsigned int	Layer() const;

	public: // temp
	Container::Binary<Base *>	Children;

	public:
	void	ChildInsert(Base & control);
	void	ChildInsert(Base * control);
	public:
	void	ChildRemove(Base & control);
	void	ChildRemove(Base * control);



	public:
	bool	Deletable;		//should be deleted when Parent is deleted



	public:
	float	Depth; // make this unsigend char. 255 should be more then enough Layers
	// why so greedy ? just make this a uint32

	protected:
	bool	_Enabled;
	public:
	bool	IsEnabled() const;
	void	MakeEnabled();
	void	MakeDisabled();

	protected:
	bool	_Visible;
	public:
	bool	IsThisVisible() const;
	void	Show();
	void	Hide();

	protected:
	bool	_Opaque;
	public:
	bool	IsTransparent() const;
	bool	IsOpaque() const;
	void	MakeTransparent();
	void	MakeOpaque();

	public:
	bool	IsVisible() const;
	bool	IsDrawable() const;
	bool	IsThisInteractible() const;
	bool	IsInteractible() const;



	protected:
	VectorF2	AnchorSize;
	VectorF2	AnchorNormal;
	BoxF2		AnchorDist;
	public: //protected:
	BoxF2		AnchorMargin;
	BoxF2		AnchorBoarder;
	BoxF2		AnchorPadding;
	// ContentOffset ?
	public:
	Anchor2D	Anchor;



	public: //protected:
	BoxF2	BoxDisplay;
	BoxF2	BoxContent;

	public: //private:
	void	BoxUpdate();

	protected:
	virtual void	RelayBoxUpdate();

	protected:
	bool	BoxUpdateIsRequested;
	public:
	void	BoxUpdateRequest();
	private:
	void	BoxUpdateResolve();



	public:
	enum class EAutoAnchorType
	{
		None,
		StackMin, //MinDist of next = MinSize of prev
		StackMinFit, //StackMin but this Control is resized to fit Children
	};
	EAutoAnchorType		AutoAnchorXType;
	EAutoAnchorType		AutoAnchorYType;

	public:
	void	UpdateAutoAnchor(); // call this in Update ?

	private:
	void	UpdateAutoAnchor_Y_StackMin();
	void	UpdateAutoAnchor_Y_StackMinFit();



	public:
	ColorF4		ColorDefault;
	//Color		ColorDisabled; // Gray Text
	ColorF4		ColorHover;

	protected:
	virtual ColorF4		ColorMake() const;



	public:
	void	Update();

	protected:
	virtual void	RelayUpdate();



	protected:
	Control::Object		Object;

	private:
	void	ObjectInsert();
	void	ObjectRemove();

	protected:
	virtual void	RelayObjectInsert();
	virtual void	RelayObjectRemove();

	private:
	bool	ObjectChangeIsRequested;
	void	ObjectChangeRequest();
	void	ObjectChangeResolve();



	private:
	void	ObjectAssignBox();

	private:
	bool	ObjectAssignBoxIsRequested;
	protected:
	void	ObjectAssignBoxRequest();
	private:
	void	ObjectAssignBoxResolve();



	private:
	void	ObjectAssignColor();

	private:
	bool	ObjectAssignColorIsRequested;
	public:
	void	ObjectAssignColorRequest();
	private:
	void	ObjectAssignColorResolve();



	public:
	void	ObjectAssign();

	protected:
	virtual void	RelayObjectAssign();



	public:
	virtual ~Base();
	Base();

	Base(const Base & other) = delete;
	Base & operator=(const Base & other) = delete;



	// Changing is only done with Forms. move this there
	protected:
	enum class EBoxChangeType : unsigned char
	{
		None,
		Move,
		ResizeMinX,
		ResizeMaxX,
		ResizeMinY,
		ResizeMaxY,
		ResizeMinMin,
		ResizeMinMax,
		ResizeMaxMin,
		ResizeMaxMax,
	};
	// this is here to have access to Box
	void	ChangeAnchorBox(BoxF2 box, EBoxChangeType type);



	public:
	Base *	FindHover(const VectorF2 & mouse);



	/* User Relay Invoker
		(const void *) or (const Control::Base *)
		not const ?
		? the Invoker Control is this
		the Control Pointer would be needed for Func Pointers
	*/
	/* User Relay return
		0: dont try to relay to parent
		1: try to relay this event to parent
	*/
	virtual void	RelayHover(HoverArgs args);
	virtual void	RelayClick(ClickArgs args);
	virtual void	RelayScroll(ScrollArgs args);
	virtual void	RelayDrag(DragArgs args);
	virtual void	RelayKey(KeyArgs args);
	virtual void	RelayText(TextArgs args);
	/* User Relay vs Func Pointer
		Relays:		internal
		Pointers:	external

		put all FuncPointer for these here ?
	*/
};
};
};

#endif