#ifndef  UI_CONTROL_OBJECT_HPP
# define UI_CONTROL_OBJECT_HPP

# include "ValueType/AxisBox2D.hpp"
# include "ValueType/ColorF4.hpp"

namespace UI
{
namespace Control
{
struct ObjectData;

struct Object
{
	ObjectData *	Data;

	bool	Is() const;

	bool	Visibility() const;
	void	Hide();
	void	Full();

	AxisBox2D &		Box();
	float &			Layer();
	ColorF4 &		Color();

	~Object();
	Object();
	Object(const Object & other);
	Object & operator=(const Object & other);

	void	Delete();
	void	Create();
};
};
};

#endif