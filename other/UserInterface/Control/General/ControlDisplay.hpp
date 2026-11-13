#ifndef  UI_CONTROL_CONTROL_DISPLAY_HPP
# define UI_CONTROL_CONTROL_DISPLAY_HPP

#include "Anchor2D.hpp"

//#include "User/MouseArgs.hpp"
//#include "User/KeyBoardArgs.hpp"
//#include "HoverArgs.hpp"
struct HoverArgs;
struct ClickArgs;
struct ScrollArgs;
struct DragArgs;
struct KeyArgs;
struct TextArgs;

#include "ValueType/_Include.hpp"
// include individual

namespace UI
{
class Manager;
namespace Control
{
class Window;
class Form;
class Base;
class ControlDisplay
{
	public:
	virtual			UI::Manager *			_Manager() = 0;
	virtual			UI::Manager *			_Manager() const = 0;
	virtual			UI::Control::Window *	_Window() = 0;
	virtual	const	UI::Control::Window *	_Window() const = 0;
	virtual			UI::Control::Form *		_Form() = 0;
	virtual	const	UI::Control::Form *		_Form() const = 0;
	// these suck, find a way to replace them



	public:
	bool	Deletable = false;
	// true means this should be deleted when Parent is deleted
	// currently not used

	private:
	bool	IsEnabled_ = true;
	public:
	bool	IsEnabled() const;
	void	Enable();
	void	Disable();

	private:
	bool	IsOpaque_ = true;
	public:
	bool	IsOpaque() const;
	void	MakeTransparent();
	void	MakeOpaque();

	private:
	bool	IsVisible_ = true;
	public:
			bool	IsThisVisible() const;
	virtual	bool	IsVisible() const;
	virtual	void	Show();
	virtual	void	Hide();

	public:
	bool	IsDisplay() const;
//	bool	IsThisInteractible() const;
	bool	IsInteractible() const;

	// IsActive
	// dont Update if not Active



//	private:	unsigned int	Layer_ = 0;
//	public:		unsigned int	Layer() const;
//	public:		void			LayerUpdate();
//	public:		void			LayerUpdateRecursive();
	public:		virtual	unsigned int	Layer() const = 0;

	public:		virtual	unsigned int	LayerLimit() const = 0;

//	protected:	float			Depth_ = 0.0f;
//	public:		float			Depth() const;
//	public:		virtual	void	DepthUpdate();
//	protected:			void	DepthUpdateRecursive();
//	public:		float			Depth() const;
	public:		float			Depth(float diff = 0.0f) const;



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
	protected:	virtual	void	AnchorUpdate() = 0;



//	private:	bool			BoxUpdateIsRequested = false;
//	public:		void			BoxUpdateRequest();
//	protected:	virtual	void	BoxUpdate();

//	protected: public:
//	BoxF2	BoxDisplay; // used for displaying Control
//	BoxF2	BoxBoarder; // used for culling Children
//	BoxF2	BoxContent; // used for anchoring Children

	public:
	virtual BoxF2	BoxDisplay() const = 0; // used for displaying Control
	virtual BoxF2	BoxBoarder() const = 0; // used for culling Children
	virtual BoxF2	BoxContent() const = 0; // used for anchoring Children



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
	public:	virtual	void	AutoAnchorUpdate();

	private:	virtual	void	AutoAnchorUpdate_Y_StackMin() = 0;
//	private:			void	AutoAnchorUpdate_Y_StackMinFit();

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



//	private:				bool	ColorUpdateIsRequested = false;
//	public:					void	ColorUpdateRequest();
//	protected:	virtual		void	ColorUpdate();

//	protected:
//	ColorF4		Color;

	protected:
	virtual ColorF4		Color() const = 0;



	protected:	virtual	void	DisplayPut() const = 0;
	public:		virtual	void	DisplayPutRecursive() const = 0;



	private:			bool	DisplayUpdateIsRequested = false;
	public:				void	DisplayUpdateRequest();
	protected:	virtual	void	DisplayUpdate();



	protected:	virtual	void	Update();
	public:		virtual	void	UpdateRecursive() = 0;



	public:
	virtual ~ControlDisplay() = default;
	ControlDisplay();
	ControlDisplay(const ControlDisplay & other) = delete;
	ControlDisplay & operator=(const ControlDisplay & other) = delete;



	protected:
	virtual	void	RelayShow();
	virtual	void	RelayHide();

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

	public:
	virtual void	RelayHover(HoverArgs args);
	virtual void	RelayClick(ClickArgs args);
	virtual void	RelayScroll(ScrollArgs args);
	virtual void	RelayDrag(DragArgs args);
	virtual void	RelayKey(KeyArgs args);
	virtual void	RelayText(TextArgs args);
};
};
};

#endif