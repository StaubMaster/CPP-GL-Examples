#ifndef  UI_CONTROL_WINDOW_HPP
# define UI_CONTROL_WINDOW_HPP

# include "Control/General/Base.hpp"

namespace UI
{
namespace Control
{
class Window : public Base
{
	public:
	void	AssignPointers(Base & control) override;

	public:
	float		DepthSize = 0.0f;
	VectorF2	WindowSize;

	public:
	//void	DepthUpdate() override;
	float	Depth() const override;

	public:
	~Window();
	Window();

	protected:
	void	BoxUpdate() override;

	public:
	void	WindowPutDisplay();

	private:	bool	DepthCalculateIsRequested = false;
	public:		void	DepthCalculateResolve();
	public:		void	DepthCalculateRequest();
	private:	void	DepthCalculate();
};
};
};

#endif