#ifndef  UI_CONTROL_CONTROL_DISPLAY_HPP
# define UI_CONTROL_CONTROL_DISPLAY_HPP

# include "Control_Flags.hpp"
# include "Control_Box.hpp"
# include "Control_LayerDepth.hpp"
# include "Control_Color.hpp"

namespace UI
{
class Manager;
namespace Control_
{
class Window;
class Form;
class Base;
};
class Control_Display : public Control_Flags, public Control_LayerDepth, public Control_Box, public Control_Color
{
	public:
	void	MakeTransparent() override;
	void	MakeOpaque() override;

	public:
	virtual	void	Show() override;
	virtual	void	Hide() override;



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
	Control_Display() = default;
	Control_Display(const Control_Display & other) = delete;
	Control_Display & operator=(const Control_Display & other) = delete;
};
};

#endif