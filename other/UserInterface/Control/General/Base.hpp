#ifndef  UI_CONTROL_BASE_HPP
# define UI_CONTROL_BASE_HPP

#include "BufferData.hpp"

#include "Anchor2D.hpp"

#include "User/MouseArgs.hpp"
#include "User/KeyBoardArgs.hpp"
#include "HoverArgs.hpp"

#include "ValueType/_Include.hpp"
// include individual

#include "Generics/Container/Binary.hpp"

#include "Object.hpp"
#include "ObjectData.hpp"


#include "AnchorEnum.hpp"

namespace UI
{
class Manager;
namespace Control
{
class Window;
class Form;
class Base
{
	protected:
	UI::Manager *			Manager = nullptr;
	UI::Control::Window *	Window = nullptr;
	UI::Control::Form *		Form = nullptr;

	protected:
	virtual void	ChangePointers(Base & control);

	public:
	void	ChangeManager(UI::Manager * manager);
	void	ChangeManager(UI::Control::Window * window);
	void	ChangeManager(UI::Control::Form * form);

	public:
	void	ChangeManagerRecursive(UI::Manager * manager);
	void	ChangeManagerRecursive(UI::Control::Window * window);
	void	ChangeManagerRecursive(UI::Control::Form * form);

	protected: public:
	Base *	Parent = nullptr;

	protected: public:
	Container::Binary<Base *>	Children;

	public:
	virtual void	ChildInsert(Base & control);
	virtual void	ChildRemove(Base & control);
	virtual void	ChildClear();

	public:
	void	ChildInsert(Base * control);
	void	ChildRemove(Base * control);

	public:
	unsigned int	Layer = 0;

	public:
	void	CalcLayer();
	void	CalcLayerRecursive();

	public:
//	unsigned int	Layer() const;
	unsigned int	LayerLimit() const;

	public:
	float	Depth = 0.0f; // make this unsigend char. 255 should be more then enough Layers
	// why so greedy ? just make this a uint32

	public:
	virtual void	AssignDepth();
	
	protected:
	void	AssignDepthRecursive();



	public:
	bool	Deletable = false;	//should be deleted when Parent is deleted



	protected:
	bool	_Enabled = true;
	public:
	bool	IsEnabled() const;
	void	MakeEnabled();
	void	MakeDisabled();
	/*
		recursive change Color
	*/

	protected:
	bool	_Visible = true;
	public:
	bool	IsThisVisible() const;
	void	Show();
	void	Hide();
	/*
		recursive change Display
	*/

	protected:
	bool	_Opaque = true;
	public:
	bool	IsTransparent() const;
	bool	IsOpaque() const;
	void	MakeTransparent();
	void	MakeOpaque();
	/*
		change Display
	*/

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
	// make Anchor for X and Y seperate
	// do BoxUpdate seperately ?



	public: //protected:
	BoxF2	BoxDisplay; // used for displaying Control
	BoxF2	BoxBoarder; // used for culling Children
	BoxF2	BoxContent; // used for anchoring Children

	protected:
	virtual void	BoxUpdate();

	private:
	bool	BoxUpdateIsRequested = false;
	void	BoxUpdateResolve();

	public:
	void	BoxUpdateRequest();



	public:
	enum class EAutoAnchorType
	{
		None,
		StackMin, //MinDist of next = MinSize of prev
		StackMinFit, //StackMin but this Control is resized to fit Children
	};
	EAutoAnchorType		AutoAnchorXType = EAutoAnchorType::None;
	EAutoAnchorType		AutoAnchorYType = EAutoAnchorType::None;

	private:
	bool	AutoAnchorUpdateIsRequested = false;
	void	AutoAnchorUpdateResolve();

	public:
	void	AutoAnchorUpdateRequest();

	public:
	virtual void	AutoAnchorUpdate();
	/* AutoAnchor should be done automatically
		when ?
			when ChildInsert()
			when ChildRemove()
			when Child Visibility changes
			when Child Box Changes ?
			DisplayShow() ?
				should be requested
				should not be done when not Visible
		how ?
			need to update Child Boxes first
			so call BoxUpdate again (if needed)
		also X and Y are independant
	*/

	private:
	void	AutoAnchorUpdate_Y_StackMin();
	void	AutoAnchorUpdate_Y_StackMinFit();

	/* combine AutoAnchor and BoxUpdate ?
		BoxUpdate changes Box based on Parent
		AutoAnchorUpdate changes Box based on Children

		UpdateRecursive
		BoxUpdate is done before Updatie()ing Children
		AutoAnchorUpdate is done after Updatie()ing Children

		minimize work
		if AutoAnchorUpdate does something
			tell Parent to also AutoAnchorUpdate
		else
			dont tell Parent to AutoAnchorUpdate

		if AutoAnchorUpdate is supposed to do something
			dont do normal BoxUpdate ?
	*/



	public:
	ColorF4		ColorDefault;
	//Color		ColorDisabled; // Gray Text
	ColorF4		ColorHover;

	protected:
	ColorF4		Color;

	protected:
	virtual void	ColorUpdate();

	private:
	bool	ColorUpdateIsRequested = false;
	void	ColorUpdateResolve();

	public:
	void	ColorUpdateRequest();
	void	ColorUpdateRequestRecursive();



	protected:
	bool	Display;

	protected:
	virtual void	DisplayPut() const;

	protected:
	void	DisplayPutRecursive() const;

	protected:
	virtual void	DisplayShow();
	virtual void	DisplayHide();

	private:
	bool	DisplayChangeIsRequested = false;
	void	DisplayChangeRequest();
	void	DisplayChangeResolve();

	protected:
	virtual void	DisplayChange();



	protected:
	virtual void	Update();

	public:
	void	UpdateRecursive();



	public:
	virtual ~Base();
	Base();

	Base(const Base & other) = delete;
	Base & operator=(const Base & other) = delete;



	public:
	Base *	FindHover(const VectorF2 & mouse);



	/* User Relay
		these should only be called automatically by the Window/Manager
		these change the Controll internally,
		and might call Function Pointers for external stuff
		they should not be accessible to the outside
		they should not be called from inside the Control
	*/
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