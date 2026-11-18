#ifndef  PROPERTY_CONTROL_VECTOR_F_3_HPP
# define PROPERTY_CONTROL_VECTOR_F_3_HPP

# include "UI/NestedProperty.hpp"
# include "Control/Controls/Label.hpp"

struct VectorF3;

namespace UI
{
struct VectorF3 : public NestedProperty
{
	UI::Control_::Label	X;
	UI::Control_::Label	Y;
	UI::Control_::Label	Z;

	VectorF3(const char * name);

	::VectorF3 * Object;
	void	Syncronize();
	void	Change(::VectorF3 * obj);
};
};

#endif