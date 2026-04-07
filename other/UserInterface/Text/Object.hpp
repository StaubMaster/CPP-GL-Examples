#ifndef  UI_TEXT_OBJECT_HPP
# define UI_TEXT_OBJECT_HPP

# include "ValueType/Point2D.hpp"
# include "ValueType/AxisBox2D.hpp"
# include "string"

namespace UI
{
namespace Text
{
struct ObjectData;

struct Object
{
	ObjectData * Data;

	bool			Is() const;
	std::string &	String() const;
	
	Point2D &		Pos() const;
	AxisBox2D &		Bound() const;

	bool	Visibility() const;
	void	Hide() const;
	void	Full() const;

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