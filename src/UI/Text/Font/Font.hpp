#ifndef  UI_TEXT_FONT_HPP
# define UI_TEXT_FONT_HPP

# include "Parsing/ParsingCommand.hpp"
# include "Format/Image.hpp"
# include "Miscellaneous/Container/Dynamic.hpp"
# include "DataStruct/AxisBox2D.hpp"

# include <string>
# include <exception>

struct FileContext;

namespace UI
{

namespace Text
{

class Font
{
	private:
	struct Character
	{
		unsigned int	Code;
		AxisBox2D		Box;
		Character();
	};

	public:
	Image *							AtlasTexture;
	Character						DefaultCharacter;
	Container::Dynamic<Character>	Characters;

	private:
	Font();
	public:
	~Font();

	public:
	AxisBox2D CharacterBoxFromCode(unsigned int code);

	public:
	struct Template;
	//Template * ToTemplate();

	private:
	struct ParsingData;
	public:
	static Font * Parse(const FileContext & file);
};

};

};

#endif