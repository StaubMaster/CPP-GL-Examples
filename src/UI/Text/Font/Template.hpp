#ifndef  UI_TEXT_FONT_TEMPLATE_HPP
# define UI_TEXT_FONT_TEMPLATE_HPP

# include "UI/Text/Font/Font.hpp"

# include "DataStruct/Point2D.hpp"

class Image;

namespace UI
{

namespace Text
{

struct Font::Template
{
	Font &	Referance;
	Point2D	Scale;

	Template(Font & referance);
	~Template();

	void Done();

	void Change_Scale(Point2D scale);
	void Insert_Image(Image * img);
	void Change_DefaultCharacter(Point2D pos, Point2D size);
	void Insert_Character(unsigned int code, Point2D pos, Point2D size);
};

};

};

#endif