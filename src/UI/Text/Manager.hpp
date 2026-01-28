#ifndef  UI_TEXT_MANAGER_HPP
# define UI_TEXT_MANAGER_HPP

#include "Data.hpp"
#include "Buffer.hpp"
#include "Shader.hpp"

#include "Miscellaneous/Container/Binary.hpp"
#include "Miscellaneous/EntryContainer/Binary.hpp"

#include "Font/Font.hpp"
#include "Graphics/Texture/Array2D.hpp"



class DirectoryInfo;



namespace UI
{

namespace Text
{

class Manager
{
	public:
	UI::Text::TextShader Shader;
	UI::Text::BufferArray BufferArray;

	Container::Binary<UI::Text::Main_Data> Main_Data_Container;
	EntryContainer::Binary<UI::Text::Inst_Data> Inst_Data_Container;

	Font * TextFont;
	Texture::Array2D Pallet_Texture;

	public:
	Manager(const DirectoryInfo & shader_dir, const DirectoryInfo & text_dir);
	~Manager();

	public:
	void Draw();
};

};

};

#endif