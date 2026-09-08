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
	void	ChangePointers(Base & control) override;

	public:
	float		DepthSize = 0.0f;
	VectorF2	WindowSize;

	public:
	void	AssignDepth() override;

	public:
	~Window();
	Window();

	protected:
	void	BoxUpdate() override;

	public:
	void	WindowPutDisplay();

	private:
	bool	DepthUpdateIsRequested = false;
	public:
	void	DepthUpdateResolve();
	public:
	void	DepthUpdateRequest();
	private:
	void	DepthUpdate();
};
};
};

#endif