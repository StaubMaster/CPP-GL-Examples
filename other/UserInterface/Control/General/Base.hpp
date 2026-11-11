#ifndef  UI_CONTROL_BASE_HPP
# define UI_CONTROL_BASE_HPP

#include "Anchor2D.hpp"

#include "User/MouseArgs.hpp"
#include "User/KeyBoardArgs.hpp"
#include "HoverArgs.hpp"

#include "ValueType/_Include.hpp"
// include individual

#include "Generics/Container/Binary.hpp"

#include "AnchorEnum.hpp"

/* ...Resolve
are resolve functoins needed ?
they should only be called in the Update function
so just check there ?
*/

/* ...RequestRecursive
sometimes, when something updates, it causes all children to also need to be updated
this is known then the update is requested, so it immedeatly asks all children to update
instead, only request one to update, and once it is done updating, it tells all children to update ?
*/

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

	public:
	void	AssignPointer(UI::Manager * manager);
	void	AssignPointer(UI::Control::Window * window);
	void	AssignPointer(UI::Control::Form * form);

	public:
	void	AssignPointerRecursive(UI::Manager * manager);
	void	AssignPointerRecursive(UI::Control::Window * window);
	void	AssignPointerRecursive(UI::Control::Form * form);

	protected:
	virtual void	AssignPointers(Base & control);

	protected: public:
	Base *	Parent = nullptr;

	protected: public:
	Container::Binary<Base *>	Children;

	public:
	virtual void	ChildClear();
	virtual void	ChildRemove(Base & control);
	virtual void	ChildInsert(Base & control);

	public:
	void	ChildRemove(Base * control);
	void	ChildInsert(Base * control);



	public:
	bool	Deletable = false;
	// true means this should be deleted when Parent is deleted
	// currently not used

	protected:
	bool	IsEnabled_ = true;
	public:
	bool	IsEnabled() const;
	void	Enable();
	void	Disable();

	protected:
	bool	IsVisible_ = true;
	public:
	bool	IsThisVisible() const;
	void	Show();
	void	Hide();

	// make this IsTransparent, so it defaults to false
	protected:
	bool	IsOpaque_ = true;
	public:
	bool	IsOpaque() const;
	void	MakeTransparent();
	void	MakeOpaque();

	public:
	bool	IsVisible() const;
	bool	IsDisplay() const;
//	bool	IsThisInteractible() const;
	bool	IsInteractible() const;



//	private:	unsigned int	Layer_ = 0;
//	public:		unsigned int	Layer() const;
//	public:		void			LayerUpdate();
//	public:		void			LayerUpdateRecursive();
	public:		unsigned int	Layer() const;

	public:		unsigned int	LayerLimit() const;

//	protected:	float			Depth_ = 0.0f;
//	public:		float			Depth() const;
//	public:		virtual	void	DepthUpdate();
//	protected:			void	DepthUpdateRecursive();
	public:		float			Depth() const;



	protected: public:
	VectorF2	AnchorSize;
	VectorF2	AnchorNormal;
	BoxF2		AnchorDist;
	protected: public:
	BoxF2		AnchorMargin;
	BoxF2		AnchorBoarder;
	BoxF2		AnchorPadding;
	protected: public:
	Anchor2D	Anchor;
	protected: public:
//	VectorF2	ContentOffset ?

	protected:	bool			AnchorUpdateIsRequested = false;
	public:		void			AnchorUpdateRequest();
//	public:		void			AnchorUpdateRequestRecursive();
//	private:	void			AnchorUpdateResolve();
	protected:	virtual	void	AnchorUpdate();



	protected: public:
//	BoxF2	BoxDisplay; // used for displaying Control
//	BoxF2	BoxBoarder; // used for culling Children
//	BoxF2	BoxContent; // used for anchoring Children

//	private:	bool			BoxUpdateIsRequested = false;
//	public:		void			BoxUpdateRequest();
//	public:		void			BoxUpdateRequestRecursive();
//	private:	void			BoxUpdateResolve();
//	protected:	virtual	void	BoxUpdate();

	public:
	virtual BoxF2	BoxDisplay() const; // used for displaying Control
	virtual BoxF2	BoxBoarder() const; // used for culling Children
	virtual BoxF2	BoxContent() const; // used for anchoring Children



	public:
	enum class EAutoAnchorType
	{
		None,
		StackMin,		//next.MinDist = prev.MinSize
		//StackMinFit,	//next.MinDist = prev.MinSize but this.Size is made to Fit
	};
	EAutoAnchorType		AutoAnchorXType = EAutoAnchorType::None;
	EAutoAnchorType		AutoAnchorYType = EAutoAnchorType::None;

	private:		bool	AutoAnchorUpdateIsRequested = false;
	public:			void	AutoAnchorUpdateRequest();
//	private:		void	AutoAnchorUpdateResolve();
	public:	virtual	void	AutoAnchorUpdate();

	private:		void	AutoAnchorUpdate_Y_StackMin();
//	private:		void	AutoAnchorUpdate_Y_StackMinFit();

	/* should Children be able to effect Parent ?
		normal Controls dont do that ?
		the only ones I can think of are HTML
		HTML is very complex
		Controls can have Maximum and Minimum Sizes
		they also auto arange themselves
		which is what I want
		changing Children to is easy
		maybe make another to automatically make all Children use the "Both" Anchor
		making the Parent fit the Children is not really needed
	*/



	protected: public:
	ColorF4		ColorDefault;
	//ColorF4	ColorDisabled; // Gray Text
	ColorF4		ColorHover;

//	protected:
//	ColorF4		Color;

//	private:				bool	ColorUpdateIsRequested = false;
//	public:					void	ColorUpdateRequest();
//	public:					void	ColorUpdateRequestRecursive();
//	private:				void	ColorUpdateResolve();
//	protected:	virtual		void	ColorUpdate();

	protected:
	virtual ColorF4		Color() const;



	protected:			bool	Display;
	protected:	virtual	void	DisplayPut() const;
	protected:			void	DisplayPutRecursive() const;

	protected:	virtual	void	DisplayShow();
	protected:	virtual	void	DisplayHide();



	private:			bool	DisplayUpdateIsRequested = false;
	private:			void	DisplayUpdateRequest();
//	private:			void	DisplayUpdateRequestRecursive();
//	private:			void	DisplayUpdateResolve();
	protected:	virtual	void	DisplayUpdate();



	protected:	virtual	void	Update();
	public:				void	UpdateRecursive();



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