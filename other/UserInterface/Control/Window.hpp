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
	//float	Depth() const override;

	public:
	~Window() = default;
	Window();

	protected:
//	void	AnchorUpdate() override;
//	void	BoxUpdate() override;
	public:
	BoxF2	BoxDisplay() const override;
	BoxF2	BoxBoarder() const override;
	BoxF2	BoxContent() const override;

	public:
	void	WindowPutDisplay();

	private:	bool	DepthCalculateIsRequested = false;
	public:		void	DepthCalculateRequest();
//	public:		void	DepthCalculateResolve();
	private:	void	DepthCalculate();

	protected:
	void	Update() override;
};
};
};

#endif