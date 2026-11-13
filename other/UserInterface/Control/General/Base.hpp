#ifndef  UI_CONTROL_BASE_HPP
# define UI_CONTROL_BASE_HPP

# include "ControlDisplay.hpp"

# include "Generics/Container/Binary.hpp"

struct DisplayPosition;

namespace UI
{
namespace Control
{
class Base : public ControlDisplay
{
	public:
	UI::Control::Form *		Form_ = nullptr; // Forn and Window dont need this.
	/*
		make Base that ForM and Window inherit from,
		and another Base,
		that inhertis from the first Base
		and that all of the actual Control inherit from
	*/

	public:
	virtual			UI::Manager *			_Manager() override;
	virtual			UI::Manager *			_Manager() const override;
	virtual			UI::Control::Window *	_Window() override;
	virtual	const	UI::Control::Window *	_Window() const override;
	virtual			UI::Control::Form *		_Form() override;
	virtual	const	UI::Control::Form *		_Form() const override;
	// these suck, find a way to replace them

	public:
	void	ChangeForm(UI::Control::Form * form);



	protected: public:
	Base *	Parent = nullptr; // could this be const ?

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
	bool	IsVisible() const override;
	void	Show() override;
	void	Hide() override;



	public:		unsigned int	Layer() const override;

	public:		unsigned int	LayerLimit() const override;



	protected:	virtual	void	AnchorUpdate() override;



	public:
	virtual BoxF2	BoxDisplay() const override; // used for displaying Control
	virtual BoxF2	BoxBoarder() const override; // used for culling Children
	virtual BoxF2	BoxContent() const override; // used for anchoring Children



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
	UI::Control::Base *		Find(const DisplayPosition & display_pos);



	public:
	virtual ~Base();
	Base();
	Base(const Base & other) = delete;
	Base & operator=(const Base & other) = delete;
};
};
};

#endif