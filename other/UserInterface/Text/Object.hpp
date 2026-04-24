#ifndef  UI_TEXT_OBJECT_HPP
# define UI_TEXT_OBJECT_HPP

# include "Alignment.hpp"

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
	std::string &	String();

	Point2D &		TextPosition();
	Alignment &		TextAlignmentX();
	Alignment &		TextAlignmentY();

	Point2D &		CharacterSize();
	Alignment &		CharacterAlignmentX();
	Alignment &		CharacterAlignmentY();

	AxisBox2D &		Bound();

	bool	Visibility() const;
	void	Hide();
	void	Full();

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