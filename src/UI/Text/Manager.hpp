#ifndef  UI_TEXT_MANAGER_HPP
# define UI_TEXT_MANAGER_HPP

#include "Data.hpp"
#include "Buffer.hpp"
#include "Shader.hpp"

#include "Miscellaneous/Container/Dynamic.hpp"
#include "Miscellaneous/EntryContainer/Dynamic.hpp"

#include "Graphics/Texture/2DArray.hpp"



class DirectoryContext;



namespace UI
{

namespace Text
{

class Manager
{
	public:
		TextShader Shader;
		BufferArray BufferArray;

		Container::Dynamic<UI::Text::Main_Data> Main_Data_Container;
		EntryContainer::Dynamic<UI::Text::Inst_Data> Inst_Data_Container;

		Texture::T2DArray * Pallet_Texture;

	public:
		Manager(const DirectoryContext & shader_dir, const DirectoryContext & image_dir);
		~Manager();

	public:
		void Draw();

	public:
		static Point2D CharToTextCoord(int c);
};

};

};

#endif