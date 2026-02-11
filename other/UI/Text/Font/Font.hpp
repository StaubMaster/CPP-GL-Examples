#ifndef  UI_TEXT_FONT_HPP
# define UI_TEXT_FONT_HPP

# include "FileParsing/Text/TextCommand.hpp"
# include "Image.hpp"
# include "Miscellaneous/Container/Binary.hpp"
# include "ValueType/AxisBox2D.hpp"

# include <string>
# include <exception>

class FileInfo;

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
	Image							AtlasTexture;
	Character						DefaultCharacter;
	Container::Binary<Character>	Characters;

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
	static Font * Parse(const FileInfo & file);
};

};

};

#endif