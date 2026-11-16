#ifndef  UI_CONTROL_BASE_HPP
# define UI_CONTROL_BASE_HPP

# include "Control_Base.hpp"

namespace UI
{
namespace Control_
{
// rename from Base to Control
// put outside of Control namespace
class Base : public Control_Base
{
	protected:
			UI::Manager *			_Manager() override;
			UI::Manager *			_Manager() const override;
			UI::Control_::Window *	_Window() override;
	const	UI::Control_::Window *	_Window() const override;
	// these suck, find a way to replace them

	protected:
	bool	IsHovering() const;

	public:
	void	ChangeFormRecursive(UI::Control_::Form * form);



	public:
	bool	IsVisible() const override;
	void	Show() override;
	void	Hide() override;



	public:		unsigned int	Layer() const override;

	public:		unsigned int	LayerLimit() const override;

	public:		float	LayerDepth() const override;
	public:		float	DepthOffset() const override;
	public:		float	Depth(float depth = 0.0f) const override;



	protected:	virtual	void	AnchorUpdate() override;



	protected:
	bool	MetaIs() const override;
	BoxF2	MetaBoxBoarder() const override;
	BoxF2	MetaBoxContent() const override;



	private:		void	AutoAnchorUpdate_Y_StackMin() override;
//	private:		void	AutoAnchorUpdate_Y_StackMinFit();



	protected: public:
	ColorF4		ColorDefault;
	//ColorF4	ColorDisabled; // Gray Text
	//ColorF4		ColorHover; // Base does not need HoverColor

	protected:
	virtual ColorF4		Color() const override;



	protected:	virtual	void	DisplayPut() const override;
	public:				void	DisplayPutRecursive() const override;



	protected:	virtual	void	DisplayUpdate() override;



	public:				void	UpdateRecursive() override;



	public:
	virtual ~Base();
	Base();
	Base(const Base & other) = delete;
	Base & operator=(const Base & other) = delete;
};
};
};

#endif