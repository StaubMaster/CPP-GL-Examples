#ifndef  UI_CONTROL_WINDOW_HPP
# define UI_CONTROL_WINDOW_HPP

# include "Control/General/Base.hpp"

struct DisplaySize;
struct DisplayPosition;

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
	public:		BoxF2		Box() const;



	private:
	UI::Control::Form *		Find(const DisplayPosition & display_pos);
	private:
	UI::Control::Form *		Hovering_ = nullptr;
	UI::Control::Form *		Selected_ = nullptr;
	public:
	UI::Control::Form *		Hovering() const;
	UI::Control::Form *		Selected() const;
	private:
	void	HoveringChange(UI::Control::Form * form, const DisplayPosition & display_pos);
	void	SelectedChange();
	public:
	void	HoveringUpdate(const DisplayPosition & display_pos);
	void	SelectedUpdate();



	private:	bool	DepthCalculateIsRequested = false;
	public:		void	DepthCalculateRequest();
//	public:		void	DepthCalculateResolve();
	private:	void	DepthCalculate();

	public:		float	DepthSize = 0.0f; // how much Depth does a Control take



	public:
	void	DisplayPut();
	public:
	void	Update();



	public:
	~Window() = default;
	Window();
};
};
};

#endif