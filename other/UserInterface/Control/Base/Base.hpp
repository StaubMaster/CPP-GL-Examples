#ifndef  UI_CONTROL_BASE_HPP
# define UI_CONTROL_BASE_HPP

#include "Data.hpp"

#include "Anchor2D.hpp"

#include "User/MouseArgs.hpp"
#include "User/KeyBoardArgs.hpp"

#include "ValueType/_Include.hpp"

#include "Miscellaneous/Container/Binary.hpp"

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
namespace Text { class Manager; };
namespace Control
{
class Manager;
class Base
{
	protected:
	Manager *			ControlManager;
	UI::Text::Manager *	TextManager;

	protected:
	Object		ControlObject;

	protected:
	Base * Parent;
	Container::Binary<Control::Base *> Children;

	public:
	float	Depth; // make this unsigend char. 255 should be more then enough Layers
	unsigned char	Layer() const;

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

	private:
	void	DrawableWantUpdate();
	protected:
	bool	DrawableNeedUpdate;

	public:
	bool	Deletable;		//should be deleted when Parent is deleted

	protected:
	// DisplayBox needs to change if these change ?
	VectorF2	AnchorSize;
	VectorF2	AnchorNormal;
	BoxF2		AnchorDist;
	protected:
	BoxF2		AnchorMargin;
	BoxF2		AnchorBoarder;
	BoxF2		AnchorPadding;
	public:
	Anchor2D	Anchor;

	protected:
	void		BoxWantUpdate();
	public:
	bool		BoxNeedUpdate;
	protected:
	bool		ObjectBoxNeedAssign;
	protected:
	BoxF2		DisplayBox;
	BoxF2		ContainerBox;

	protected:
	bool		ObjectColorNeedAssign;
	public:
	ColorF4		ColorDefault;
	//Color		ColorDisabled; // Gray Text
	ColorF4		ColorHover;

	public:
	virtual ~Base();
	Base();

	public:
	void			ChildInsert(Base & control);
	void			ChildInsert(Base * control);
	virtual void	ChangeManager(Manager * manager);
	virtual void	ChangeManager(UI::Text::Manager * manager);

	// UpdateHandler that has referances to these functions

	// seperate functinos for changing internals vs changing Graphics Object

	public:
	void	Update();

	protected:
	void	ChangeAnchorBox(BoxF2 box);

	private:
	void	UpdateBox();
	void	InsertObject();
	void	RemoveObject();
	void	AssignObjectBox();
	void	AssignObjectColor();

	// Relay Auto
	protected:
	virtual void	RelayUpdateBox();
	virtual void	RelayInsertObject();
	virtual void	RelayRemoveObject();
	virtual void	RelayAssignObjectBox();
	virtual void	RelayAssignObjectColor();

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