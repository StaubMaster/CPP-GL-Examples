#ifndef  UI_CONTROL_BASE_HPP
# define UI_CONTROL_BASE_HPP

# include "Control_Display.hpp"
# include "Control_UserRelay.hpp"
# include "Control_Container.hpp"

namespace UI
{
namespace Control
{
// rename from Base to Control
// put outside of Control namespace
class Base : public Control_Container<Base>, public Control_Display, public Control_UserRelay
{
	public:
	UI::Control::Form *		Form_ = nullptr; // Forn and Window dont need this.

	public:
			UI::Manager *			_Manager();
			UI::Manager *			_Manager() const;
			UI::Control::Window *	_Window();
	const	UI::Control::Window *	_Window() const;
	// these suck, find a way to replace them

	public:
	void	ChangeFormRecursive(UI::Control::Form * form);



	private:
	Base *	Parent_ = nullptr;
	public:
	Base *	Parent() const;

	public:
	virtual void	ChildClear() override;
	virtual void	ChildRemove(Base & control) override;
	virtual void	ChildInsert(Base & control) override;

	public:
	bool					Check(const DisplayPosition & display_pos) const override;
	UI::Control::Base *		Find(const DisplayPosition & display_pos) override;



	public:
	bool	IsVisible() const override;
	void	Show() override;
	void	Hide() override;



	public:		unsigned int	Layer() const override;

	public:		unsigned int	LayerLimit() const override;

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
	ColorF4		ColorHover;

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