#ifndef  UI_TEXT_OBJECT_DATA_HPP
# define UI_TEXT_OBJECT_DATA_HPP

# include "Alignment.hpp"

# include "ValueType/Vector/F2.hpp"
# include "ValueType/Box/F2.hpp"
# include "ValueType/Color/F4.hpp"

# include <string>

namespace UI
{
namespace Text
{
struct ObjectData
{
	bool	Remove = false;
	bool	Display = true;

	std::string		Text;
//	const char *	Text;
	VectorF2		TextPosition;
	Alignment		TextAlignmentX;
	Alignment		TextAlignmentY;

	VectorF2		CharacterSize;
	Alignment		CharacterAlignmentX;
	Alignment		CharacterAlignmentY;

	BoxF2			Bound;
	ColorF4			Color0;
	ColorF4			Color1;
	float			Depth = 1.0f;

	bool			DisplayTextCursor = false;
	unsigned int	TextCursorIndex = 0;

	~ObjectData() = default;
	ObjectData(); // basically only for CharacterSize
	ObjectData(const ObjectData & other) = default;
	ObjectData & operator=(const ObjectData & other) = default;

	void	AlignTopLeft();
	void	AlignTopMiddle();
	void	AlignTopRight();
	void	AlignMiddleLeft();
	void	AlignMiddleMiddle();
	void	AlignMiddleRight();
	void	AlignBottomLeft();
	void	AlignBottomMiddle();
	void	AlignBottomRight();
};
};
};

#endif