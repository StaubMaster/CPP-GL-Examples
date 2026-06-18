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
	private:
	ObjectData * Data;

	public:
	bool	Is() const;

	bool	Visibility() const;
	void	Hide();
	void	Show();

	// change to get/set instead of returning referances ?

	std::string &	Text();
	VectorF2 &		TextPosition();
	Alignment &		TextAlignmentX();
	Alignment &		TextAlignmentY();

	VectorF2 &		CharacterSize();
	Alignment &		CharacterAlignmentX();
	Alignment &		CharacterAlignmentY();

	BoxF2 &			Bound();
	ColorF4 &		Color();

	void	AlignTopLeft();
	void	AlignTopMiddle();
	void	AlignTopRight();
	void	AlignMiddleLeft();
	void	AlignMiddleMiddle();
	void	AlignMiddleRight();
	void	AlignBottomLeft();
	void	AlignBottomMiddle();
	void	AlignBottomRight();

	bool			TextCursorVisibility() const;
	void			HideTextCursor();
	void			ShowTextCursor();
	unsigned int &	TextCursorIndex();

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