#ifndef  UI_TEXT_FONT_TEMPLATE_HPP
# define UI_TEXT_FONT_TEMPLATE_HPP

# include "Text/Font/Font.hpp"

# include "ValueType/Vector/F2.hpp"

class Image;

namespace UI
{

namespace Text
{

struct Font::Template
{
	Font &	Referance;
	VectorF2	Scale;

	Template(Font & referance);
	~Template();

	void Done();

	void Change_Scale(VectorF2 scale);
	void Insert_Image(Image img);
	void Change_DefaultCharacter(VectorF2 pos, VectorF2 size);
	void Insert_Character(unsigned int code, VectorF2 pos, VectorF2 size);
};

};

};

#endif