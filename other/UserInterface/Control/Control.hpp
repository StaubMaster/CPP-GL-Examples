#ifndef  UI_CONTROL_CONTROL_HPP
# define UI_CONTROL_CONTROL_HPP

# include "General/Control_Display.hpp"
# include "General/Control_UserRelay.hpp"
# include "General/Control_Container.hpp"

namespace UI
{
class Manager;
namespace Control_
{
class Window;
class Form;
};
class Control : public Control_Container, public Control_Display, public Control_UserRelay
{
	public:
	virtual			UI::Manager *			_Manager();
	virtual			UI::Manager *			_Manager() const;
	virtual			UI::Control_::Window *	_Window();
	virtual	const	UI::Control_::Window *	_Window() const;
	virtual			UI::Control_::Form *	_Form();
	virtual	const	UI::Control_::Form *	_Form() const;

	protected:	Control *	Parent_ = nullptr;
	public:		Control *	Parent() const;

	public:
	virtual void	ChildClear() override;
	virtual void	ChildRemove(Control & control) override;
	virtual void	ChildInsert(Control & control) override;

	public:
	bool				Check(const DisplayPosition & display_pos) const override;
	UI::Control *		Find(const DisplayPosition & display_pos) override;

	protected:
	bool	IsHovering() const;

	public:
	bool	IsVisible() const override;
	void	Show() override;
	void	Hide() override;

	protected: public:
						ColorF4		ColorDefault;
	protected:	virtual	ColorF4		Color() const override;

	public:	unsigned int	Layer() const override;
	public:	unsigned int	LayerLimit() const override;
	public:	float			Depth(float depth = 0.0f) const override;

	protected:	virtual	void	AnchorUpdate() override;

	protected:
	bool	MetaIs() const override;
	BoxF2	MetaBoxBoarder() const override;
	BoxF2	MetaBoxContent() const override;

	/* Changing Parent
		Fit it needed for Editor3D
		how to prevent recursive loop
		{
AutoFitMinY()
	does not change this.Dist
	does     change this.Size
	needs Children.Dist and Children.Size
		}
		rename AutoAnchor to AutoArranger
	*/
	private:			void	AutoAnchorUpdate_Y_StackMin() override;
	public:				void	AutoFitMinY() override;

	protected:	virtual	void	DisplayPut() const override;
	public:				void	DisplayPutRecursive() const override;

	protected:	virtual	void	DisplayUpdate() override;

	public:				void	UpdateRecursive() override;

	public:
	virtual ~Control() = default;
	Control() = default;
	Control(const Control & other) = delete;
	Control & operator=(const Control & other) = delete;
};
};

#endif