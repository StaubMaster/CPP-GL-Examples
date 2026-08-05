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



	protected:
	Base *		Parent;

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

	public: //protected:
	bool	BoxUpdateIsRequested;
	public: //private:
	void	BoxUpdateRequest();
	private:
	void	BoxUpdateResolve();

	protected:
	virtual void	RelayBoxUpdate();



	public:
	enum class EAutoSizerType
	{
		None,
		FitFixed,
	};
	EAutoSizerType		AutoSizerXType;
	EAutoSizerType		AutoSizerYType;

	public:
	void	UpdateAutoSize();

	private:
	void	UpdateAutoSizeGridY();



	public:
	ColorF4		ColorDefault;
	//Color		ColorDisabled; // Gray Text
	ColorF4		ColorHover;



	protected:
	Control::Object		Object;
	bool				ObjectNewBox;
	bool				ObjectNewColor;

	private:
	bool	ObjectChangeIsRequested;
	void	ObjectChangeRequest();
	void	ObjectChangeResolve(); // combine this with ObjectAssign() ?

	private:
	void	ObjectInsert();
	void	ObjectRemove();
	void	ObjectAssign(); // combine this with ObjectChangeResolve() ?
	void	ObjectAssignBox();
	void	ObjectAssignColor();

	protected:
	virtual void	RelayObjectInsert();
	virtual void	RelayObjectRemove();
	virtual void	RelayObjectAssignBox();
	virtual void	RelayObjectAssignColor();



	public:
	virtual ~Base();
	Base();

	Base(const Base & other) = delete;
	Base & operator=(const Base & other) = delete;

	public:
	void	Update();



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
	enum class HoverArgs
	{
		Enter,
		Move,
		Leave,
	}; // should be a struct that also stores position

	//	for automatic Updating. should not be called by User
	public:
	Base *	CheckHover(VectorF2 mouse);
	void	ChangeHover(HoverArgs args);

	// Relay User
	// should take Pointer to Invoker ?
	//   (const void *) or (const Control::Base *)
	//   should these even be const ?
	virtual void	RelayHover(HoverArgs args);
	virtual void	RelayClick(ClickArgs args);
	virtual void	RelayScroll(ScrollArgs args);
	virtual void	RelayCursorDrag(DragArgs args);
	virtual void	RelayKey(KeyArgs args);
	virtual void	RelayText(TextArgs args);
};
};
};

#endif