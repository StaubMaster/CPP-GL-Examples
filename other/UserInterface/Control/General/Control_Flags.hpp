#ifndef  UI_CONTROL_CONTROL_FLAGS_HPP
# define UI_CONTROL_CONTROL_FLAGS_HPP

namespace UI
{
class Control_Flags
{
	//IsDynamic
	// delete this Control when Parent is deleted

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
	virtual	void	MakeTransparent();
	virtual	void	MakeOpaque();

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

	//IsActive
	// dont Update if not Active
};
};

#endif