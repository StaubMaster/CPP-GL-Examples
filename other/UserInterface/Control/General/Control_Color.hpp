#ifndef  UI_CONTROL_CONTROL_COLOR_HPP
# define UI_CONTROL_CONTROL_COLOR_HPP

# include "ValueType/_Include.hpp"

namespace UI
{
class Control_Color
{
//	private:				bool	ColorUpdateIsRequested = false;
//	public:					void	ColorUpdateRequest();
//	protected:	virtual		void	ColorUpdate();

//	protected:
//	ColorF4		Color;

	protected:
	virtual ColorF4		Color() const = 0;
};
};

#endif