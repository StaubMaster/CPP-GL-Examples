#ifndef  UI_TEXT_FONT_HPP
# define UI_TEXT_FONT_HPP

# include "FileParsing/Text/TextCommand.hpp"
# include "Image.hpp"
# include "Miscellaneous/Container/Binary.hpp"
# include "ValueType/Box/F2.hpp"

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
		BoxF2			Box;
		Character();
	};
	struct CharacterRange
	{
		unsigned int					CodeMin;
		unsigned int					CodeMax;
		Container::Binary<Character>	Characters;
	};

	public:
	Image								AtlasTexture;
	Character							DefaultCharacter;
	Container::Binary<Character>		Characters;
	Container::Binary<CharacterRange*>	CharacterRanges;

	public:
	Character &		operator[](unsigned int code);

	public:
	~Font();
	Font();
	Font(const Font & other) = delete;
	Font & operator=(const Font & other) = delete;

	private:
	struct ParsingData;
	public:
	static Font * Parse(const FileInfo & file);
};

};

};

#endif