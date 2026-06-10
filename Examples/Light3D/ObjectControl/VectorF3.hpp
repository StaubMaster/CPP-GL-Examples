#ifndef  OBJECT_CONTROL_VECTOR_F_3_HPP
# define OBJECT_CONTROL_VECTOR_F_3_HPP

# include "Control/GroupBox.hpp"
# include "Control/Label.hpp"

struct VectorF3;

namespace UI
{
namespace Control
{
struct VectorF3 : public GroupBox
{
	Label	X;
	Label	Y;
	Label	Z;

	~VectorF3();
	VectorF3();

	::VectorF3 * Object;
	void	Change(::VectorF3 * obj);
};
};
};

#endif