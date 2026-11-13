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
class Control_Display
{
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
	public:		virtual float	Depth(float depth = 0.0f) const = 0;



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

	private:	bool			AnchorUpdateIsRequested = false;
	public:		void			AnchorUpdateRequest();
	protected:	virtual	void	AnchorUpdate();



//	private:	bool			BoxUpdateIsRequested = false;
//	public:		void			BoxUpdateRequest();
//	protected:	virtual	void	BoxUpdate();

//	protected: public:
//	BoxF2	BoxDisplay; // used for displaying Control
//	BoxF2	BoxBoarder; // used for culling Children
//	BoxF2	BoxContent; // used for anchoring Children

	protected:
	virtual bool	MetaIs() const = 0;
	virtual BoxF2	MetaBoxBoarder() const = 0;
	virtual BoxF2	MetaBoxContent() const = 0;

	public:
	BoxF2	BoxDisplay() const; // used for displaying Control
	BoxF2	BoxBoarder() const; // used for culling Children
	BoxF2	BoxContent() const; // used for anchoring Children



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

	protected:	virtual	void	RelayShow();
	protected:	virtual	void	RelayHide();



	protected:	virtual	void	Update();
	public:		virtual	void	UpdateRecursive() = 0;



	public:
	virtual ~Control_Display() = default;
	Control_Display();
	Control_Display(const Control_Display & other) = delete;
	Control_Display & operator=(const Control_Display & other) = delete;
};
};
};

#endif