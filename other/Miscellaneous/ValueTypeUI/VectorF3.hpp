#ifndef  PROPERTY_CONTROL_VECTOR_F_3_HPP
# define PROPERTY_CONTROL_VECTOR_F_3_HPP

# include "ValueTypeUI/PropertyControl.hpp"
# include "Control/Label.hpp"

struct VectorF3;

namespace UI
{
namespace Control
{
struct VectorF3 : public PropertyControl
{
	Label	X;
	Label	Y;
	Label	Z;

	~VectorF3();
	VectorF3(const char * name);

	::VectorF3 * Object;
	void	Update();
	void	Change(::VectorF3 * obj);
};
};
};

#endif