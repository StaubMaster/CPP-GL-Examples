#ifndef  UI_CONTROL_WINDOW_HPP
# define UI_CONTROL_WINDOW_HPP

# include "Control/General/Base.hpp"

struct DisplaySize;

namespace UI
{
class Manager;
namespace Control
{
class Form;
class Window : public Base
{
	public:
	UI::Manager *			Manager_ = nullptr;

	public:
			UI::Manager *			_Manager() override;
			UI::Manager *			_Manager() const override;
			UI::Control::Window *	_Window() override;
	const	UI::Control::Window *	_Window() const override;
			UI::Control::Form *		_Form() override;
	const	UI::Control::Form *		_Form() const override;

	public:
	void	AssignPointers(Base & control) override;



	private:	VectorF2	Size;
	public:		void		SizeChange(const DisplaySize & display_size);

	public:		float	DepthSize = 0.0f;
	private:	bool	DepthCalculateIsRequested = false;
	public:		void	DepthCalculateRequest();
//	public:		void	DepthCalculateResolve();
	private:	void	DepthCalculate();



	public:
	BoxF2	BoxDisplay() const override;
	BoxF2	BoxBoarder() const override;
	BoxF2	BoxContent() const override;

	protected:
	void	Update() override;



	public:
	~Window() = default;
	Window();
};
};
};

#endif