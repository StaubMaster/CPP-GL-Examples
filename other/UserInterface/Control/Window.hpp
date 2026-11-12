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
class Window
{
	public:
	UI::Manager *			Manager_ = nullptr;

	public:
			UI::Manager *			_Manager();
			UI::Manager *			_Manager() const;
			UI::Control::Window *	_Window();
	const	UI::Control::Window *	_Window() const;
			UI::Control::Form *		_Form();
	const	UI::Control::Form *		_Form() const;

	public:
	void	AssignPointers(Form & control);



	protected: public:
	Container::Binary<Form *>	Children;

	public:
	void	ChildClear();
	void	ChildRemove(Form & control);
	void	ChildInsert(Form & control);

	public:
	void	ChildRemove(Form * control);
	void	ChildInsert(Form * control);



	private:	VectorF2	Size;
	public:		void		SizeChange(const DisplaySize & display_size);

	public:		float	DepthSize = 0.0f;
	private:	bool	DepthCalculateIsRequested = false;
	public:		void	DepthCalculateRequest();
//	public:		void	DepthCalculateResolve();
	private:	void	DepthCalculate();



	public:
	BoxF2	BoxDisplay() const;
	BoxF2	BoxBoarder() const;
	BoxF2	BoxContent() const;

	public:
	void	DisplayPut();
	public:
	void	Update();



	public:
	~Window() = default;
	Window();



	public:
	ControlDisplay *	FindHover(const VectorF2 & mouse);
};
};
};

#endif