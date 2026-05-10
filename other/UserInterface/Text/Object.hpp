#ifndef  UI_TEXT_OBJECT_HPP
# define UI_TEXT_OBJECT_HPP

# include "Alignment.hpp"

# include "ValueType/Vector/F2.hpp"
# include "ValueType/Box/F2.hpp"
# include "ValueType/ColorF4.hpp"

# include <string>

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

	VectorF2 &		TextPosition();
	Alignment &		TextAlignmentX();
	Alignment &		TextAlignmentY();

	VectorF2 &		CharacterSize();
	Alignment &		CharacterAlignmentX();
	Alignment &		CharacterAlignmentY();

	BoxF2 &			Bound();
	ColorF4 &		Color();

	bool	Visibility() const;
	void	Hide();
	void	Full();

	void	AlignTopLeft();
	void	AlignTopMiddle();
	void	AlignTopRight();
	void	AlignMiddleLeft();
	void	AlignMiddleMiddle();
	void	AlignMiddleRight();
	void	AlignBottomLeft();
	void	AlignBottomMiddle();
	void	AlignBottomRight();

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